/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)



#define CPUCLK_FREQ                                                     80000000



/* Defines for PWM_0 */
#define PWM_0_INST                                                         TIMA1
#define PWM_0_INST_IRQHandler                                   TIMA1_IRQHandler
#define PWM_0_INST_INT_IRQN                                     (TIMA1_INT_IRQn)
#define PWM_0_INST_CLK_FREQ                                             10000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_0_C0_PORT                                                 GPIOB
#define GPIO_PWM_0_C0_PIN                                          DL_GPIO_PIN_4
#define GPIO_PWM_0_C0_IOMUX                                      (IOMUX_PINCM17)
#define GPIO_PWM_0_C0_IOMUX_FUNC                     IOMUX_PINCM17_PF_TIMA1_CCP0
#define GPIO_PWM_0_C0_IDX                                    DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_0_C1_PORT                                                 GPIOB
#define GPIO_PWM_0_C1_PIN                                          DL_GPIO_PIN_5
#define GPIO_PWM_0_C1_IOMUX                                      (IOMUX_PINCM18)
#define GPIO_PWM_0_C1_IOMUX_FUNC                     IOMUX_PINCM18_PF_TIMA1_CCP1
#define GPIO_PWM_0_C1_IDX                                    DL_TIMER_CC_1_INDEX

/* Defines for PWM_SERVO */
#define PWM_SERVO_INST                                                     TIMG7
#define PWM_SERVO_INST_IRQHandler                               TIMG7_IRQHandler
#define PWM_SERVO_INST_INT_IRQN                                 (TIMG7_INT_IRQn)
#define PWM_SERVO_INST_CLK_FREQ                                           320000
/* GPIO defines for channel 0 */
#define GPIO_PWM_SERVO_C0_PORT                                             GPIOA
#define GPIO_PWM_SERVO_C0_PIN                                     DL_GPIO_PIN_28
#define GPIO_PWM_SERVO_C0_IOMUX                                   (IOMUX_PINCM3)
#define GPIO_PWM_SERVO_C0_IOMUX_FUNC                  IOMUX_PINCM3_PF_TIMG7_CCP0
#define GPIO_PWM_SERVO_C0_IDX                                DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_SERVO_C1_PORT                                             GPIOA
#define GPIO_PWM_SERVO_C1_PIN                                     DL_GPIO_PIN_31
#define GPIO_PWM_SERVO_C1_IOMUX                                   (IOMUX_PINCM6)
#define GPIO_PWM_SERVO_C1_IOMUX_FUNC                  IOMUX_PINCM6_PF_TIMG7_CCP1
#define GPIO_PWM_SERVO_C1_IDX                                DL_TIMER_CC_1_INDEX

/* Defines for PWM_ULTRASONIC */
#define PWM_ULTRASONIC_INST                                                TIMG8
#define PWM_ULTRASONIC_INST_IRQHandler                          TIMG8_IRQHandler
#define PWM_ULTRASONIC_INST_INT_IRQN                            (TIMG8_INT_IRQn)
#define PWM_ULTRASONIC_INST_CLK_FREQ                                     5000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_ULTRASONIC_C0_PORT                                        GPIOA
#define GPIO_PWM_ULTRASONIC_C0_PIN                                DL_GPIO_PIN_23
#define GPIO_PWM_ULTRASONIC_C0_IOMUX                             (IOMUX_PINCM53)
#define GPIO_PWM_ULTRASONIC_C0_IOMUX_FUNC             IOMUX_PINCM53_PF_TIMG8_CCP0
#define GPIO_PWM_ULTRASONIC_C0_IDX                           DL_TIMER_CC_0_INDEX



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMG6)
#define TIMER_0_INST_IRQHandler                                 TIMG6_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMG6_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                         (24999U)
/* Defines for TIMER_ULTRASONIC */
#define TIMER_ULTRASONIC_INST                                            (TIMG0)
#define TIMER_ULTRASONIC_INST_IRQHandler                        TIMG0_IRQHandler
#define TIMER_ULTRASONIC_INST_INT_IRQN                          (TIMG0_INT_IRQn)
#define TIMER_ULTRASONIC_INST_LOAD_VALUE                                (19999U)
/* Defines for TIMER_Balance */
#define TIMER_Balance_INST                                               (TIMA0)
#define TIMER_Balance_INST_IRQHandler                           TIMA0_IRQHandler
#define TIMER_Balance_INST_INT_IRQN                             (TIMA0_INT_IRQn)
#define TIMER_Balance_INST_LOAD_VALUE                                   (49999U)




/* Defines for I2C_OLED */
#define I2C_OLED_INST                                                       I2C1
#define I2C_OLED_INST_IRQHandler                                 I2C1_IRQHandler
#define I2C_OLED_INST_INT_IRQN                                     I2C1_INT_IRQn
#define I2C_OLED_BUS_SPEED_HZ                                             100000
#define GPIO_I2C_OLED_SDA_PORT                                             GPIOA
#define GPIO_I2C_OLED_SDA_PIN                                     DL_GPIO_PIN_16
#define GPIO_I2C_OLED_IOMUX_SDA                                  (IOMUX_PINCM38)
#define GPIO_I2C_OLED_IOMUX_SDA_FUNC                   IOMUX_PINCM38_PF_I2C1_SDA
#define GPIO_I2C_OLED_SCL_PORT                                             GPIOA
#define GPIO_I2C_OLED_SCL_PIN                                     DL_GPIO_PIN_17
#define GPIO_I2C_OLED_IOMUX_SCL                                  (IOMUX_PINCM39)
#define GPIO_I2C_OLED_IOMUX_SCL_FUNC                   IOMUX_PINCM39_PF_I2C1_SCL


/* Defines for UART_WIT */
#define UART_WIT_INST                                                      UART0
#define UART_WIT_INST_FREQUENCY                                         40000000
#define UART_WIT_INST_IRQHandler                                UART0_IRQHandler
#define UART_WIT_INST_INT_IRQN                                    UART0_INT_IRQn
#define GPIO_UART_WIT_RX_PORT                                              GPIOA
#define GPIO_UART_WIT_RX_PIN                                      DL_GPIO_PIN_11
#define GPIO_UART_WIT_IOMUX_RX                                   (IOMUX_PINCM22)
#define GPIO_UART_WIT_IOMUX_RX_FUNC                    IOMUX_PINCM22_PF_UART0_RX
#define UART_WIT_BAUD_RATE                                              (115200)
#define UART_WIT_IBRD_40_MHZ_115200_BAUD                                    (21)
#define UART_WIT_FBRD_40_MHZ_115200_BAUD                                    (45)
/* Defines for UART_GIMBAL */
#define UART_GIMBAL_INST                                                   UART1
#define UART_GIMBAL_INST_FREQUENCY                                      40000000
#define UART_GIMBAL_INST_IRQHandler                             UART1_IRQHandler
#define UART_GIMBAL_INST_INT_IRQN                                 UART1_INT_IRQn
#define GPIO_UART_GIMBAL_RX_PORT                                           GPIOA
#define GPIO_UART_GIMBAL_TX_PORT                                           GPIOA
#define GPIO_UART_GIMBAL_RX_PIN                                    DL_GPIO_PIN_9
#define GPIO_UART_GIMBAL_TX_PIN                                    DL_GPIO_PIN_8
#define GPIO_UART_GIMBAL_IOMUX_RX                                (IOMUX_PINCM20)
#define GPIO_UART_GIMBAL_IOMUX_TX                                (IOMUX_PINCM19)
#define GPIO_UART_GIMBAL_IOMUX_RX_FUNC                 IOMUX_PINCM20_PF_UART1_RX
#define GPIO_UART_GIMBAL_IOMUX_TX_FUNC                 IOMUX_PINCM19_PF_UART1_TX
#define UART_GIMBAL_BAUD_RATE                                           (115200)
#define UART_GIMBAL_IBRD_40_MHZ_115200_BAUD                                 (21)
#define UART_GIMBAL_FBRD_40_MHZ_115200_BAUD                                 (45)
/* Defines for UART_0 */
#define UART_0_INST                                                        UART3
#define UART_0_INST_FREQUENCY                                           80000000
#define UART_0_INST_IRQHandler                                  UART3_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART3_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_25
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_26
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM55)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM59)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM55_PF_UART3_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM59_PF_UART3_TX
#define UART_0_BAUD_RATE                                                (115200)
#define UART_0_IBRD_80_MHZ_115200_BAUD                                      (43)
#define UART_0_FBRD_80_MHZ_115200_BAUD                                      (26)





/* Defines for DMA_WIT */
#define DMA_WIT_CHAN_ID                                                      (2)
#define UART_WIT_INST_DMA_TRIGGER                            (DMA_UART0_RX_TRIG)
/* Defines for DMA_CH1 */
#define DMA_CH1_CHAN_ID                                                      (1)
#define UART_0_INST_DMA_TRIGGER_0                            (DMA_UART3_TX_TRIG)
/* Defines for DMA_CH0 */
#define DMA_CH0_CHAN_ID                                                      (0)
#define UART_0_INST_DMA_TRIGGER_1                            (DMA_UART3_RX_TRIG)


/* Port definition for Pin Group LED */
#define LED_PORT                                                         (GPIOB)

/* Defines for USER_LED: GPIOB.22 with pinCMx 50 on package pin 21 */
#define LED_USER_LED_PIN                                        (DL_GPIO_PIN_22)
#define LED_USER_LED_IOMUX                                       (IOMUX_PINCM50)
/* Port definition for Pin Group GPIO_LASER */
#define GPIO_LASER_PORT                                                  (GPIOA)

/* Defines for PIN_0: GPIOA.1 with pinCMx 2 on package pin 34 */
#define GPIO_LASER_PIN_0_PIN                                     (DL_GPIO_PIN_1)
#define GPIO_LASER_PIN_0_IOMUX                                    (IOMUX_PINCM2)
/* Port definition for Pin Group BEE */
#define BEE_PORT                                                         (GPIOB)

/* Defines for Bee_Port: GPIOB.17 with pinCMx 43 on package pin 14 */
#define BEE_Bee_Port_PIN                                        (DL_GPIO_PIN_17)
#define BEE_Bee_Port_IOMUX                                       (IOMUX_PINCM43)
/* Port definition for Pin Group GPIO_OLED */
#define GPIO_OLED_PORT                                                   (GPIOB)

/* Defines for PIN_SCL: GPIOB.9 with pinCMx 26 on package pin 61 */
#define GPIO_OLED_PIN_SCL_PIN                                    (DL_GPIO_PIN_9)
#define GPIO_OLED_PIN_SCL_IOMUX                                  (IOMUX_PINCM26)
/* Defines for PIN_SDA: GPIOB.8 with pinCMx 25 on package pin 60 */
#define GPIO_OLED_PIN_SDA_PIN                                    (DL_GPIO_PIN_8)
#define GPIO_OLED_PIN_SDA_IOMUX                                  (IOMUX_PINCM25)
/* Defines for AIN1: GPIOB.3 with pinCMx 16 on package pin 51 */
#define TB6612_AIN1_PORT                                                 (GPIOB)
#define TB6612_AIN1_PIN                                          (DL_GPIO_PIN_3)
#define TB6612_AIN1_IOMUX                                        (IOMUX_PINCM16)
/* Defines for AIN2: GPIOB.2 with pinCMx 15 on package pin 50 */
#define TB6612_AIN2_PORT                                                 (GPIOB)
#define TB6612_AIN2_PIN                                          (DL_GPIO_PIN_2)
#define TB6612_AIN2_IOMUX                                        (IOMUX_PINCM15)
/* Defines for BIN1: GPIOA.7 with pinCMx 14 on package pin 49 */
#define TB6612_BIN1_PORT                                                 (GPIOA)
#define TB6612_BIN1_PIN                                          (DL_GPIO_PIN_7)
#define TB6612_BIN1_IOMUX                                        (IOMUX_PINCM14)
/* Defines for BIN2: GPIOB.14 with pinCMx 31 on package pin 2 */
#define TB6612_BIN2_PORT                                                 (GPIOB)
#define TB6612_BIN2_PIN                                         (DL_GPIO_PIN_14)
#define TB6612_BIN2_IOMUX                                        (IOMUX_PINCM31)
/* Defines for X1: GPIOB.24 with pinCMx 52 on package pin 23 */
#define IR_X_X1_PORT                                                     (GPIOB)
#define IR_X_X1_PIN                                             (DL_GPIO_PIN_24)
#define IR_X_X1_IOMUX                                            (IOMUX_PINCM52)
/* Defines for X2: GPIOB.20 with pinCMx 48 on package pin 19 */
#define IR_X_X2_PORT                                                     (GPIOB)
#define IR_X_X2_PIN                                             (DL_GPIO_PIN_20)
#define IR_X_X2_IOMUX                                            (IOMUX_PINCM48)
/* Defines for X3: GPIOB.18 with pinCMx 44 on package pin 15 */
#define IR_X_X3_PORT                                                     (GPIOB)
#define IR_X_X3_PIN                                             (DL_GPIO_PIN_18)
#define IR_X_X3_IOMUX                                            (IOMUX_PINCM44)
/* Defines for X4: GPIOB.19 with pinCMx 45 on package pin 16 */
#define IR_X_X4_PORT                                                     (GPIOB)
#define IR_X_X4_PIN                                             (DL_GPIO_PIN_19)
#define IR_X_X4_IOMUX                                            (IOMUX_PINCM45)
/* Defines for X5: GPIOA.12 with pinCMx 34 on package pin 5 */
#define IR_X_X5_PORT                                                     (GPIOA)
#define IR_X_X5_PIN                                             (DL_GPIO_PIN_12)
#define IR_X_X5_IOMUX                                            (IOMUX_PINCM34)
/* Defines for X6: GPIOB.16 with pinCMx 33 on package pin 4 */
#define IR_X_X6_PORT                                                     (GPIOB)
#define IR_X_X6_PIN                                             (DL_GPIO_PIN_16)
#define IR_X_X6_IOMUX                                            (IOMUX_PINCM33)
/* Defines for X7: GPIOB.15 with pinCMx 32 on package pin 3 */
#define IR_X_X7_PORT                                                     (GPIOB)
#define IR_X_X7_PIN                                             (DL_GPIO_PIN_15)
#define IR_X_X7_IOMUX                                            (IOMUX_PINCM32)
/* Defines for X8: GPIOA.27 with pinCMx 60 on package pin 31 */
#define IR_X_X8_PORT                                                     (GPIOA)
#define IR_X_X8_PIN                                             (DL_GPIO_PIN_27)
#define IR_X_X8_IOMUX                                            (IOMUX_PINCM60)
/* Port definition for Pin Group Encoder */
#define Encoder_PORT                                                     (GPIOB)

/* Defines for Left_A: GPIOB.11 with pinCMx 28 on package pin 63 */
// pins affected by this interrupt request:["Left_A","Right_A"]
#define Encoder_INT_IRQN                                        (GPIOB_INT_IRQn)
#define Encoder_INT_IIDX                        (DL_INTERRUPT_GROUP1_IIDX_GPIOB)
#define Encoder_Left_A_IIDX                                 (DL_GPIO_IIDX_DIO11)
#define Encoder_Left_A_PIN                                      (DL_GPIO_PIN_11)
#define Encoder_Left_A_IOMUX                                     (IOMUX_PINCM28)
/* Defines for Left_B: GPIOB.10 with pinCMx 27 on package pin 62 */
#define Encoder_Left_B_PIN                                      (DL_GPIO_PIN_10)
#define Encoder_Left_B_IOMUX                                     (IOMUX_PINCM27)
/* Defines for Right_A: GPIOB.6 with pinCMx 23 on package pin 58 */
#define Encoder_Right_A_IIDX                                 (DL_GPIO_IIDX_DIO6)
#define Encoder_Right_A_PIN                                      (DL_GPIO_PIN_6)
#define Encoder_Right_A_IOMUX                                    (IOMUX_PINCM23)
/* Defines for Right_B: GPIOB.7 with pinCMx 24 on package pin 59 */
#define Encoder_Right_B_PIN                                      (DL_GPIO_PIN_7)
#define Encoder_Right_B_IOMUX                                    (IOMUX_PINCM24)
/* Defines for ButtonLeft: GPIOB.21 with pinCMx 49 on package pin 20 */
#define Assignment_ButtonLeft_PORT                                       (GPIOB)
#define Assignment_ButtonLeft_PIN                               (DL_GPIO_PIN_21)
#define Assignment_ButtonLeft_IOMUX                              (IOMUX_PINCM49)
/* Defines for ButtonRight: GPIOA.14 with pinCMx 36 on package pin 7 */
#define Assignment_ButtonRight_PORT                                      (GPIOA)
#define Assignment_ButtonRight_PIN                              (DL_GPIO_PIN_14)
#define Assignment_ButtonRight_IOMUX                             (IOMUX_PINCM36)
/* Port definition for Pin Group GPIO_ULTRASONIC */
#define GPIO_ULTRASONIC_PORT                                             (GPIOB)

/* Defines for PIN_TRIG: GPIOB.12 with pinCMx 29 on package pin 64 */
#define GPIO_ULTRASONIC_PIN_TRIG_PIN                            (DL_GPIO_PIN_12)
#define GPIO_ULTRASONIC_PIN_TRIG_IOMUX                           (IOMUX_PINCM29)
/* Defines for PIN_ECHO: GPIOB.13 with pinCMx 30 on package pin 1 */
#define GPIO_ULTRASONIC_PIN_ECHO_PIN                            (DL_GPIO_PIN_13)
#define GPIO_ULTRASONIC_PIN_ECHO_IOMUX                           (IOMUX_PINCM30)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_0_init(void);
void SYSCFG_DL_PWM_SERVO_init(void);
void SYSCFG_DL_PWM_ULTRASONIC_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_TIMER_ULTRASONIC_init(void);
void SYSCFG_DL_TIMER_Balance_init(void);
void SYSCFG_DL_I2C_OLED_init(void);
void SYSCFG_DL_UART_WIT_init(void);
void SYSCFG_DL_UART_GIMBAL_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_DMA_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
