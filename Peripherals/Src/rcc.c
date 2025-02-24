/*
 * Trabajo de Tesis
 *
 *  Created on: Feb 8, 2025
 *      Author: Daniel Dominguez Fragoso
 */

#include"rcc.h"

static __IO uint32_t msTicks=0;

/*
 *  @brief MSI MAX SPEDD(80 Mhz) Config
 */
void rcc_MSI_PLL_config(void){
	/*
	 * MSI config Parameters--> STM32L432KC Clock Tree
	 * MSI= 4 Mhz
	 * PLLM= 1
	 * N= 40
	 * R= 2
	 * ---> SYSTEM CLOCK = 80 MHz
	 * AHB Presc=1
	 * HCLK=80 MHz
	 * Cortex Prescalar=1
	 * APB1 Presc=1 --> 80 MHz Pph Clocks, 80 Mhz Tim Clocks
	 * APB2 Presc=1 --> 80 MHz Pph Clocks, 80 Mhz Tim Clocks
	 */

	////MSI Configuration
	//Active MSI PLL Mode
	//(MSI ON by default)
	RCC->CR |= (RCC_CR_MSIPLLEN);

	////PLL Configuration
	//Disable PLL
	RCC->CR &= ~(RCC_CR_PLLON);
	//Wait for PLL Ready is cleared
	while((RCC->CR & RCC_CR_PLLRDY ));
	//Select MSI as PLL clock source
	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLSRC);
	RCC->PLLCFGR |= (RCC_PLLCFGR_PLLSRC_MSI);
	//PLLM=1
	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM);
	//PLLN=40
	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLN);
	RCC->PLLCFGR |= (0x28UL << (8U));
	//PLLR
	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLR);
	//Enable PLL
	RCC->CR |= (RCC_CR_PLLON);
	//Enable PLLCLK output(R)
	RCC->PLLCFGR |= (RCC_PLLCFGR_PLLREN);
	//Wait for PLL Ready is set
	while(!(RCC->CR & RCC_CR_PLLRDY ));
	//Flash Latency and prefetch
	FLASH->ACR &= ~(FLASH_ACR_LATENCY);
	FLASH->ACR |= (0x4UL << (0U));
	//PLL as clock source of SYSCLK
	RCC->CFGR &= ~(RCC_CFGR_SW_Msk);
	RCC->CFGR |= (RCC_CFGR_SW_Msk);
	////Wait for clock change be stable
	while(!(RCC->CFGR & (0x3UL << (2U)) ));
	//Clear prescalers
	RCC->CFGR &= ~(RCC_CFGR_PPRE1);
	RCC->CFGR &= ~(RCC_CFGR_PPRE2);
	RCC->CFGR &= ~(RCC_CFGR_HPRE);
}
/*
 * @brief MSI_PLLSAL1R for ADC (80 Mhz) Config
 */
void rcc_MSI_PLLSAL1R_config(void){
	/*
	 * MSI config Parameters--> STM32L432KC Clock Tree
	 * MSI= 4Mhz
	 * PLLM= 1
	 * N= 40
	 * R= 2
	 * ---> PLLSAL1R = 80 Mhz
	 * AHB Presc=1
	 * HCLK=80 MHz
	 * Cortex Prescalar=1
	 * APB1 Presc=1 --> 80 MHz Pph Clocks, 80 Mhz Tim Clocks
	 * APB2 Presc=1 --> 80 MHz Pph Clocks, 80 Mhz Tim Clocks
	 */
	////MSI Configuration
	//Active MSI PLL Mode
	//(MSI ON by default)
	RCC->CR |= (RCC_CR_MSIPLLEN);
	RCC->CCIPR &= ~RCC_CCIPR_SAI1SEL;
	RCC->APB2ENR |= RCC_APB2ENR_SAI1EN;
	////PLL Configuration
	//Disable PLLSAL1
	RCC->CR &= ~(RCC_CR_PLLSAI1ON);
	//Wait for PLLSAL1 Ready is cleared
	while((RCC->CR & RCC_CR_PLLSAI1RDY ));
	//Select MSI as PLL clock source
	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLSRC);
	RCC->PLLCFGR |= (RCC_PLLCFGR_PLLSRC_MSI);
	//PLLM=1
	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM);
	//PLLSAI_N=40
	RCC->PLLSAI1CFGR &= ~(RCC_PLLSAI1CFGR_PLLSAI1N);
	RCC->PLLSAI1CFGR |= (0x28UL << (8U));
	//PLLSAI1_R
	RCC->PLLSAI1CFGR &= ~(RCC_PLLSAI1CFGR_PLLSAI1R);
	//Enable PLLSAI1
	RCC->CR |=  (RCC_CR_PLLSAI1ON);
	//Enable PLLSAI1 output(R)
	RCC->PLLSAI1CFGR |= (RCC_PLLSAI1CFGR_PLLSAI1REN);
	//Wait for PLLSAI1 Ready is set
	while(!(RCC->CR & RCC_CR_PLLSAI1RDY ));
}
/*
 * @brief SysTick Config
 */
void rcc_SysTick_config(uint32_t tick){
	//Reset Control Register
	SysTick->CTRL =0;
	//Set the reload value
	SysTick->LOAD =tick-1;
	//Enable SysTick Interrupt
	NVIC_EnableIRQ(SysTick_IRQn);
	//Set the priority
	NVIC_SetPriority(SysTick_IRQn,0);
	//Reset SysTick Value to 0
	SysTick->VAL =0;
	//Enable SysTick from Control Register
	SysTick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk);
	SysTick->CTRL |= (SysTick_CTRL_TICKINT_Msk);
	SysTick->CTRL |= (SysTick_CTRL_ENABLE_Msk);
}
/*
 * @brief increment ms Tick
 */
void rcc_msIncTick(void){
	msTicks++;
}
/*
 * @brief get increment ms Tick
 */
uint32_t rcc_msGetTick(void){

	return msTicks;
}
/*
 * @brief ms delay
 */
void rcc_msDelay(uint32_t msTime){
	uint32_t startTicks=rcc_msGetTick();
	while( (rcc_msGetTick()-startTicks)<msTime);
}
/*
 * @brief SysTick interrupt Callback
 */
void SysTick_Handler(void){
	NVIC_ClearPendingIRQ(SysTick_IRQn);
	rcc_msIncTick();
}
