#include "I2C_Display.h"

#if(MODE == ONE_PIXEL_BLINK)

/**
 * ============================================================================
 * STUDENT LESSON: BLINKING A SINGLE PIXEL OVER I2C
 * ============================================================================
 * Concepts covered:
 * 1. Initializing the I2C Master peripheral and configuring pins (SDA/SCL).
 * 2. Sending initialization commands to wake up the SSD1306 OLED controller.
 * 3. Modifying a single bit in the framebuffer memory (`fb[0][0]`).
 * 4. Flushing the framebuffer across the I2C bus to update the physical screen.
 * ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// --- I2C Hardware Definitions ---
#define I2C_SCREEN_PORT        i2c0
#define I2C_SCREEN_PIN_SDA     8      // GPIO 8 (Physical Pin 11)
#define I2C_SCREEN_PIN_SCL     9      // GPIO 9 (Physical Pin 12)
#define I2C_SCREEN_OLED_ADDR   0x3C   // Standard 7-bit I2C address for SSD1306

// --- Display Dimensions ---
#define OLED_WIDTH 128
#define OLED_HEIGHT 32

// The framebuffer: 4 vertical pages (32 pixels / 8 bits per byte) by 128 columns.
static uint8_t fb[OLED_HEIGHT / 8][OLED_WIDTH];

// Sends a single byte over I2C (is_data = true for pixel RAM, false for commands)
void i2c_screen_send_byte(uint8_t val, bool is_data) {
    uint8_t buf[2];
    buf[0] = is_data ? 0x40 : 0x00; // 0x40 tells the OLED "data follows", 0x00 means "command follows"
    buf[1] = val;
    i2c_write_blocking(I2C_SCREEN_PORT, I2C_SCREEN_OLED_ADDR, buf, 2, false);
}

// Startup command sequence required to configure the OLED hardware controller
void i2c_screen_init() {
    uint8_t cmds[] = {
        0xAE,       // Display off
        0xD5, 0x80, // Clock divide ratio
        0xA8, 0x1F, // Multiplex ratio (32 lines for 128x32)
        0xD3, 0x00, // Display offset
        0x40,       // Start line address
        0x8D, 0x14, // Charge pump enabled (internal voltage boost)
        0x20, 0x00, // Horizontal addressing mode
        0xA1,       // Segment re-map
        0xC8,       // COM output scan direction
        0xDA, 0x02, // COM pins hardware configuration
        0x81, 0x8F, // Contrast control
        0xD9, 0xF1, // Pre-charge period
        0xDB, 0x40, // VCOMH deselect level
        0xA4,       // Entire display on resume
        0xA6,       // Normal display (non-inverted)
        0xAF        // Display on
    };
    for (int i = 0; i < sizeof(cmds); i++) {
        i2c_screen_send_byte(cmds[i], false);
    }
}

// Pushes the entire local framebuffer memory block over I2C to the physical screen
void i2c_screen_flush() {
    // Set column address range from 0 to 127
    i2c_screen_send_byte(0x21, false); i2c_screen_send_byte(0, false); i2c_screen_send_byte(OLED_WIDTH - 1, false);
    // Set page address range from 0 to 3
    i2c_screen_send_byte(0x22, false); i2c_screen_send_byte(0, false); i2c_screen_send_byte((OLED_HEIGHT / 8) - 1, false);

    // Create a bulk packet: 1 data control byte (0x40) + 512 bytes of pixel memory (128 * 4)
    uint8_t packet[(OLED_WIDTH * (OLED_HEIGHT / 8)) + 1];
    packet[0] = 0x40;
    memcpy(&packet[1], fb, sizeof(fb));
    i2c_write_blocking(I2C_SCREEN_PORT, I2C_SCREEN_OLED_ADDR, packet, sizeof(packet), false);
}

int main() {
    stdio_init_all();

    // Initialize I2C0 peripheral at 400 kHz on GP8 (SDA) and GP9 (SCL)
    i2c_init(I2C_SCREEN_PORT, 400 * 1000);
    gpio_set_function(I2C_SCREEN_PIN_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCREEN_PIN_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SCREEN_PIN_SDA);
    gpio_pull_up(I2C_SCREEN_PIN_SCL);

    sleep_ms(100);
    i2c_screen_init();

    // Main Loop: Blink the first pixel (top-left corner) every 500 milliseconds
    while (true) {
        // --- STEP 1: Turn ON the first pixel ---
        memset(fb, 0, sizeof(fb));    // Clear the whole buffer to 0s
        fb[0][0] = 0x01;              // Page 0, Column 0: LSB (0x01) lights the very top-left pixel
        i2c_screen_flush();           // Send buffer over I2C to display
        sleep_ms(500);                // Wait half a second

        // --- STEP 2: Turn OFF the first pixel ---
        memset(fb, 0, sizeof(fb));    // Clear the whole buffer back to 0s
        i2c_screen_flush();           // Send buffer over I2C to display
        sleep_ms(500);                // Wait half a second
    }
}

#endif