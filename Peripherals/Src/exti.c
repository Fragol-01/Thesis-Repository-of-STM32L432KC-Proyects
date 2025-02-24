/*
 * Trabajo de Tesis
 *
 *  Created on: Feb 13, 2025
 *      Author: Daniel Dominguez Fragoso
 */

#include "exti.h"

/*
 * @brief EXTI Push-Botton Config(PA12->D2)
 */
void exti_PB_Config(void){
	//Enable GPIO port A clock
	RCC->AHB2ENR |=(RCC_AHB2ENR_GPIOAEN);
	//Enable SYSCFG port clock
	RCC->APB2ENR |=(RCC_APB2ENR_SYSCFGEN);
	//Enable mode Input with Internal Pull-Up
	GPIOA->MODER &= ~(GPIO_MODER_MODE12);
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD12);
	GPIOA->PUPDR |= (GPIO_PUPDR_PUPD12_0);
	// Select the source input for the EXTI12 external interrupt(PA12)
    SYSCFG->EXTICR[3] &= ~(SYSCFG_EXTICR4_EXTI12);
    //Unblock Interrupt
    EXTI->IMR1 |= (EXTI_IMR1_IM12);
    //Enable in Rising edge
    EXTI-> RTSR1 |= (EXTI_RTSR1_RT12);
    //Disable Falling edge
    EXTI-> FTSR1 &= ~(EXTI_FTSR1_FT12);
    //Set priority
    NVIC_SetPriority(EXTI15_10_IRQn, 15);
    //Enable the NVIC
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}
