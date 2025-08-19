#include "i2c-lcd.h"

static I2C_HandleTypeDef *_hi2c;
static uint8_t backlight_state = LCD_BACKLIGHT;

static void lcd_send_internal(uint8_t data, uint8_t flags) {
    HAL_StatusTypeDef res;
    for (uint8_t i = 0; i < 2; i++) {
        uint8_t nibble = (i == 0) ? (data & 0xF0) : ((data << 4) & 0xF0);
        uint8_t data_t[4];

        // Prepare the 4 bytes for proper Enable pulse
        data_t[0] = nibble | flags | backlight_state | 0x04; // EN=1
        data_t[1] = nibble | flags | backlight_state | 0x04; // EN=1 (hold)
        data_t[2] = nibble | flags | backlight_state;        // EN=0
        data_t[3] = nibble | flags | backlight_state;        // EN=0 (hold)

        res = HAL_I2C_Master_Transmit(_hi2c, LCD_I2C_ADDR, data_t, 4, HAL_MAX_DELAY);
        HAL_Delay(2); // Increased delay for LCD processing
    }
}

void lcd_send_cmd(char cmd) {
    lcd_send_internal(cmd, 0x00);
}

void lcd_send_data(char data) {
    lcd_send_internal(data, 0x01); // RS = 1
}

void lcd_clear(void) {
    lcd_send_cmd(LCD_CLR);
    HAL_Delay(5); // Increased delay for clear command
}

void lcd_put_cur(uint8_t row, uint8_t col) {
    uint8_t addr = (row == 0) ? 0x80 : 0xC0;
    addr += col;
    lcd_send_cmd(addr);
}

void lcd_send_string(char *str) {
    while (*str) {
        lcd_send_data(*str++);
    }
}

void lcd_init(I2C_HandleTypeDef *hi2c) {
    _hi2c = hi2c;
    HAL_Delay(50); // wait for LCD to power up

    // Proper initialization sequence for I2C LCD
    // Send initial 8-bit commands to get into known state
    lcd_send_cmd(0x33); // Initialize
    HAL_Delay(5);
    lcd_send_cmd(0x32); // Initialize
    HAL_Delay(5);
    lcd_send_cmd(0x28); // 4-bit mode, 2 lines, 5x8 font
    HAL_Delay(5);
    lcd_send_cmd(0x0C); // Display on, cursor off, blink off
    HAL_Delay(5);
    lcd_send_cmd(0x06); // Entry mode: increment cursor, no shift
    HAL_Delay(5);
    lcd_clear();        // Clear display
}
