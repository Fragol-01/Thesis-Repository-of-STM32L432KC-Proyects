/*
 * Trabajo de Tesis
 *
 *  Created on: Feb 11, 2025
 *      Author: Daniel Dominguez Fragoso
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "main.h"
//BIT-BANDING
#define BB_BASE_ADDRS    0x42000000
#define GPIOA_ODR_OFFSET 0x00000414
#define BB_PIN_3         3
#define BB_PA3_ODR_ADDRS *(uint32_t *)(BB_BASE_ADDRS + GPIOA_ODR_OFFSET*32 + BB_PIN_3*4 )

/*
 * @brief GPIO LED D13(PB3) Config
 */
void gpio_LED_Config(void);
/*
 * @brief Led toggle green
 */
void gpio_LED_toggleGreen();
/*
 * @brief Led write green
 */
void gpio_LED_writeGreen(bool state);
/*
 * @brief GPIO Push-Button Config(PA12->D2)
 */
void gpio_PB_Config(void);
/*
 * @brief read Push-Button
 */
bool gpio_PB_Read(void);
/*
 * @brief ADC GPIO pins: PA1(A1->ADC1_IN6)->POT,PA3(A2->ADC1_IN8)->X Joystick,PA4(A3->ADC1_IN9)->Y joystick
 */
void gpio_ADC_config(void);




#endif /* INC_GPIO_H_ */
