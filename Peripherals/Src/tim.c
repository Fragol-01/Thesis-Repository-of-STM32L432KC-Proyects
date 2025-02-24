/*
 * Trabajo de Tesis
 *
 *  Created on: Feb 20, 2025
 *      Author: Daniel Dominguez Fragoso
 */


#include "tim.h"

/*
 * @brief TIM3 ADC TRGO timer with interrupt Config
 */
void tim_TIM6_with_INTERRPUT_Config(uint16_t msPeriod){
	// Disable temporally the timer to configure
	TIM6->CR1 &= ~(TIM_CR1_CEN);
	//Enable TIM6 Clock
	RCC-> APB1ENR1 &= ~(RCC_APB1ENR1_TIM6EN);
	RCC-> APB1ENR1 |= (RCC_APB1ENR1_TIM6EN);
	//********This timer is only upcounter*******//
	//CLEAR TIMx_CR1 Register
	TIM6-> CR1 = 0;//DEFAULT
	//Disable status bit Remapping
//	TIM6-> CR1 &= ~(TIM_CR1_UIFREMAP);
	//Disable AutoReload
//	TIM6-> CR1 &= ~(TIM_CR1_ARPE);
	//Request source only counter overflow/underflow
//	TIM6-> CR1 &= ~(TIM_CR1_URS);
	//Update Event enabled
//	TIM6-> CR1 &= ~(TIM_CR1_UDIS);
	//Disable One-Pulse Mode
//	TIM6-> CR1 &= ~(TIM_CR1_OPM);//Periodic
	//Mode--> TRGO
	TIM6->CR2 &= ~(TIM_CR2_MMS);
	TIM6->CR2 |=  (TIM_CR2_MMS_1);//The update event is selected as a trigger output (TRGO)
	//Set TIM6 Prescaler--> CK_CNT= (Fck_psc/(PSC[15:0]+1))
	TIM6-> PSC &= ~(TIM_PSC_PSC);
	TIM6-> PSC = (8000-1);// 10KHz
	//Period
	//Set Auto_reload Register
	TIM6-> ARR &= ~(TIM_ARR_ARR);
	TIM6-> ARR |=  ((msPeriod*10)-1); //MAX-->6553 ms
	//Update Register on event
	TIM6->EGR=1;
	//Clear TIMx_DIER Register
	TIM6-> DIER = 0;
	//Enable Update interrupt
	TIM6-> DIER |= (TIM_DIER_UIE);
	//Enable Update DMA Request
	TIM6-> DIER |= (TIM_DIER_UDE);
	//Enable NVIC Interrupt
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
	NVIC_SetPriority(TIM6_DAC_IRQn,0);

	TIM6-> CR1 |= (TIM_CR1_CEN);
}

/*
 * @brief TIM3 ADC TRGO timer Config
 */
void tim_TIM6_Config(uint16_t msPeriod){
	// Disable temporally the timer to configure
	TIM6->CR1 &= ~(TIM_CR1_CEN);
	//Enable TIM6 Clock
	RCC-> APB1ENR1 &= ~(RCC_APB1ENR1_TIM6EN);
	RCC-> APB1ENR1 |= (RCC_APB1ENR1_TIM6EN);
	//********This timer is only upcounter*******//
	//CLEAR TIMx_CR1 Register
	TIM6-> CR1 = 0;//DEFAULT
	//Disable status bit Remapping
//	TIM6-> CR1 &= ~(TIM_CR1_UIFREMAP);
	//Disable AutoReload
//	TIM6-> CR1 &= ~(TIM_CR1_ARPE);
	//Request source only counter overflow/underflow
//	TIM6-> CR1 &= ~(TIM_CR1_URS);
	//Update Event enabled
//	TIM6-> CR1 &= ~(TIM_CR1_UDIS);
	//Disable One-Pulse Mode
//	TIM6-> CR1 &= ~(TIM_CR1_OPM);//Periodic
	//Mode--> TRGO
	TIM6->CR2 &= ~(TIM_CR2_MMS);
	TIM6->CR2 |=  (TIM_CR2_MMS_1);//The update event is selected as a trigger output (TRGO)
	//Set TIM6 Prescaler--> CK_CNT= (Fck_psc/(PSC[15:0]+1))
	TIM6-> PSC &= ~(TIM_PSC_PSC);
	TIM6-> PSC = (8000-1);// 10KHz
	//Period
	//Set Auto_reload Register
	TIM6-> ARR &= ~(TIM_ARR_ARR);
	TIM6-> ARR |=  ((msPeriod*10)-1); //MAX-->6553 ms
	//Update Register on event
	TIM6->EGR=1;
	//Enable Counter
	TIM6-> CR1 |= (TIM_CR1_CEN);
}

/*
 * @brief TIM1 ADC AWD timer Config
 */
void tim_TIM1_AWD_Config(uint16_t msPeriod){
	// Disable temporally the timer to configure
	TIM1->CR1 &= ~(TIM_CR1_CEN);
	//Enable TIM1 Clock
	RCC-> APB2ENR &= ~(RCC_APB2ENR_TIM1EN);
	RCC-> APB2ENR |= (RCC_APB2ENR_TIM1EN);
	//Set in upcounter mode
	TIM1->CR1 &= ~(TIM_CR1_DIR);
	//CLEAR TIMx_CR1 Register
	TIM6-> CR1 = 0;//DEFAULT
	//Disable status bit Remapping
//	TIM1-> CR1 &= ~(TIM_CR1_UIFREMAP);
	//Disable AutoReload
//	TIM1-> CR1 &= ~(TIM_CR1_ARPE);
	//Request source only counter overflow/underflow
//	TIM1-> CR1 &= ~(TIM_CR1_URS);
	//Update Event enabled
//	TIM1-> CR1 &= ~(TIM_CR1_UDIS);
	//Disable One-Pulse Mode
//	TIM1-> CR1 &= ~(TIM_CR1_OPM);//Periodic
	//Mode--> TRGO
	TIM1->CR2 &= ~(TIM_CR2_MMS);
	TIM1->CR2 |=  (TIM_CR2_MMS_1);//The update event is selected as a trigger output (TRGO)
	//Set TIM6 Prescaler--> CK_CNT= (Fck_psc/(PSC[15:0]+1))
	TIM1-> PSC &= ~(TIM_PSC_PSC);
	TIM1-> PSC = (8000-1);// 10KHz
	//Period
	//Set Auto_reload Register
	TIM1-> ARR &= ~(TIM_ARR_ARR);
	TIM1-> ARR |=  ((msPeriod*10)-1); //MAX-->6553 ms
	//Update Register on event
	TIM1->EGR=1;
	//Enable Counter
	TIM1-> CR1 |= (TIM_CR1_CEN);
	//TIM1_ETR source is selected with the ETR_ADC3_RMP and ETR_ADC1_RMP bit field in TIM1_OR1 register
	TIM1-> OR2 &= ~(TIM1_OR2_ETRSEL);
	//TIM1_ETR is connected to ADC1 AWD1
	TIM1-> OR1 &= ~(TIM1_OR1_ETR_ADC1_RMP);
	TIM1-> OR1 |= (TIM1_OR1_ETR_ADC1_RMP_0);

}
