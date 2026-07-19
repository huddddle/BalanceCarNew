#include "hostcom.h"
#include <stdlib.h>
#include <string.h>

char g_Host_Var1 = '0';
int16_t g_Host_Var2 = 0;
char g_Host_Var3 = '0';

uint8_t gTxPacket[HOST_PACKET_LEN];
uint8_t gRxPacket[HOST_PACKET_LEN];

volatile bool gCheckUART = false;
volatile bool gDMADone_TX = true;
volatile bool gDMADone_RX = false;

static void Host_StartTx(const uint8_t *data)
{
    DL_DMA_setSrcAddr(DMA, DMA_CH1_CHAN_ID, (uint32_t)data);
    DL_DMA_setDestAddr(
        DMA, DMA_CH1_CHAN_ID, (uint32_t)&UART_0_INST->TXDATA);
    DL_DMA_setTransferSize(DMA, DMA_CH1_CHAN_ID, HOST_PACKET_LEN);
    gCheckUART = false;
    gDMADone_TX = false;
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
    DL_DMA_enableChannel(DMA, DMA_CH1_CHAN_ID);
}

static void Host_StartRx(void)
{
    DL_DMA_setSrcAddr(
        DMA, DMA_CH0_CHAN_ID, (uint32_t)&UART_0_INST->RXDATA);
    DL_DMA_setDestAddr(DMA, DMA_CH0_CHAN_ID, (uint32_t)gRxPacket);
    DL_DMA_setTransferSize(DMA, DMA_CH0_CHAN_ID, HOST_PACKET_LEN);
    gDMADone_RX = false;
    DL_DMA_enableChannel(DMA, DMA_CH0_CHAN_ID);
}

bool Host_Send(char var1, const char *var2, char var3)
{
    if ((var2 == NULL) || (strlen(var2) != HOST_VAR2_LEN) ||
        (gDMADone_TX == false)) {
        return false;
    }

    gTxPacket[0] = '$';
    gTxPacket[1] = (uint8_t)var1;
    gTxPacket[2] = ',';
    memcpy(&gTxPacket[3], var2, HOST_VAR2_LEN);
    gTxPacket[9] = ',';
    gTxPacket[10] = (uint8_t)var3;
    gTxPacket[11] = '#';
    Host_StartTx(gTxPacket);
    return true;
}

void Host_Receive_Start(void)
{
    NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
    Host_StartRx();
}

bool Host_Receive_Process(void)
{
    char var2[HOST_VAR2_LEN + 1U];
    bool valid = false;

    if (gDMADone_RX == false) {
        return false;
    }

    if ((gRxPacket[0] == '$') && (gRxPacket[2] == ',') &&
        (gRxPacket[9] == ',') && (gRxPacket[11] == '#')) {
        memcpy(var2, &gRxPacket[3], HOST_VAR2_LEN);
        var2[HOST_VAR2_LEN] = '\0';
        g_Host_Var1 = (char)gRxPacket[1];
        g_Host_Var2 = (int16_t)strtol(var2, NULL, 10);
        g_Host_Var3 = (char)gRxPacket[10];
        valid = true;
    }

    Host_StartRx();
    return valid;
}

void UART_0_INST_IRQHandler(void)
{
    switch (DL_UART_Main_getPendingInterrupt(UART_0_INST)) {
        case DL_UART_MAIN_IIDX_EOT_DONE:
            gCheckUART = true;
            break;
        case DL_UART_MAIN_IIDX_DMA_DONE_TX:
            gDMADone_TX = true;
            break;
        case DL_UART_MAIN_IIDX_DMA_DONE_RX:
            gDMADone_RX = true;
            break;
        default:
            break;
    }
}
