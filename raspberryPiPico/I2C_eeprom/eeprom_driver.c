#include "hardware/i2c.h"
#include "pico/stdlib.h"

#define I2C_PORT        i2c0
#define EEPROM_BASE_ADDR 0x50

void eeprom_init() {
    // I2C bus is initialized globally in main, but put any startup checks here if needed
}

void eeprom_write_byte(uint16_t mem_address, uint8_t data) {
    uint8_t device_addr = EEPROM_BASE_ADDR | ((mem_address >> 8) & 0x07);
    uint8_t buf[2] = { (uint8_t)(mem_address & 0xFF), data };
    i2c_write_blocking(I2C_PORT, device_addr, buf, 2, false);
    sleep_ms(5); // AT24C16 internal write cycle delay (~5ms)
}

uint8_t eeprom_read_byte(uint16_t mem_address) {
    uint8_t device_addr = EEPROM_BASE_ADDR | ((mem_address >> 8) & 0x07);
    uint8_t mem_addr_low = (uint8_t)(mem_address & 0xFF);
    uint8_t read_data = 0;

    i2c_write_blocking(I2C_PORT, device_addr, &mem_addr_low, 1, true);
    i2c_read_blocking(I2C_PORT, device_addr, &read_data, 1, false);
    
    return read_data;
}