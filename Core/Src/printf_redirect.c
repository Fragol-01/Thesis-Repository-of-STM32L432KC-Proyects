/*
 * Trabajo de Tesis
 *
 *  Created on: Feb 11, 2025
 *      Author: Daniel Dominguez Fragoso
 */

#include "usart.h"

int __io_putchar(int ch);
int _write(int file,char *ptr, int len);

int __io_putchar(int ch) {
 uint8_t c[1];
 c[0] = ch & 0x00FF;
 usart_USART2_TX_Function(&c[0], 1, 100);
 return ch;
}

int _write(int file,char *ptr, int len) {
 int DataIdx;
 for(DataIdx= 0; DataIdx< len; DataIdx++) {
  __io_putchar(*ptr++);
 }
 return len;
}
