/*
 * Trabajo de Tesis
 *
 *  Created on: Feb 11, 2025
 *      Author: Daniel Dominguez Fragoso
 */
#include "gpio.h"

/*
 * @brief GPIO LED D13(PB3) Config
 */
void gpio_LED_Config(void){
//Enable GPIO Port B Clock
RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOBEN);
//Config in GPOM
GPIOB->MODER &= ~(GPIO_MODER_MODE3);
GPIOB->MODER |= (GPIO_MODER_MODE3_0);
GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD3);
GPIOB->PUPDR |= (GPIO_PUPDR_PUPD3_0);
GPIOB->OTYPER &= ~(GPIO_OTYPER_IDR_3);
GPIOB->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED3);
GPIOB->OSPEEDR |= (GPIO_OSPEEDR_OSPEED3_1);
}
/*
 * @brief Led toggle green
 */
void gpio_LED_toggleGreen(){
	GPIOB->ODR ^= (GPIO_ODR_OD3);
}
/*
 * @brief Led write green
 */
void gpio_LED_writeGreen(bool state){
	//Bit banding
	//BB_PA3_ODR_ADDRS= state;

	if(state){
	GPIOB->ODR |= (GPIO_ODR_OD3);
	}
	else{
	GPIOB->ODR |= ~(GPIO_ODR_OD3);
	}
}
/*
 * @brief GPIO Push-Button Config(PA12->D2)
 */
void gpio_PB_Config(void){
	//Enable GPIO port A clock
	RCC->AHB2ENR |=(RCC_AHB2ENR_GPIOAEN);
	//Enable mode Input with Internal Pull-Up
	GPIOA->MODER &= ~(GPIO_MODER_MODE12);
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD12);
	GPIOA->PUPDR |= (GPIO_PUPDR_PUPD12_0);
}
/*
 * @brief read Push-Button
 */
bool gpio_PB_Read(void){
return (bool)(GPIOA->IDR & (GPIO_IDR_ID12) );
}
/*
 * @brief ADC GPIO pins: PA1(A1->ADC1_IN6)->POT,PA3(A2->ADC1_IN8)->X Joystick,PA4(A3->ADC1_IN9)->Y joystick
 */
void gpio_ADC_config(void){
	//Enable Port A Clock
	RCC->AHB1ENR &= ~(RCC_AHB2ENR_GPIOAEN);
	RCC->AHB1ENR |= (RCC_AHB2ENR_GPIOAEN);
	//Config pins in Analog mode
	GPIOA->MODER &= ~(GPIO_MODER_MODE1);
	GPIOA->MODER &= ~(GPIO_MODER_MODE3);
	GPIOA->MODER &= ~(GPIO_MODER_MODE4);
	GPIOA->MODER |= (GPIO_MODER_MODE1);
	GPIOA->MODER |= (GPIO_MODER_MODE3);
	GPIOA->MODER |= (GPIO_MODER_MODE4);
}











