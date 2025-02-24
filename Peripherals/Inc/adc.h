/*
 * Trabajo de Tesis
 *
 *  Created on: Feb 15, 2025
 *      Author: Daniel Dominguez Fragoso
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "main.h"

//ADC Channel Sampling select
typedef enum ADC_ChannelSampling_TAG
{
	ADC_ChannelSampling_Potentiometer= ADC_SMPR1_SMP6_Pos,
	ADC_ChannelSampling_JoysticX= ADC_SMPR1_SMP8_Pos,
	ADC_ChannelSampling_JoysticY= ADC_SMPR1_SMP9_Pos



}ADC_ChannelSampling_e;
//ADC Channel select
typedef enum ADC_SingleSelect_TAG
{
	ADC_SingleSelect_Potentiometer=6,
	ADC_SingleSelect_JoysticX=8,
	ADC_SingleSelect_JoysticY=9
}ADC_SingleSelect_e;


/*
 * @brief Config of ADC continuous conversion, Auto-Delay and PLLSAI1 as source clock
 */
void adc_SINGLEchannel_AutoDelayedConversionMode_continuous_Config_PLLSAI1src(ADC_SingleSelect_e channel , ADC_ChannelSampling_e sampleCH);
/*
 * @brief Config of ADC continuous conversion, Auto-Delay and HCLK/1 as source clock
 */
void adc_SINGLEchannel_AutoDelayedConversionMode_continuous_Config_HCLKsrc(ADC_SingleSelect_e channel, ADC_ChannelSampling_e sampleCH);
/*
 * @brief ADC Multi-channel Config
 */
void adc_MULTICHANNEL_Config(void);
/*
 * @brief ADC DMA Multi-channel with TIM6(TRGO) Config
 */
void adc_MULTICHANNEL_TIM6trgo_Config_(void);
/*
 * @brief ADC DMA Config
 */
void adc_MULTICHANNEL_DMA_Config(uint16_t *pDMAbuffer);
/*
 * @brief ADC Start
 */
void adc_START(void);
/*
 * @brief ADC Stop
 */
void adc_STOP(void);
/*
 * @brief ADC Poll of end of conversion
 */
bool adc_PollEOC(uint32_t msTimeout);
/*
 * @brief ADC Read Value of Conversion of 12 bits
 */
uint16_t adc_READ_Value();
/*
 * @brief delay for ADC voltage regulator start-up time(20us)
 * A 80Mhz->CM=12.5ns->CM x 1600=20us-> TADCVREG_STUP_MAX=20us
 */
void adc_ADCVREG_STUP_delay(void);
/*
 * @brief Enable/Disable ADC Interrupt -EOC
 */
void adc_EOCIE_ENABLE();
void adc_EOCIE_DISABLE();
/*
 * @brief ADC Analog Watch-Dog Config
 * @param threshold Lower/Higher--> 0/4095
 */
void adc_SingleAWD_Config(uint8_t channel,uint16_t Hthreshold,uint16_t Lthreshol);






#endif /* INC_ADC_H_ */
