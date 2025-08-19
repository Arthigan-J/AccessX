/*
 * keypad.c
 *
 *  Created on: Aug 17, 2025
 *      Author: AJ
 */


#include "keypad.h"

// Keypad layout - modify this to match your specific keypad
static const char keypad_layout[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Row pins array for easier iteration
static GPIO_TypeDef* row_ports[4] = {
    KEYPAD_ROW1_Port, KEYPAD_ROW2_Port, KEYPAD_ROW3_Port, KEYPAD_ROW4_Port
};

static uint16_t row_pins[4] = {
    KEYPAD_ROW1_Pin, KEYPAD_ROW2_Pin, KEYPAD_ROW3_Pin, KEYPAD_ROW4_Pin
};

// Column pins array for easier iteration
static GPIO_TypeDef* col_ports[4] = {
    KEYPAD_COL1_Port, KEYPAD_COL2_Port, KEYPAD_COL3_Port, KEYPAD_COL4_Port
};

static uint16_t col_pins[4] = {
    KEYPAD_COL1_Pin, KEYPAD_COL2_Pin, KEYPAD_COL3_Pin, KEYPAD_COL4_Pin
};

void keypad_init(void) {
    // Set all rows to HIGH (default state)
    for (int i = 0; i < 4; i++) {
        HAL_GPIO_WritePin(row_ports[i], row_pins[i], GPIO_PIN_SET);
    }
}

char keypad_scan(void) {
    // Scan each row
    for (int row = 0; row < 4; row++) {
        // Set current row LOW
        HAL_GPIO_WritePin(row_ports[row], row_pins[row], GPIO_PIN_RESET);

        // Small delay to allow signal to settle
        HAL_Delay(1);

        // Check each column
        for (int col = 0; col < 4; col++) {
            // If column pin is LOW, a key is pressed (pull-up resistor makes it normally HIGH)
            if (HAL_GPIO_ReadPin(col_ports[col], col_pins[col]) == GPIO_PIN_RESET) {
                // Set row back to HIGH before returning
                HAL_GPIO_WritePin(row_ports[row], row_pins[row], GPIO_PIN_SET);

                // Return the corresponding key
                return keypad_layout[row][col];
            }
        }

        // Set row back to HIGH
        HAL_GPIO_WritePin(row_ports[row], row_pins[row], GPIO_PIN_SET);
    }

    // No key pressed
    return '\0';
}

char keypad_get_key(void) {
    char key = '\0';
    static char last_key = '\0';

    key = keypad_scan();

    // Simple debouncing - only return key if it's different from last scan
    if (key != '\0' && key != last_key) {
        last_key = key;
        HAL_Delay(50); // Debounce delay
        return key;
    } else if (key == '\0') {
        last_key = '\0';
    }

    return '\0';
}
