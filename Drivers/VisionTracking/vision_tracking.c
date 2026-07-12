#include "vision_tracking.h"
#include "ti_msp_dl_config.h"
#include "oled_hardware_i2c.h"
#include <stdio.h>
#include <string.h>

// 最近一次接收到的视觉数据
VisionData_t vision_data = {0};

// 接收状态机的私有缓存(仅本文件使用)
static char    rx_buf[16];   // 存放帧头帧尾之间的字符
static uint8_t rx_idx = 0;   // 当前写入位置
static uint8_t receiving = 0; // 是否处于一帧接收过程中

/*
 * 解析一帧(不含帧头 '$' 和帧尾 '#')的字符串, 例如 "+120,2"。
 * 兼容变长: "+120,2" / "-45,1" / "+3,0" 都能正确解析。
 */
static void Vision_ParseFrame(const char *s)
{
    int  sign = 1;
    long err  = 0;
    int  dat  = 0;
    int  i    = 0;
    uint8_t got_error = 0;
    uint8_t got_comma = 0;

    // 1. 符号
    if (s[i] == '+') { sign = 1;  i++; }
    else if (s[i] == '-') { sign = -1; i++; }

    // 2. 误差数字
    while (s[i] >= '0' && s[i] <= '9') {
        err = err * 10 + (s[i] - '0');
        i++;
        got_error = 1;
    }

    // 3. 分隔逗号 + 附加数据
    if (s[i] == ',') {
        got_comma = 1;
        i++;
        while (s[i] >= '0' && s[i] <= '9') {
            dat = dat * 10 + (s[i] - '0');
            i++;
        }
    }

    // 4. 写入全局数据
    vision_data.error = (int16_t)(sign * err);
    vision_data.data  = (uint8_t)dat;
    vision_data.valid = (got_error && got_comma) ? 1 : 0;

    strncpy(vision_data.raw, s, sizeof(vision_data.raw) - 1);
    vision_data.raw[sizeof(vision_data.raw) - 1] = '\0';

    vision_data.frame_count++;
    vision_data.updated = 1;
}

/*
 * 视觉串口接收中断: 逐字节接收, 按 '$' ... '#' 组帧, 收齐一帧后解析。
 * 每进入一次中断就翻转一次 B22(LED), 用于调试观察串口是否有数据进来。
 */
void UART_VISION_INST_IRQHandler(void)
{
    switch (DL_UART_Main_getPendingInterrupt(UART_VISION_INST))
    {
        case DL_UART_MAIN_IIDX_RX:
        {
            uint8_t ch = DL_UART_Main_receiveData(UART_VISION_INST);

            // B22 调试指示灯: 进中断即翻转电平, 说明串口正在收数据
            DL_GPIO_togglePins(LED_PORT, LED_USER_LED_PIN);

            if (ch == '$') {              // 帧头: 开始接收新的一帧
                rx_idx = 0;
                receiving = 1;
            } else if (ch == '#') {       // 帧尾: 结束并解析
                if (receiving) {
                    rx_buf[rx_idx] = '\0';
                    Vision_ParseFrame(rx_buf);
                    receiving = 0;
                }
            } else if (receiving) {       // 中间字符: 写入缓存
                if (rx_idx < sizeof(rx_buf) - 1) {
                    rx_buf[rx_idx++] = (char)ch;
                } else {
                    receiving = 0;        // 溢出保护: 帧异常过长, 丢弃本帧
                }
            }
            break;
        }

        default:
            break;
    }
}

// 初始化: 使能接收中断 + 绘制 OLED 静态标签(覆盖之前的调试信息)
void Vision_Init(void)
{
    NVIC_ClearPendingIRQ(UART_VISION_INST_INT_IRQN);
    NVIC_EnableIRQ(UART_VISION_INST_INT_IRQN);

    OLED_Clear();
    // OLED_ShowString(0, 0, (uint8_t *)"Vision Tracking", 8);
    OLED_ShowString(0, 0, (uint8_t *)"Raw:", 8);
    OLED_ShowString(0, 2, (uint8_t *)"Err:", 8);
    OLED_ShowString(0, 4, (uint8_t *)"Dat:", 8);

}

// 刷新 OLED 上的动态视觉数据(在主循环中调用)
void Vision_ShowOLED(void)
{
    static char buf[20];

    // 原始帧字符串(用空格补齐, 覆盖上一次残留的字符)
    snprintf(buf, sizeof(buf), "%-11s", vision_data.raw);
    OLED_ShowString(4 * 8, 0, (uint8_t *)buf, 8);

    // 带符号误差
    snprintf(buf, sizeof(buf), "%-6d", vision_data.error);
    OLED_ShowString(4 * 8, 2, (uint8_t *)buf, 8);

    // 1 位附加数据
    snprintf(buf, sizeof(buf), "%-3u", (unsigned)vision_data.data);
    OLED_ShowString(4 * 8, 4, (uint8_t *)buf, 8);


}
