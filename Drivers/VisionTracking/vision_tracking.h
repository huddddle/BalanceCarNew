#ifndef __VISION_TRACKING_H
#define __VISION_TRACKING_H

#include <stdint.h>

/*
 * ============================ 视觉寻迹串口驱动 ============================
 *
 * 视觉模块通过串口 UART_VISION 周期性地发送一帧数据：
 *
 *      $<sign><error>,<data>#
 *
 *   例:  $+120,2#   ->  误差 error = +120 , 附加数据 data = 2
 *        $-045,1#   ->  误差 error = -45  , 附加数据 data = 1
 *
 *   '$'   : 帧头
 *   sign  : 符号 '+' / '-'
 *   error : 误差(带符号一共 4 位 = 符号 + 3 位数字)
 *   ','   : 误差与数据之间的分隔符
 *   data  : 1 位附加数据
 *   '#'   : 帧尾
 *
 * 串口硬件(见 mspm0-modules.syscfg 中的 UART_VISION)：
 *      外设   : UART3
 *      引脚   : RX = PA25   (视觉模块的 TX 接到这里, 板子上标注 RX)
 *               TX = PA26   (板子上标注 TX, 需要向视觉端发指令时使用)
 *      波特率 : 115200 - 8 - N - 1     (如与视觉端不一致, 改 syscfg 后重新生成)
 *      中断   : 使能 RX 接收中断, 中断服务函数 = UART3_IRQHandler
 *
 * ------------------------- 与现有循迹逻辑的兼容性 -------------------------
 * vision_data.error 的物理含义与现有红外循迹 move.c/Tracking() 里的 Tracking_Sum
 * 完全一致：都表示“车体相对赛道中线的偏差”。因此后续写循迹控制时可以直接把
 * vision_data.error 当作偏差喂进 PD 控制器, 写法与 Tracking() 里保持一致：
 *
 *      static int last_err = 0;
 *      int err    = vision_data.error;
 *      int adjust = (int)(Kp * err + Kd * (err - last_err));
 *      last_err   = err;
 *      Left_Control (1, irSpeed - adjust);
 *      Right_Control(1, irSpeed + adjust);
 *
 * 本驱动只负责【接收 / 解析 / 显示 / 调试指示】, 不实现任何循迹控制逻辑。
 * ========================================================================
 */

typedef struct {
    int16_t  error;        // 带符号误差, 例如 +120 / -45
    uint8_t  data;         // 1 位附加数据
    uint8_t  valid;        // 最近一帧是否解析成功(格式正确 = 1)
    uint32_t frame_count;  // 已成功解析的帧计数(可观察数据是否在持续更新)
    volatile uint8_t updated; // 收到新帧后置 1; 主循环读取后可自行清 0
    char     raw[16];      // 帧头帧尾之间的原始字符串, 例如 "+120,2"
} VisionData_t;

// 最近一次接收到的视觉数据(在中断中更新, 主循环读取)
extern VisionData_t vision_data;

// 初始化视觉串口: 使能 UART3 的 NVIC 中断 + B22(LED) 调试指示灯 + 绘制 OLED 静态标签
void Vision_Init(void);

// 刷新 OLED 上的视觉数据(在主循环中周期调用)
void Vision_ShowOLED(void);

// 视觉串口接收中断服务函数(名字由 SysConfig 生成: UART3_IRQHandler)
void UART_VISION_INST_IRQHandler(void);

#endif /* __VISION_TRACKING_H */
