#include "control.h"
#include "clock.h"
#include "ti_msp_dl_config.h"
#include "uart_callback.h"

static void Gimbal_DelayMs(uint32_t milliseconds)
{
    (void)mspm0_delay_ms(milliseconds);
}

void Gimbal_Init(void)
{
    DL_GPIO_setDigitalInternalResistor(
        GPIO_UART_GIMBAL_IOMUX_RX, DL_GPIO_RESISTOR_PULL_UP);
    DL_UART_Main_enableInterrupt(
        UART_GIMBAL_INST, DL_UART_MAIN_INTERRUPT_RX);
    NVIC_ClearPendingIRQ(UART_GIMBAL_INST_INT_IRQN);
    NVIC_EnableIRQ(UART_GIMBAL_INST_INT_IRQN);

    usart1_send(0x00U);
    Gimbal_DelayMs(1500U);

    BLDC_Enable(BLDC_ADDR_1);
    Gimbal_DelayMs(1U);
    BLDC_Enable(BLDC_ADDR_2);
    Gimbal_DelayMs(1U);
    BLDC_SetMode(BLDC_ADDR_1, MODE_SPEED);
    Gimbal_DelayMs(1U);
    BLDC_SetMode(BLDC_ADDR_2, MODE_SPEED);
    Gimbal_DelayMs(1U);
}
