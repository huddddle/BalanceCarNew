#include "ti_msp_dl_config.h"
#include "uart_callback.h"
#include "DataScope_DP.h"

void usart1_send(u8 data)
{
    while (DL_UART_isTXFIFOFull(UART_GIMBAL_INST) == true) {
    }
    DL_UART_Main_transmitData(UART_GIMBAL_INST, data);
}

void USART1_SEND(u8 *data, u8 len)
{
    u8 index;

    for (index = 0U; index < len; index++) {
        usart1_send(data[index]);
    }
}

void uart1_send_data(uint8_t data)
{
    usart1_send(data);
}

void uart1_send_SendArray(uint8_t *data, uint8_t len)
{
    USART1_SEND(data, len);
}

u8 BCC_Sum1(u8 *usart_data, unsigned char count)
{
    unsigned char checksum = 0U;
    unsigned char index;

    for (index = 0U; index < count; index++) {
        checksum ^= usart_data[index];
    }
    return checksum;
}

void UART_GIMBAL_INST_IRQHandler(void)
{
    if (DL_UART_Main_getPendingInterrupt(UART_GIMBAL_INST) ==
        DL_UART_MAIN_IIDX_RX) {
        BLDC_ParseRxData(DL_UART_Main_receiveData(UART_GIMBAL_INST));
    }
}
