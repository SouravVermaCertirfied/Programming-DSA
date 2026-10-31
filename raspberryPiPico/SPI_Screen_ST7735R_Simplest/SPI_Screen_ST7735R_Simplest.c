#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

// SPI Defines using your exact pins
#define SPI_PORT spi0
#define PIN_DC   16  // Reassigned from MISO (display is write-only)
#define PIN_CS   17  // Chip Select
#define PIN_SCK  18  // Clock
#define PIN_MOSI 19  // Data (SDA)

// Display dimensions
#define TFT_WIDTH  128
#define TFT_HEIGHT 160

// ST7735 Commands
#define ST7735_SWRESET 0x01
#define ST7735_SLPOUT  0x11
#define ST7735_DISPON  0x29
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define ST7735_COLMOD  0x3A

static inline void lcd_command(uint8_t cmd) {
    gpio_put(PIN_DC, 0); // DC low = Command
    gpio_put(PIN_CS, 0);
    spi_write_blocking(SPI_PORT, &cmd, 1);
    gpio_put(PIN_CS, 1);
}

static inline void lcd_data(const uint8_t *data, size_t size) {
    gpio_put(PIN_DC, 1); // DC high = Data
    gpio_put(PIN_CS, 0);
    spi_write_blocking(SPI_PORT, data, size);
    gpio_put(PIN_CS, 1);
}

void st7735_init() {
    sleep_ms(150);

    lcd_command(ST7735_SWRESET);
    sleep_ms(150);

    lcd_command(ST7735_SLPOUT);
    sleep_ms(500);

    // Color mode: 16-bit color (RGB565)
    lcd_command(ST7735_COLMOD);
    uint8_t color_mode = 0x05;
    lcd_data(&color_mode, 1);

    lcd_command(ST7735_DISPON);
    sleep_ms(100);
}

void st7735_fill_screen(uint16_t color) {
    lcd_command(ST7735_CASET);
    uint8_t caset_data[] = { 0x00, 0x00, 0x00, (uint8_t)(TFT_WIDTH - 1) };
    lcd_data(caset_data, 4);

    lcd_command(ST7735_RASET);
    uint8_t raset_data[] = { 0x00, 0x00, 0x00, (uint8_t)(TFT_HEIGHT - 1) };
    lcd_data(raset_data, 4);

    lcd_command(ST7735_RAMWR);

    uint8_t high = color >> 8;
    uint8_t low = color & 0xFF;

    gpio_put(PIN_DC, 1);
    gpio_put(PIN_CS, 0);
    for (int i = 0; i < TFT_WIDTH * TFT_HEIGHT; i++) {
        spi_write_blocking(SPI_PORT, &high, 1);
        spi_write_blocking(SPI_PORT, &low, 1);
    }
    gpio_put(PIN_CS, 1);
}

int main()
{
    stdio_init_all();

    // SPI initialisation at 16 MHz
    spi_init(SPI_PORT, 16000 * 1000);
    gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
    // Configure CS and DC using your pins (17 and 16)
    gpio_init(PIN_CS);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);

    gpio_init(PIN_DC);
    gpio_set_dir(PIN_DC, GPIO_OUT);
    gpio_put(PIN_DC, 1);

    st7735_init();

    bool state = false;

    while (true) {
        if (state) {
            st7735_fill_screen(0xF800); // Red
            printf("Screen RED\n");
        } else {
            st7735_fill_screen(0x0000); // Black
            printf("Screen BLACK\n");
        }
        
        state = !state;
        sleep_ms(1000);
    }
}