/*
 * Trabajo de Tesis
 *
 *  Created on: Feb 17, 2025
 *      Author: Daniel Dominguez Fragoso
 */
#include"main.h"
#include"usart.h"
#include"gpio.h"
#include"adc.h"

#define SYSTEM_CLK  80000000
#define PLLSAI1_CLK 80000000

//VARIABLES
volatile int EOCflag=0;
volatile uint16_t ADC_VAL= 0;



int main(void)
{	//Max clock 80 Mhz Speed
	rcc_MSI_PLL_config();
	rcc_MSI_PLLSAL1R_config();
	rcc_SysTick_config(80000);
	//USART2 Config
	usart_USART2_Config(SYSTEM_CLK);
	usart_USART2_GPIO_CONFIG();
	//ADC Config
	gpio_ADC_config();
	//adc_SingleAWD_Config(ADC_ChannelSampling_JoysticX, 3000, 2000);
	adc_SINGLEchannel_AutoDelayedConversionMode_continuous_Config_PLLSAI1src(ADC_SingleSelect_JoysticX, ADC_ChannelSampling_JoysticX);
	adc_EOCIE_ENABLE();

	while(1){
		if(EOCflag){
			printf("The ADC value is %u\n\r", (int)ADC_VAL);
			EOCflag=0;
		}
		else{
			printf("ADC Value read failed\n\r");
		}
	rcc_msDelay(300);
	}

}

void ADC1_IRQHandler(void){
	if( (ADC1->ISR & (ADC_ISR_EOC) ) ){
		EOCflag=1;
		NVIC_ClearPendingIRQ(ADC1_IRQn);
		//Clear the end of conversion flag-->ADC1->ISR |= (ADC_ISR_EOC) or:
		ADC_VAL=adc_READ_Value();
	}
}
