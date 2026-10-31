#include "I2C_Display.h"

#if(MODE == DISPLAY_ONE_NUMBER)
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// --- I2C Screen Configuration (Dedicated Pins) ---
#define I2C_SCREEN_PORT        i2c0
#define I2C_SCREEN_PIN_SDA     8       // Physical Pin 11
#define I2C_SCREEN_PIN_SCL     9       // Physical Pin 12
#define I2C_SCREEN_OLED_ADDR   0x3C    // Standard OLED I2C Address

// 128x32 Display dimensions (4 pages of 8 rows = 32 pixels high)
#define OLED_WIDTH 128
#define OLED_HEIGHT 32
static uint8_t fb[OLED_HEIGHT / 8][OLED_WIDTH];

// Send a single command or data byte to the screen
void i2c_screen_send_byte(uint8_t val, bool is_data) {
    uint8_t buf[2];
    buf[0] = is_data ? 0x40 : 0x00;
    buf[1] = val;
    i2c_write_blocking(I2C_SCREEN_PORT, I2C_SCREEN_OLED_ADDR, buf, 2, false);
}

void i2c_screen_init() {
    uint8_t cmds[] = {
        0xAE,       // Display off
        0xD5, 0x80, // Clock divide ratio
        0xA8, 0x1F, // Multiplex ratio (32 for 128x32)
        0xD3, 0x00, // Display offset
        0x40,       // Start line address
        0x8D, 0x14, // Charge pump
        0x20, 0x00, // Horizontal addressing mode
        0xA1,       // Segment re-map
        0xC8,       // COM output scan direction
        0xDA, 0x02, // COM pins hardware configuration
        0x81, 0x8F, // Contrast control
        0xD9, 0xF1, // Pre-charge period
        0xDB, 0x40, // VCOMH deselect level
        0xA4,       // Entire display on resume
        0xA6,       // Normal display
        0xAF        // Display on
    };
    for (int i = 0; i < sizeof(cmds); i++) {
        i2c_screen_send_byte(cmds[i], false);
    }
}

// Clear the frame buffer
void i2c_screen_clear() {
    memset(fb, 0, sizeof(fb));
}

// Draw a character onto the frame buffer
void i2c_screen_draw_char(int x, int page, char c) {
    const uint8_t *glyph = NULL;

    static const uint8_t font_s[5]     = {0x48, 0x54, 0x54, 0x54, 0x24}; // Lowercase s
    static const uint8_t font_o[5]     = {0x38, 0x44, 0x44, 0x44, 0x38}; // Lowercase o
    static const uint8_t font_u[5]     = {0x3C, 0x40, 0x40, 0x20, 0x7C}; // Lowercase u
    static const uint8_t font_r[5]     = {0x7C, 0x08, 0x04, 0x04, 0x08}; // Lowercase r
    static const uint8_t font_a[5]     = {0x20, 0x54, 0x54, 0x54, 0x78}; // Lowercase a
    static const uint8_t font_v[5]     = {0x1C, 0x20, 0x40, 0x20, 0x1C}; // Lowercase v
    static const uint8_t font_e[5]     = {0x38, 0x54, 0x54, 0x54, 0x18}; // Lowercase e
    static const uint8_t font_m[5]     = {0x7C, 0x04, 0x08, 0x04, 0x7C}; // Lowercase m
    static const uint8_t font_space[5] = {0x00, 0x00, 0x00, 0x00, 0x00};

    switch (c) {
        case 's': glyph = font_s; break;
        case 'o': glyph = font_o; break;
        case 'u': glyph = font_u; break;
        case 'r': glyph = font_r; break;
        case 'a': glyph = font_a; break;
        case 'v': glyph = font_v; break;
        case 'e': glyph = font_e; break;
        case 'm': glyph = font_m; break;
        case ' ': glyph = font_space; break;
        default:  glyph = font_space; break;
    }

    if (glyph) {
        for (int i = 0; i < 5; i++) {
            if (x + i >= 0 && x + i < OLED_WIDTH && page >= 0 && page < 4) {
                fb[page][x + i] = glyph[i];
            }
        }
    }
}

// Draw a full string onto the frame buffer
void i2c_screen_draw_string(int x, int page, const char *str) {
    int cursor_x = x;
    while (*str) {
        i2c_screen_draw_char(cursor_x, page, *str);
        cursor_x += 6; // 5 pixels for char + 1 pixel gap
        str++;
    }
}

// Push the frame buffer to the OLED screen
void i2c_screen_flush() {
    i2c_screen_send_byte(0x21, false); 
    i2c_screen_send_byte(0, false); 
    i2c_screen_send_byte(OLED_WIDTH - 1, false);
    
    i2c_screen_send_byte(0x22, false); 
    i2c_screen_send_byte(0, false); 
    i2c_screen_send_byte((OLED_HEIGHT / 8) - 1, false);

    uint8_t packet[(OLED_WIDTH * (OLED_HEIGHT / 8)) + 1];
    packet[0] = 0x40;
    memcpy(&packet[1], fb, sizeof(fb));
    i2c_write_blocking(I2C_SCREEN_PORT, I2C_SCREEN_OLED_ADDR, packet, sizeof(packet), false);
}

int main() {
    stdio_init_all();

    // Initialize I2C0 for the screen on GP8 (SDA) and GP9 (SCL)
    i2c_init(I2C_SCREEN_PORT, 400 * 1000);
    gpio_set_function(I2C_SCREEN_PIN_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCREEN_PIN_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SCREEN_PIN_SDA);
    gpio_pull_up(I2C_SCREEN_PIN_SCL);

    sleep_ms(100);
    i2c_screen_init();

    // "sourav verma" has 12 characters -> (12 * 6) - 1 = 71 pixels wide
    const int text_width = 71;
    const int max_x = OLED_WIDTH - text_width; // 128 - 71 = 57 pixels

    int text_x = 10;
    int text_page = 1;
    int text_vx = 1;  // 1 pixel horizontal step for silky smooth flow
    int text_vpage = 1;
    int page_timer = 0;

    while (true) {
        i2c_screen_clear();

        // Draw "sourav verma" bouncing around
        i2c_screen_draw_string(text_x, text_page, "sourav verma");

        i2c_screen_flush();

    }
}
#endif