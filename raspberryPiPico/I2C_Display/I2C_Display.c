#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// --- I2C Screen Configuration (Dedicated Pins) ---
#define I2C_SCREEN_PORT        i2c0
#define I2C_SCREEN_PIN_SDA     8      // Physical Pin 11
#define I2C_SCREEN_PIN_SCL     9      // Physical Pin 12
#define I2C_SCREEN_OLED_ADDR   0x3C   // Standard OLED I2C Address

// 128x32 Display dimensions (4 pages of 8 rows = 32 pixels high)
#define OLED_WIDTH 128
#define OLED_HEIGHT 32
static uint8_t fb[OLED_HEIGHT / 8][OLED_WIDTH];

// Tiny 5x7 font table for digit 9 (and others)
static const uint8_t font5x7[10][5] = {
    {0x3E, 0x51, 0x49, 0x45, 0x3E}, // 0
    {0x00, 0x42, 0x7F, 0x40, 0x00}, // 1
    {0x42, 0x61, 0x51, 0x49, 0x46}, // 2
    {0x21, 0x41, 0x45, 0x4B, 0x31}, // 3
    {0x18, 0x14, 0x12, 0x7F, 0x10}, // 4
    {0x27, 0x45, 0x45, 0x45, 0x39}, // 5
    {0x3C, 0x4A, 0x49, 0x49, 0x30}, // 6
    {0x01, 0x71, 0x09, 0x05, 0x03}, // 7
    {0x36, 0x49, 0x49, 0x49, 0x36}, // 8
    {0x06, 0x49, 0x49, 0x29, 0x1E}  // 9
};

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
    if (c >= '0' && c <= '9') {
        int index = c - '0';
        for (int i = 0; i < 5; i++) {
            if (x + i < OLED_WIDTH && page < 4) {
                fb[page][x + i] = font5x7[index][i];
            }
        }
    }
}

// Push the frame buffer to the OLED screen
void i2c_screen_flush() {
    i2c_screen_send_byte(0x21, false); i2c_screen_send_byte(0, false); i2c_screen_send_byte(OLED_WIDTH - 1, false);
    i2c_screen_send_byte(0x22, false); i2c_screen_send_byte(0, false); i2c_screen_send_byte((OLED_HEIGHT / 8) - 1, false);

    uint8_t packet[OLED_WIDTH * (OLED_HEIGHT / 8) + 1];
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

    // Clear buffer, draw "9" roughly centered, and update display
    i2c_screen_clear();
    i2c_screen_draw_char(60, 1, '9'); 
    i2c_screen_flush();

    while (true) {
        tight_loop_contents();
    }
}