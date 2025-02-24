//#include"main.h"
//#include"usart.h"
//#include"gpio.h"
//#include"exti.h"
//
//#define SYSTEM_CLK 80000000
//
//int  FLAG=0;
//
//int main(void)
//{	//Max clock 80 Mhz Speed
//	rcc_MSI_PLL_config();
//	rcc_SysTick_config(80000);
//    //usart_USART2_Config(SYSTEM_CLK);
//    //usart_USART2_GPIO_CONFIG();
//    gpio_LED_Config();
//    //GPIO Push-Button Config(PA12->D2)
//    gpio_PB_Config();
//    //EXTI Push-Botton Config(PA12->D2)
//    exti_PB_Config();
//
//	while(1){
//		if(FLAG){
//			FLAG=0;
//			gpio_LED_toggleGreen();
//			rcc_msDelay(200);
//			EXTI->IMR1 |= (EXTI_IMR1_IM12);
//		}
//	}
//
//}
//
//void EXTI4_IRQHandler(void){
//	//Clear Pending Interrupt
//	NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
//	EXTI->PR1 |= (EXTI_PR1_PIF12);
//	//Block Interrupt for rebound of PB
//	EXTI->IMR1 &= ~(EXTI_IMR1_IM12);
//    FLAG=1;
//}
