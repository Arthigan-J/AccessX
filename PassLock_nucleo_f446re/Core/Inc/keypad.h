/*
 * keypad.h
 *
 * Created on: Aug 17, 2025
 * Author: AJ
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

#include "stm32f4xx_hal.h"

// GPIO Pin Definitions (Updated to match IOC configuration)
#define KEYPAD_ROW1_Port GPIOA
#define KEYPAD_ROW1_Pin GPIO_PIN_6
#define KEYPAD_ROW2_Port GPIOA
#define KEYPAD_ROW2_Pin GPIO_PIN_7
#define KEYPAD_ROW3_Port GPIOB
#define KEYPAD_ROW3_Pin GPIO_PIN_6
#define KEYPAD_ROW4_Port GPIOC
#define KEYPAD_ROW4_Pin GPIO_PIN_7

#define KEYPAD_COL1_Port GPIOA
#define KEYPAD_COL1_Pin GPIO_PIN_9
#define KEYPAD_COL2_Port GPIOA
#define KEYPAD_COL2_Pin GPIO_PIN_8
#define KEYPAD_COL3_Port GPIOB
#define KEYPAD_COL3_Pin GPIO_PIN_10
#define KEYPAD_COL4_Port GPIOB
#define KEYPAD_COL4_Pin GPIO_PIN_4


// Function prototypes
void keypad_init(void);
char keypad_scan(void);
char keypad_get_key(void);

#endif /* INC_KEYPAD_H_ */
