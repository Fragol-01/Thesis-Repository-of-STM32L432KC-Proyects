/*
 * Trabajo de Tesis
 *
 *  Created on: Feb 20, 2025
 *      Author: Daniel Dominguez Fragoso
 */

#ifndef INC_TIM_H_
#define INC_TIM_H_

#include "main.h"

/*
 * @brief TIM3 ADC TRGO timer with interrupt Config
 */
void tim_TIM6_with_INTERRPUT_Config(uint16_t msPeriod);
/*
 * @brief TIM3 ADC TRGO timer Config
 */
void tim_TIM6_Config(uint16_t msPeriod);
/*
 * @brief TIM1 ADC AWD timer Config
 */
void tim_TIM1_AWD_Config(uint16_t msPeriod);


#endif /* INC_TIM_H_ */
