#ifndef HOST_COM_H
#define HOST_COM_H

#include "ti_msp_dl_config.h"
#include <stdbool.h>
#include <stdint.h>

/* UART3 unique low-level driver: PA25 RX, PA26 TX, 115200 8N1. */
#define HOST_PACKET_LEN       (12U)
#define HOST_VAR2_LEN         (6U)

extern char g_Host_Var1;
extern int16_t g_Host_Var2;
extern char g_Host_Var3;
extern uint8_t gTxPacket[HOST_PACKET_LEN];
extern uint8_t gRxPacket[HOST_PACKET_LEN];
extern volatile bool gCheckUART;
extern volatile bool gDMADone_TX;
extern volatile bool gDMADone_RX;

bool Host_Send(char var1, const char *var2, char var3);
void Host_Receive_Start(void);
bool Host_Receive_Process(void);
void UART_0_INST_IRQHandler(void);

#endif
