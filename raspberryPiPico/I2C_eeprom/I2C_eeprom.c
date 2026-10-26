#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// External driver declarations
void eeprom_init();
void eeprom_write_byte(uint16_t mem_address, uint8_t data);
uint8_t eeprom_read_byte(uint16_t mem_address);

void oled_init();
void oled_clear();
void oled_draw_char(int x, int page, char c);
void oled_flush();

#define I2C_BUS_PORT     i2c0
#define I2C_BUS_PIN_SDA  8      // Physical Pin 11
#define I2C_BUS_PIN_SCL  9      // Physical Pin 12

int main() {
    stdio_init_all();
    sleep_ms(1500);

    // Initialize Shared I2C0 Bus
    i2c_init(I2C_BUS_PORT, 400 * 1000);
    gpio_set_function(I2C_BUS_PIN_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_BUS_PIN_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_BUS_PIN_SDA);
    gpio_pull_up(I2C_BUS_PIN_SCL);

    // Initialize Devices
    sleep_ms(100);
    oled_init();
    eeprom_init();

    printf("Pico booted up. Reading last state from EEPROM...\n");

    // 1. Immediately read and display what is *already* in the EEPROM on boot
    oled_clear();
    int x_pos = 2;
    for (int i = 0; i < 10; i++) {
        uint8_t mem_val = eeprom_read_byte(i);
        char display_char = (mem_val >= 0 && mem_val <= 9) ? ('0' + mem_val) : '-';
        oled_draw_char(x_pos, 1, display_char);
        x_pos += 12;
    }
    oled_flush();
    
    // Give you 2 seconds to see the restored state on the screen
    sleep_ms(2000); 

    // Find a smart starting point, or just start writing at index 0 
    // (If you want it to resume where it left off, you can track an index pointer in EEPROM byte 10, 
    // but for simplicity, let's start writing at index 0 with the last read value + 1)
    uint16_t write_index = 0;
    uint8_t last_val = eeprom_read_byte(0);
    uint8_t data_value = (last_val >= 1 && last_val <= 9) ? (last_val % 9) + 1 : 1;

    while (true) {
        // Write current value to EEPROM index
        eeprom_write_byte(write_index, data_value);
        printf("Wrote value %d to EEPROM address %d\n", data_value, write_index);

        // Clear and read all 10 bytes from EEPROM to update OLED
        oled_clear();
        x_pos = 2;
        for (int i = 0; i < 10; i++) {
            uint8_t mem_val = eeprom_read_byte(i);
            char display_char = (mem_val >= 0 && mem_val <= 9) ? ('0' + mem_val) : '-';
            oled_draw_char(x_pos, 1, display_char);
            x_pos += 12;
        }
        oled_flush();

        // Advance index 0 to 9
        write_index = (write_index + 1) % 10;
        data_value = (data_value % 9) + 1;

        sleep_ms(1000);
    }
}