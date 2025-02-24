/*
 * Trabajo de Tesis
 *
 *  Created on: Feb 10, 2025
 *      Author: Daniel Dominguez Fragoso
 */

#ifndef INC_USART_H_
#define INC_USART_H_


#include"main.h"


/*
 * @brief USART2 GPIO Config
 */
void usart_USART2_GPIO_CONFIG(void);
/*
 * USART2 Peripherals Config
 */
void usart_USART2_Config(uint32_t SYSTEM_CLK);
/*
 * USART2 Transmit Function
 */
bool usart_USART2_TX_Function(uint8_t *data, uint8_t len, uint32_t timeout);




#endif /* INC_USART_H_ */
