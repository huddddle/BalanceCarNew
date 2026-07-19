#ifndef __CONTROL_H
#define __CONTROL_H

#include "DataScope_DP.h"

/*
 * ============================================================================
 * UART_GIMBAL SysConfig 配置教程
 * ============================================================================
 *
 * 目标
 *   在 MSPM0G3507 上使用 UART1：PA8(TX)、PA9(RX)、115200 8N1，连接
 *   F32C 二维云台的两个无刷电机控制器。SysConfig 实例名必须为
 *   UART_GIMBAL，代码中的宏均由这个实例名生成。
 *
 * 参考工程
 *   D:/Electric/My_TI_Workspace/empty_LP_MSPM0G3507_nortos_ticlang
 *
 * 1. 打开配置
 *   在 CCS Project Explorer 中双击工程根目录 mspm0-modules.syscfg。
 *
 * 2. 添加或改名 UART
 *   左侧 Communication -> UART。若已有绑定 UART1 的 UART_BT，不要再
 *   新增第二个实例，直接将 UART_BT 改名为 UART_GIMBAL。一个硬件 UART
 *   只能绑定一个 SysConfig UART 实例。
 *
 * 3. Basic Configuration
 *   Instance Name      : UART_GIMBAL
 *   Peripheral         : UART1
 *   Target Baud Rate   : 115200
 *   Direction          : TX and RX
 *   Data Bits          : 8
 *   Parity             : None
 *   Stop Bits          : One
 *   Interrupt Priority : 3
 *   Enable FIFO        : disabled
 *
 * 4. PinMux
 *   TX : PA8  / IOMUX_PINCM19 / UART1_TX
 *   RX : PA9  / IOMUX_PINCM20 / UART1_RX
 *   RX 建议上拉；Gimbal_Init() 会在运行时打开内部上拉。
 *
 * 5. Interrupts
 *   Enabled Interrupts : RX
 *   云台反馈帧由 UART1 RX 中断逐字节送入 BLDC_ParseRxData()，不要给
 *   UART_GIMBAL 配置 DMA。UART_GIMBAL_INST_IRQHandler 的实际符号会由
 *   SysConfig 宏展开为 UART1_IRQHandler。
 *
 * 6. 文本配置参考
 *   UART2.$name                            = "UART_GIMBAL";
 *   UART2.targetBaudRate                   = 115200;
 *   UART2.interruptPriority                = "3";
 *   UART2.enabledInterrupts                = ["RX"];
 *   UART2.peripheral.$assign               = "UART1";
 *   UART2.peripheral.txPin.$assign         = "PA8";
 *   UART2.peripheral.rxPin.$assign         = "PA9";
 *   UART2.peripheral.$suggestSolution      = "UART1";
 *
 *   UART2 只是 .syscfg 内的 JavaScript 变量名，硬件外设仍是 UART1。
 *
 * 7. 保存和检查生成结果
 *   Ctrl+S 保存。CCS 构建时生成 Debug/ti_msp_dl_config.h 和 .c。
 *   ti_msp_dl_config.h 中应出现：
 *     UART_GIMBAL_INST             UART1
 *     UART_GIMBAL_INST_IRQHandler  UART1_IRQHandler
 *     UART_GIMBAL_INST_INT_IRQN    UART1_INT_IRQn
 *     GPIO_UART_GIMBAL_IOMUX_TX    IOMUX_PINCM19
 *     GPIO_UART_GIMBAL_IOMUX_RX    IOMUX_PINCM20
 *     UART_GIMBAL_BAUD_RATE        115200
 *
 * 8. main.c 用法和可裁剪要求
 *   在 SYSCFG_DL_init() 后调用 Gimbal_Init()。它会打开 RX 中断、发送
 *   唤醒字节、使能地址 1/2，并将两个控制器设置为速度闭环模式。
 *   除 main.c 外，BalanceCarNew 的其他目录不得 include 本文件或调用
 *   GBControl API。以后不用云台时，只需：
 *     a. 将 Drivers/GBControl 目录 Exclude from Build；
 *     b. 删除 main.c 的 #include "control.h" 和 Gimbal_Init()；
 *     c. 可选：在 SysConfig 中删除 UART_GIMBAL，释放 PA8/PA9。
 *
 * 9. 串口冲突说明
 *   PA8/PA9 只属于云台，不再用于旧蓝牙。蓝牙、视觉和上位机统一通过
 *   Hostcom 使用 UART3 的 PA25(RX)/PA26(TX)，帧格式为：
 *     $<var1>,<六字符有符号十进制数>,<var3>#
 *   例如：$2,+12000,6#（固定 12 字节）。
 * ============================================================================
 */

void Gimbal_Init(void);

#endif
