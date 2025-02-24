///*
//* Trabajo de Tesis
//*
//*  Created on: Feb 18, 2025
//*      Author: Daniel Dominguez Fragoso
//*/
//#include"main.h"
//#include"usart.h"
//#include"gpio.h"
//#include"exti.h"
//
//#define SYSTEM_CLK  80000000
//#define PLLSAI1_CLK 80000000
//
////VARIABLES
//int FLAG=0;
//
//
//
//int main(void)
//{	//Max clock 80 Mhz Speed
//	rcc_MSI_config();
//	rcc_SysTick_config(80000);
//	//USART2 Config
//	usart_USART2_Config(SYSTEM_CLK);
//	usart_USART2_GPIO_CONFIG();
//	//LED Config
//	gpio_LED_Config();
//	//PB Config
//	gpio_PB_Config();
//	//EXTI Config
//	exti_PB_Config();
//
//	while(1){
//		if(FLAG){
//			printf("INTERRUPCION...\n\r");
//			gpio_LED_toggleGreen();
//			rcc_msDelay(200);
//			FLAG=0;
//		}
//   }
//
//}
//
//void EXTI15_10_IRQHandler(void){
//	//Clear Pending Interrupt
//	NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
//	EXTI->PR1 |= (EXTI_PR1_PIF12);
//	FLAG=1;
//
//
//}
//
