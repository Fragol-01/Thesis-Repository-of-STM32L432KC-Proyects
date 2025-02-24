/*
 * Trabajo de Tesis
 *
 *  Created on: Feb 15, 2025
 *      Author: Daniel Dominguez Fragoso
 */


#include "adc.h"

/*
 * @brief Config of ADC continuous conversion, Auto-Delay and PLLSAI1 as source clock
 */
void adc_SINGLEchannel_AutoDelayedConversionMode_continuous_Config_PLLSAI1src(ADC_SingleSelect_e channel, ADC_ChannelSampling_e sampleCH){
	//Enable ADC clock
	RCC->AHB2ENR |= (RCC_AHB2ENR_ADCEN);
	//PLLSAI1 as clock source of ADC
	RCC->CCIPR &= ~(RCC_CCIPR_ADCSEL);
	RCC->CCIPR |= (RCC_CCIPR_ADCSEL_0);
	//Disable ADC
	ADC1->CR &= ~(ADC_CR_ADEN);
	//Configured channels 6,8,9 as single-ended mode
	ADC1-> DIFSEL &= ~( (0x001A0UL << (0U)) );
	//Select "Asynchronous clock mode" as ADC clock source
	ADC1_COMMON->CCR &=~(ADC_CCR_CKMODE);
	//Select Prescalar of ADC clock source
	ADC1_COMMON->CCR &= ~(ADC_CCR_PRESC);//not divided
	//Exit the Deep-power-down mode
	ADC1->CR &= ~(ADC_CR_DEEPPWD);
	//Enable the ADC internal voltage regulator
	ADC1->CR |= (ADC_CR_ADVREGEN);
	//Wait for the startup time of the ADC voltage regulator
	adc_ADCVREG_STUP_delay();
	////ADC Calibration
	//Single-Ended Input mode calibration
	ADC1->CR &= ~(ADC_CR_ADCALDIF);
	//Calibration start
	ADC1->CR |= (ADC_CR_ADCAL);
	//Wait until calibration is stopped
	while (ADC1->CR & ADC_CR_ADCAL);
	//Right Align Mode
	ADC1->CFGR &= ~(ADC_CFGR_ALIGN);
	//Continuous Conversion Mode
	ADC1->CFGR &= ~(ADC_CFGR_CONT);
	ADC1->CFGR |= (ADC_CFGR_CONT);
	//Auto-delayed Mode
	ADC1->CFGR |= (ADC_CFGR_AUTDLY);
	//Sample time to 24.5 ADC CLK Cycles
	//Tconv= (24.5+12.5) ADC CLK Cycles = 37 ADC clock cycles = 462.5ns for F_CLK=80 MHz
	//Max Sample Frequency = 2.16MHz
	ADC1->SMPR1 &=~ (ADC_SMPR1_SMP6);
	ADC1->SMPR1 &=~ (ADC_SMPR1_SMP8);
	ADC1->SMPR1 &=~ (ADC_SMPR1_SMP9);
	ADC1->SMPR1 |= (0x3UL << sampleCH);
	//Regular channel sequence length
	ADC1->SQR1 &=~(ADC_SQR1_L);//1 conversion only
	//Assigned as the 1st in the regular conversion sequence
	ADC1->SQR1  &= ~(ADC_SQR1_SQ1);
	ADC1->SQR1  |= (channel << (6U));
	//Software Trigger
	ADC1->CFGR &= ~(ADC_CFGR_EXTEN);
	/************ADC START*******************/
    adc_START();
}
/*
 * @brief Config of ADC continuous conversion, Auto-Delay and HCLK/1 as source clock
 */
void adc_SINGLEchannel_AutoDelayedConversionMode_continuous_Config_HCLKsrc(ADC_SingleSelect_e channel, ADC_ChannelSampling_e sampleCH){
	//Enable ADC clock
	RCC->AHB2ENR |= (RCC_AHB2ENR_ADCEN);
	//Disable ADC
	ADC1->CR &= ~(ADC_CR_ADEN);
	//Configured channels 6,8,9 as single-ended mode
	ADC1-> DIFSEL &= ~( (0x001A0UL << (0U)) );
	//Select HCLK/1 as ADC clock source
	ADC1_COMMON->CCR &=~(ADC_CCR_CKMODE);
	ADC1_COMMON->CCR |= (ADC_CCR_CKMODE_0);
	//Exit the Deep-power-down mode
	ADC1->CR &= ~(ADC_CR_DEEPPWD);
	//Enable the ADC internal voltage regulator
	ADC1->CR |= (ADC_CR_ADVREGEN);
	//Wait for the startup time of the ADC voltage regulator
	adc_ADCVREG_STUP_delay();
	////ADC Calibration
	//Single-Ended Input mode calibration
	ADC1->CR &= ~(ADC_CR_ADCALDIF);
	//Calibration start
	ADC1->CR |= (ADC_CR_ADCAL);
	//Wait until calibration is stopped
	while (ADC1->CR & ADC_CR_ADCAL);
	//Right Align Mode
	ADC1->CFGR &= ~(ADC_CFGR_ALIGN);
	//Continuous Conversion Mode
	ADC1->CFGR &= ~(ADC_CFGR_CONT);
	ADC1->CFGR |= (ADC_CFGR_CONT);
	//Auto-delayed Mode
	ADC1->CFGR |= (ADC_CFGR_AUTDLY);
	//Sample time to 24.5 ADC CLK Cycles
	//Tconv= (24.5+12.5) ADC CLK Cycles = 37 ADC clock cycles = 462.5ns for F_CLK=80 MHz
	//Max Sample Frequency = 2.16MHz
	ADC1->SMPR1 &=~ (ADC_SMPR1_SMP6);
	ADC1->SMPR1 &=~ (ADC_SMPR1_SMP8);
	ADC1->SMPR1 &=~ (ADC_SMPR1_SMP9);
	ADC1->SMPR1 |= (0x3UL << sampleCH);
	//Regular channel sequence length
	ADC1->SQR1 &=~(ADC_SQR1_L);//1 conversion only
	//Assigned as the 1st in the regular conversion sequence
	ADC1->SQR1  &= ~(ADC_SQR1_SQ1);
	ADC1->SQR1  |= (channel << (6U));
	//Software Trigger
	ADC1->CFGR &= ~(ADC_CFGR_EXTEN);
	//////////////////ADC START////////////////
    adc_START();
}
/*
 * @brief ADC Multi-channel Config
 */
void adc_MULTICHANNEL_Config(void){
	//Enable ADC clock
	RCC->AHB2ENR |= (RCC_AHB2ENR_ADCEN);
	//Select HCLK/1 as ADC clock source
	ADC1_COMMON->CCR &=~(ADC_CCR_CKMODE);
	ADC1_COMMON->CCR |= (ADC_CCR_CKMODE_0);
	//Exit the Deep-power-down mode
	ADC1->CR &= ~(ADC_CR_DEEPPWD);
	//Enable the ADC internal voltage regulator
	ADC1->CR |= (ADC_CR_ADVREGEN);
	//Wait for the startup time of the ADC voltage regulator
	adc_ADCVREG_STUP_delay();
	////ADC Calibration
	//Single-Ended Input mode calibration
	ADC1->CR &= ~(ADC_CR_ADCALDIF);
	//Calibration start
	ADC1->CR |= (ADC_CR_ADCAL);
	//Wait until calibration is stopped
	while (ADC1->CR & ADC_CR_ADCAL);
	//Right Align Mode
	ADC1->CFGR &= ~(ADC_CFGR_ALIGN);
	//Single Conversion Mode
	ADC1->CFGR &= ~(ADC_CFGR_CONT);
	//Sample time to 24.5 ADC CLK Cycles
	//Tconv= (24.5+12.5) ADC CLK Cycles = 37 ADC clock cycles = 462.5ns for F_CLK=80 MHz
	//Max Sample Frequency = 2.16MHz
	ADC1->SMPR1 &=~ (ADC_SMPR1_SMP6);
	ADC1->SMPR1 &=~ (ADC_SMPR1_SMP8);
	ADC1->SMPR1 &=~ (ADC_SMPR1_SMP9);
	//ADC1->SMPR1 |= (0x3UL << ADC_SMPR1_SMP6_Pos);
	ADC1->SMPR1 |= (0x3UL << ADC_SMPR1_SMP8_Pos);
	ADC1->SMPR1 |= (0x3UL << ADC_SMPR1_SMP9_Pos);
	//Regular channel sequence length
	ADC1->SQR1 &= ~(ADC_SQR1_L);//Clear
	ADC1->SQR1 |= ( (0x1UL << (0U)) );
	//Assigned sequence order in the regular conversion
	/*ADC1->SQR1  &= ~(ADC_SQR1_SQ1);
	ADC1->SQR1  |= ((0x6UL << (6U)));*/
	ADC1->SQR1  &= ~(ADC_SQR1_SQ1);
	ADC1->SQR1  |= ((0x8UL << (6U)));
	ADC1->SQR1  &= ~(ADC_SQR1_SQ2);
	ADC1->SQR1  |= ((0x9UL << (12U)));
	//Software Trigger
	ADC1->CFGR &=~ (ADC_CFGR_EXTEN);
	/************ADC START*******************/
	//Clear the ADC ready flag(It is cleared by writing 1 to it.)
	ADC1->ISR |=(ADC_ISR_ADRDY);
	//Enable ADC
	ADC1->CR |=(ADC_CR_ADEN);
	//Wait until ADC is ready
	while (!(ADC1->CR & ADC_CR_ADEN));
	//Clear the ADC ready flag again
	ADC1->ISR |=(ADC_ISR_ADRDY);
	//Enable DMA
	ADC1-> CFGR |= (ADC_CFGR_DMAEN);
	// DMA in Circular Mode
	ADC1-> CFGR |= (ADC_CFGR_DMACFG);
	//Start the first conversion
	ADC1->CR |=(ADC_CR_ADSTART);
}
/*
 * @brief ADC DMA Multi-channel with TIM6(TRGO) Config
 */
void adc_MULTICHANNEL_TIM6trgo_Config_(void){
	//Enable ADC clock
	RCC->AHB2ENR |= (RCC_AHB2ENR_ADCEN);
	//Select HCLK/1 as ADC clock source
	ADC1_COMMON->CCR &=~(ADC_CCR_CKMODE);
	ADC1_COMMON->CCR |= (ADC_CCR_CKMODE_0);
	//Exit the Deep-power-down mode
	ADC1->CR &= ~(ADC_CR_DEEPPWD);
	//Enable the ADC internal voltage regulator
	ADC1->CR |= (ADC_CR_ADVREGEN);
	//Wait for the startup time of the ADC voltage regulator
	adc_ADCVREG_STUP_delay();
	////ADC Calibration
	//Single-Ended Input mode calibration
	ADC1->CR &= ~(ADC_CR_ADCALDIF);
	//Calibration start
	ADC1->CR |= (ADC_CR_ADCAL);
	//Wait until calibration is stopped
	while (ADC1->CR & ADC_CR_ADCAL);
	//Right Align Mode
	ADC1->CFGR &= ~(ADC_CFGR_ALIGN);
	//Single Conversion Mode
	ADC1->CFGR &= ~(ADC_CFGR_CONT);
	//Sample time to 24.5 ADC CLK Cycles
	//Tconv= (24.5+12.5) ADC CLK Cycles = 37 ADC clock cycles = 462.5ns for F_CLK=80 MHz
	//Max Sample Frequency = 2.16MHz
	ADC1->SMPR1 &=~ (ADC_SMPR1_SMP6);
	ADC1->SMPR1 &=~ (ADC_SMPR1_SMP8);
	ADC1->SMPR1 &=~ (ADC_SMPR1_SMP9);
	ADC1->SMPR1 |= (0x3UL << ADC_SMPR1_SMP6_Pos);
	ADC1->SMPR1 |= (0x3UL << ADC_SMPR1_SMP8_Pos);
	ADC1->SMPR1 |= (0x3UL << ADC_SMPR1_SMP9_Pos);
	//Regular channel sequence length
	ADC1->SQR1 &= ~(ADC_SQR1_L);//Clear
	ADC1->SQR1 |= ( (0x1UL << (0U)) );
	//Assigned sequence order in the regular conversion
	/*ADC1->SQR1  &= ~(ADC_SQR1_SQ1);
	ADC1->SQR1  |= ((0x6UL << (6U)));*/
	ADC1->SQR1  &= ~(ADC_SQR1_SQ1);
	ADC1->SQR1  |= ((0x8UL << (6U)));
	ADC1->SQR1  &= ~(ADC_SQR1_SQ2);
	ADC1->SQR1  |= ((0x9UL << (12U)));
	//Rising Trigger Edge
	ADC1->CFGR &= ~(ADC_CFGR_EXTEN);
	ADC1->CFGR |= (ADC_CFGR_EXTEN_0);
	//Select External Trigger
	ADC1->CFGR &= ~(ADC_CFGR_EXTSEL);
	ADC1->CFGR |= ( (0xDUL << (6U)) );//Event #13-->EXT13->TIM6_TRGO
	/************ADC START*******************/
	//Clear the ADC ready flag(It is cleared by writing 1 to it.)
	ADC1->ISR |=(ADC_ISR_ADRDY);
	//Enable ADC
	ADC1->CR |=(ADC_CR_ADEN);
	//Wait until ADC is ready
	while (!(ADC1->CR & ADC_CR_ADEN));
	//Clear the ADC ready flag again
	ADC1->ISR |=(ADC_ISR_ADRDY);
	//Enable DMA
	ADC1-> CFGR |= (ADC_CFGR_DMAEN);
	// DMA in Circular Mode
	ADC1-> CFGR |= (ADC_CFGR_DMACFG);
	//Start the first conversion
	ADC1->CR |=(ADC_CR_ADSTART);
}
/*
 * @brief ADC DMA Config
 */
void adc_MULTICHANNEL_DMA_Config(uint16_t *pDMAbuffer){
	//DMA1--> Channel1->ADC1
	//Enable DMA Clock
	RCC-> AHB1ENR &= ~(RCC_AHB1ENR_DMA1EN);
	RCC-> AHB1ENR |= (RCC_AHB1ENR_DMA1EN);
	//Clear DMA Flags
	DMA1->IFCR |= (DMA_IFCR_CGIF1);
	//Peripheral address (src)--> ADC_DR
	DMA1_Channel1->CPAR= (uint32_t)(&(ADC1->DR));
	//Memory address (Destination is uint16_t adc_samples[3])
	DMA1_Channel1->CMAR =(uint32_t)(pDMAbuffer);
	// Declare the number of transfer
	DMA1_Channel1->CNDTR=2;
	//Clear CCR Register
	DMA1_Channel1->CCR =0;
	//Enable Transfer Complete Interrupt
	DMA1_Channel1->CCR |= (DMA_CCR_TCIE);
	NVIC_SetPriority(DMA1_Channel1_IRQn,0);
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
	//Transfer Direction is Perph to Mem
	DMA1_Channel1->CCR &= ~(DMA_CCR_DIR);
	//Enable Circular Mode
	DMA1_Channel1->CCR |= (DMA_CCR_CIRC);
	//Disable Peripheral increment mode
	DMA1_Channel1->CCR &= ~(DMA_CCR_PINC);
	//Enable Memory increment mode
	DMA1_Channel1->CCR |= (DMA_CCR_MINC);
	//Peripheral size word is 16 > 12bit of ADC data word
	DMA1_Channel1->CCR |= (DMA_CCR_PSIZE_0);
	//Memory size word is 16 > 12bit of ADC data word
	DMA1_Channel1->CCR |= (DMA_CCR_MSIZE_0);
	//Set priority level to VERY HIGH
	DMA1_Channel1->CCR |= (DMA_CCR_PL);
	//Enable DMA
	DMA1_Channel1->CCR |= (DMA_CCR_EN);
}
/*
 * @brief ADC Start
 */
void adc_START(void){
	//Clear the ADC ready flag(It is cleared by writing 1 to it.)
	ADC1->ISR |=(ADC_ISR_ADRDY);
	//Enable ADC
	ADC1->CR |=(ADC_CR_ADEN);
	//Wait until ADC is ready
	while (!(ADC1->CR & ADC_CR_ADEN));
	//Clear the ADC ready flag again
	ADC1->ISR |=(ADC_ISR_ADRDY);
	//Start the first conversion
	ADC1->CR |=(ADC_CR_ADSTART);
}
/*
 * @brief ADC Stop
 */
void adc_STOP(void){
	while( (ADC1->CR & (ADC_CR_ADSTART | ADC_CR_JADSTART)) ){}
	ADC1->CR |= (ADC_CR_ADDIS);
	while( (ADC1-> CR & (ADC_CR_ADEN)) ){}
}
/*
 * @brief ADC Poll of end of conversion
 */
bool adc_PollEOC(uint32_t msTimeout){
	uint32_t startTicks= rcc_msGetTick();
	while(! (ADC1-> ISR & ADC_ISR_EOC) ){
		if( (rcc_msGetTick()- startTicks) > msTimeout){
			return false;
		}
	}
	return true;
}
/*
 * @brief ADC Read Value of Conversion of 12 bits
 */
uint16_t adc_READ_Value(){
	return (ADC1->DR & 0xFFF);
}
/*
 * @brief delay for ADC voltage regulator start-up time(20us)
 * A 80Mhz->CM=12.5ns->CM x 1600=20us-> TADCVREG_STUP_MAX=25us>20us
 */
void adc_ADCVREG_STUP_delay(void)
{
	volatile uint32_t i;
	for (i=0;i<2000;i++) {}
}
/*
 * @brief Enable/Disable ADC Interrupt -EOC
 */
void adc_EOCIE_ENABLE(){
	//Enable Interrupt
	ADC1-> IER |= (ADC_IER_EOCIE);
	//Enable ADC NVIC Interrupt
	NVIC_EnableIRQ(ADC1_IRQn);
	NVIC_SetPriority(ADC1_IRQn,0);
}
void adc_EOCIE_DISABLE(){
	//Disable Interrupt
	ADC1-> IER &= ~(ADC_IER_EOCIE);
	//Enable ADC NVIC Interrupt
	NVIC_DisableIRQ(ADC1_IRQn);
}
/*
 * @brief ADC Analog Watch-Dog Config
 * @param threshold Lower/Higher--> 0/4095
 */
void adc_SingleAWD_Config(uint8_t channel,uint16_t Hthreshold,uint16_t Lthreshol){
	//Set threshold values
	ADC1->TR1= 0; //CLEAR
	ADC1->TR1 |= ( (Hthreshold << ADC_TR1_HT1_Pos) | (Lthreshol << ADC_TR1_LT1_Pos) );// range between 3000--2000
	//Select the AWD channel
	ADC1-> CFGR &= ~(ADC_CFGR_AWD1CH);
	ADC1-> CFGR |= (channel << (ADC_CFGR_AWD1CH_Pos));
	//Enable AWD1 in one regular channel
	ADC1-> CFGR |= (ADC_CFGR_AWD1EN);
	ADC1-> CFGR |= (ADC_CFGR_AWD1SGL);
	ADC1-> CFGR &= ~(ADC_CFGR_JAWD1EN);
	//Enable AWD interrupt---> AWDx (x=1,2,3) flag is cleared by software by writing 1 to it.
	ADC1-> IER |= (ADC_IER_AWD1IE);
	NVIC_EnableIRQ(ADC1_IRQn);
	//Enable the AWD .
    ADC1-> CFGR|= (ADC_CFGR_AWD1EN);
}


