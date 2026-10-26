#include "pico/stdlib.h"
#include "hardware/spi.h"

// Pin definitions
#define PIN_SCK   18
#define PIN_MOSI  19
#define PIN_CS    17
#define PIN_DC    16
#define PIN_RST   21

// ST7735 Commands
#define ST7735_SWRESET 0x01
#define ST7735_SLPOUT  0x11
#define ST7735_DISPON  0x29
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define ST7735_MADCTL  0x36
#define ST7735_COLMOD  0x3A

void tft_write_command(uint8_t cmd) {
    gpio_put(PIN_DC, 0); 
    gpio_put(PIN_CS, 0); 
    spi_write_blocking(spi0, &cmd, 1);
    gpio_put(PIN_CS, 1); 
}

void tft_write_data(const uint8_t *data, size_t len) {
    gpio_put(PIN_DC, 1); 
    gpio_put(PIN_CS, 0); 
    spi_write_blocking(spi0, data, len);
    gpio_put(PIN_CS, 1); 
}

void tft_init() {
    spi_init(spi0, 1000 * 1000);
    spi_set_format(spi0, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);

    gpio_init(PIN_CS);  gpio_set_dir(PIN_CS, GPIO_OUT);   gpio_put(PIN_CS, 1);
    gpio_init(PIN_DC);  gpio_set_dir(PIN_DC, GPIO_OUT);   gpio_put(PIN_DC, 1);
    gpio_init(PIN_RST); gpio_set_dir(PIN_RST, GPIO_OUT);  gpio_put(PIN_RST, 1);

    // Hardware Reset Pulse
    gpio_put(PIN_RST, 1);
    sleep_ms(50);
    gpio_put(PIN_RST, 0);
    sleep_ms(50);
    gpio_put(PIN_RST, 1);
    sleep_ms(150);

    tft_write_command(ST7735_SWRESET);
    sleep_ms(150);

    tft_write_command(ST7735_SLPOUT);
    sleep_ms(255);

    tft_write_command(ST7735_COLMOD);
    uint8_t color_mode = 0x05; // 16-bit RGB565
    tft_write_data(&color_mode, 1);

    tft_write_command(ST7735_MADCTL);
    uint8_t madctl = 0xC0;
    tft_write_data(&madctl, 1);

    tft_write_command(ST7735_DISPON);
    sleep_ms(100);
}

void tft_fill_color(uint16_t color) {
    tft_write_command(ST7735_CASET);
    uint8_t x_data[] = {0x00, 0x00, 0x00, 0x7F}; // 0 to 127
    tft_write_data(x_data, 4);

    tft_write_command(ST7735_RASET);
    uint8_t y_data[] = {0x00, 0x00, 0x00, 0x9F}; // 0 to 159
    tft_write_data(y_data, 4);

    tft_write_command(ST7735_RAMWR);

    uint8_t high = color >> 8;
    uint8_t low = color & 0xFF;

    gpio_put(PIN_DC, 1);
    gpio_put(PIN_CS, 0);
    for (int i = 0; i < 128 * 160; i++) {
        spi_write_blocking(spi0, &high, 1);
        spi_write_blocking(spi0, &low, 1);
    }
    gpio_put(PIN_CS, 1);
}

int main() {
    tft_init();

    while (true) {
        tft_fill_color(0xF800); // Red
        sleep_ms(1000);
        tft_fill_color(0x07E0); // Green
        sleep_ms(1000);
        tft_fill_color(0x001F); // Blue
        sleep_ms(1000);
    }
}