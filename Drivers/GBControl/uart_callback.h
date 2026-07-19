#ifndef UART_CALLBACK_H
#define UART_CALLBACK_H

#include <stdint.h>

typedef uint8_t u8;

void usart1_send(u8 data);
void USART1_SEND(u8 *data, u8 len);
void uart1_send_data(uint8_t data);
void uart1_send_SendArray(uint8_t *data, uint8_t len);
u8 BCC_Sum1(u8 *usart_data, unsigned char count);
void UART_GIMBAL_INST_IRQHandler(void);

#endif
