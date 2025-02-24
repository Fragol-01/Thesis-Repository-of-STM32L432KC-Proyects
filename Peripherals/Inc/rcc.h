/*
 * Trabajo de Tesis
 *
 *  Created on: Feb 8, 2025
 *      Author: Daniel Dominguez Fragoso
 */

#ifndef INC_RCC_H_
#define INC_RCC_H_

#include"main.h"



/*
 * @brief MSI MAX SPEDD(80 Mhz) Config
 */
void rcc_MSI_PLL_config(void);
/*
 * @brief MSI_PLLSAL1R for ADC (40 Mhz) Config
 */
void rcc_MSI_PLLSAL1R_config(void);
/*
 * @brief SysTick Config
 */
void rcc_SysTick_config(uint32_t tick);
/*
 * @brief increment ms Tick
 */
void rcc_msIncTick(void);
/*
 * @brief get increment ms Tick
 */
uint32_t rcc_msGetTick(void);
/*
 * @brief ms delay
 */
void rcc_msDelay(uint32_t msTime);


#endif /* INC_RCC_H_ */
