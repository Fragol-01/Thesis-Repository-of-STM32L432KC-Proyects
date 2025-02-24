///*
// * Trabajo de Tesis
// *
// *  Created on: Feb 17, 2025
// *      Author: Daniel Dominguez Fragoso
// */
//#include"main.h"
//#include"usart.h"
//#include"gpio.h"
//#include"adc.h"
//
//#define SYSTEM_CLK  80000000
//#define PLLSAI1_CLK 80000000
//
////VARIABLES
//int FLAG=0;
//uint16_t ADC_VAL= 0;
//uint16_t ADC_ARRAY[2]= {0};
//
//
//int main(void)
//{	//Max clock 80 Mhz Speed
//	rcc_MSI_PLL_config();
//	//rcc_MSI_PLLSAL1R_config();
//	rcc_SysTick_config(80000);
//	//USART2 Config
//	usart_USART2_Config(SYSTEM_CLK);
//	usart_USART2_GPIO_CONFIG();
//	//LED Config
//	gpio_LED_Config();
//	//ADC Config
//	gpio_ADC_config();
//	adc_MULTICHANNEL_Config();
//	adc_MULTICHANNEL_DMA_Config(ADC_ARRAY);
//
//	while(1){
//		if(FLAG){
//			for(int i=0;i<2;i++){
//				printf("The ADC Channel[%u] Sensor is %u\n\r",i+1 ,(int)ADC_ARRAY[i]);
//			}
//			FLAG=0;
//			//Signal of the end of ADC conversion
//			gpio_LED_toggleGreen();
//		}
//		else{
//			printf("DMA failed\n\r");
//		}
//		printf("-------------------------------\n\n\r");
//		rcc_msDelay(300);
//	}
//}
//
//
////DMA Transfer Complete Interrupt
//void DMA1_Channel1_IRQHandler(void){
//	if( (DMA1->ISR & (DMA_ISR_TCIF1))){
//		//Clear Interrupt
//		NVIC_ClearPendingIRQ(DMA1_Channel1_IRQn);
//		DMA1->IFCR |= (DMA_IFCR_CTCIF1);
//		adc_START();
//		FLAG=1;
//	}
//}
