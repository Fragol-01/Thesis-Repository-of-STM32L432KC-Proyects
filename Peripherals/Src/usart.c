/*
 * Trabajo de Tesis
 *
 *  Created on: Feb 10, 2025
 *      Author: Daniel Dominguez Fragoso
 */

#include"usart.h"
//#define SYSTEM_CLK 80000000

/*
 * @brief USART2 GPIO Config
 */
void usart_USART2_GPIO_CONFIG(void){
	// Enable PortA Clock
	RCC->AHB2ENR  |= ( RCC_AHB2ENR_GPIOAEN );
	// Configure pins PA2(Tx pin), PA15(Rx pin) for USART2 .
	GPIOA->MODER    &= ~( GPIO_MODER_MODE2 | GPIO_MODER_MODE15 );
	GPIOA->MODER    |=  ( ( GPIO_MODER_MODE2_1 ) | ( GPIO_MODER_MODE15_1 ) );
	GPIOA->OTYPER   &= ~( ( 0x1 << 2 ) | ( 0x1 << 15 ) );
	GPIOA->OSPEEDR  &= ~( ( 0x3 << ( 2 * 2 ) ) | ( 0x3 << ( 15 * 2 ) ) );
	GPIOA->OSPEEDR  |=  ( ( 0x2 << ( 2 * 2 ) ) | ( 0x2 << ( 15 * 2 ) ) );
	GPIOA->AFR[ 0 ] &= ~( GPIO_AFRL_AFSEL2 );
	GPIOA->AFR[ 0 ] |=  ~( GPIO_AFRL_AFSEL2_3 );
	GPIOA->AFR[ 1 ] &= ~( GPIO_AFRH_AFRH7 );
	GPIOA->AFR[ 1 ] |=  ( (GPIO_AFRH_AFSEL15_1 | GPIO_AFRH_AFSEL15_0 ) );

}
/*
 * USART2 Peripherals Config
 */
void usart_USART2_Config(uint32_t SYSTEM_CLK){
	//Enable USART2 CLK
	RCC->APB1ENR1  |= ( RCC_APB1ENR1_USART2EN );
	//Enable transmit
	USART2->CR1 |= ( USART_CR1_TE);
	// Parity control disabled
	USART2->CR1  &= ~(USART_CR1_PCE);
	//Word length to 8-bits
    USART2->CR1  &= ~(USART_CR1_M1);//default
    USART2->CR1  &= ~(USART_CR1_M0);//default
	//Stop bit to 1
    USART2->CR2  &= ~(USART_CR2_STOP);//default
	//Disable HW flow control
    USART2->CR3  &= ~(USART_CR3_CTSE);//default
    USART2->CR3  &= ~(USART_CR3_RTSE);//default
	//Set baudrate to 115200
    USART2->BRR =0;
    USART2->BRR = SYSTEM_CLK/115200;
    // Clear flags
    USART2->CR2 &= ~(USART_CR2_LINEN | USART_CR2_CLKEN);
    USART2->CR3 &= ~(USART_CR3_HDSEL | USART_CR3_IREN | USART_CR3_SCEN );
	//Enable USART2
    USART2->CR1 |= ( USART_CR1_UE );
}
/*
 * USART2 Transmit Function
 */
bool usart_USART2_TX_Function(uint8_t *data,uint8_t len, uint32_t timeout){

	//Write to DR as TXE flag is HIGH (Tx buffer Empty)
	  uint8_t dataIdx = 0;
	  uint32_t startTick = rcc_msGetTick();
	  while(dataIdx<len)
	  {
	    if(USART2->ISR & USART_ISR_TXE) //Tx buffer empty
	    {
	      USART2->TDR = data[dataIdx];
	      dataIdx++;
	    }
	    else //Manage timeout
	    {
	      if((rcc_msGetTick() - startTick)>= timeout) return false;
	    }
	  }
	  //Wait for busy flag
	  while( (USART2->ISR & USART_ISR_TC) )
	  {
	    if((rcc_msGetTick() - startTick)>= timeout) return false;
	  }
	  return true;
}
