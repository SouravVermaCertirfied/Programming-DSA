#include <string.h>
#include "hardware/i2c.h"
#include "pico/stdlib.h"

#define I2C_PORT       i2c0
#define OLED_ADDR      0x3C
#define OLED_WIDTH     128
#define OLED_HEIGHT    32

static uint8_t fb[OLED_HEIGHT / 8][OLED_WIDTH];

// Tiny 5x7 font table for digits 0-9 and space/hex
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

static void oled_send_byte(uint8_t val, bool is_data) {
    uint8_t buf[2] = {is_data ? 0x40 : 0x00, val};
    i2c_write_blocking(I2C_PORT, OLED_ADDR, buf, 2, false);
}

void oled_init() {
    uint8_t cmds[] = {
        0xAE, 0xD5, 0x80, 0xA8, 0x1F, 0xD3, 0x00, 0x40,
        0x8D, 0x14, 0x20, 0x00, 0xA1, 0xC8, 0xDA, 0x02,
        0x81, 0x8F, 0xD9, 0xF1, 0xDB, 0x40, 0xA4, 0xA6, 0xAF
    };
    for (int i = 0; i < sizeof(cmds); i++) {
        oled_send_byte(cmds[i], false);
    }
}

void oled_clear() {
    memset(fb, 0, sizeof(fb));
}

void oled_draw_char(int x, int page, char c) {
    if (c >= '0' && c <= '9') {
        int index = c - '0';
        for (int i = 0; i < 5; i++) {
            if (x + i < OLED_WIDTH && page < 4) {
                fb[page][x + i] = font5x7[index][i];
            }
        }
    }
}

void oled_flush() {
    oled_send_byte(0x21, false); oled_send_byte(0, false); oled_send_byte(OLED_WIDTH - 1, false);
    oled_send_byte(0x22, false); oled_send_byte(0, false); oled_send_byte((OLED_HEIGHT / 8) - 1, false);

    uint8_t packet[OLED_WIDTH * (OLED_HEIGHT / 8) + 1];
    packet[0] = 0x40;
    memcpy(&packet[1], fb, sizeof(fb));
    i2c_write_blocking(I2C_PORT, OLED_ADDR, packet, sizeof(packet), false);
}