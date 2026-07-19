# GBControl 云台电机控制使用手册

## 1. 模块说明

GBControl 用于通过 UART1 控制 F32C TTL 无刷电机控制器。当前工程的硬件配置如下：

- UART：`UART_GIMBAL`（硬件 UART1）
- 波特率：115200，8 数据位，1 停止位，无校验
- TX：PA8
- RX：PA9
- 默认电机地址：`BLDC_ADDR_1`（0x01）和 `BLDC_ADDR_2`（0x02）
- 协议帧头：0x7A
- 协议帧尾：0x7B

应用代码通常只需要包含：

```c
#include "control.h"
```

`control.h` 已经包含 `DataScope_DP.h`，因此可以直接使用全部 `BLDC_*` 控制函数。

## 2. 初始化

### `void Gimbal_Init(void)`

初始化云台通信和两个电机控制器。必须在 `SYSCFG_DL_init()` 和 `SysTick_Init()` 之后调用。

该函数将执行：

1. 设置 UART1 RX 引脚内部上拉；
2. 开启 UART1 RX 中断；
3. 发送唤醒字节；
4. 使用工程已有的 `mspm0_delay_ms()` 等待控制器上电；
5. 使能地址 1 和地址 2 的电机；
6. 将两个电机设置为速度闭环模式。

```c
SYSCFG_DL_init();
SysTick_Init();
Gimbal_Init();
```

## 3. 电机地址和工作模式

### 电机地址

| 宏 | 地址 | 说明 |
|---|---:|---|
| `BLDC_ADDR_1` | 0x01 | 1 号电机 |
| `BLDC_ADDR_2` | 0x02 | 2 号电机 |

### 工作模式

| 宏 | 值 | 说明 |
|---|---:|---|
| `MODE_SPEED` | 0x0000 | 速度闭环模式 |
| `MODE_MULTI_POS` | 0x0001 | 多圈位置模式 |
| `MODE_SINGLE_POS` | 0x0002 | 单圈位置模式 |
| `MODE_MULTI_POS_L` | 0x0003 | 多圈位置模式 L |
| `MODE_SINGLE_POS_L` | 0x0004 | 单圈位置模式 L |

切换控制方式前，应先调用 `BLDC_SetMode()` 设置相应模式，并在连续命令之间保留至少 1 ms 间隔。

## 4. 全部电机控制函数

### 4.1 使能电机

```c
void BLDC_Enable(uint8_t addr);
```

使能指定地址的电机。

```c
BLDC_Enable(BLDC_ADDR_1);
```

### 4.2 停止并失能电机

```c
void BLDC_Disable(uint8_t addr);
```

失能指定地址的电机。需要停止云台时，建议先发送零转速，再失能。

```c
BLDC_SetSpeed(BLDC_ADDR_1, 0);
mspm0_delay_ms(10);
BLDC_Disable(BLDC_ADDR_1);
```

### 4.3 设置转速

```c
void BLDC_SetSpeed(uint8_t addr, int16_t rpm);
```

设置电机目标转速，单位为 RPM。正负号控制旋转方向，实际正方向由电机安装方向决定。

```c
BLDC_SetMode(BLDC_ADDR_1, MODE_SPEED);
mspm0_delay_ms(1);
BLDC_SetSpeed(BLDC_ADDR_1, 20);   // 正向 20 RPM
mspm0_delay_ms(10);
BLDC_SetSpeed(BLDC_ADDR_2, -20);  // 反向 20 RPM
```

### 4.4 设置工作模式

```c
void BLDC_SetMode(uint8_t addr, uint16_t mode);
```

设置指定电机的闭环控制模式。`mode` 应使用本手册第 3 节列出的 `MODE_*` 宏。

```c
BLDC_SetMode(BLDC_ADDR_1, MODE_SPEED);
BLDC_SetMode(BLDC_ADDR_2, MODE_SINGLE_POS);
```

### 4.5 设置多圈目标角度

```c
void BLDC_SetMultiAngle(uint8_t addr, int32_t angle_x10);
```

设置多圈位置，单位为 0.1°。参数允许为负数。

```c
BLDC_SetMode(BLDC_ADDR_1, MODE_MULTI_POS);
mspm0_delay_ms(1);
BLDC_SetMultiAngle(BLDC_ADDR_1, 3600);   // +360.0°
BLDC_SetMultiAngle(BLDC_ADDR_1, -900);   // -90.0°
```

### 4.6 设置单圈目标角度

```c
void BLDC_SetSingleAngle(uint8_t addr, uint16_t angle_x10);
```

设置单圈绝对角度，单位为 0.1°。有效范围为 0～3599，即 0.0°～359.9°；大于 3599 的输入会被函数限制为 3599。

```c
BLDC_SetMode(BLDC_ADDR_2, MODE_SINGLE_POS);
mspm0_delay_ms(1);
BLDC_SetSingleAngle(BLDC_ADDR_2, 900);   // 90.0°
```

### 4.7 设置加速度

```c
void BLDC_SetAcc(uint8_t addr, uint16_t acc);
```

设置电机加速度，单位为 转/s²。具体允许范围以所用 F32C 控制器说明书为准。

```c
BLDC_SetAcc(BLDC_ADDR_1, 100);
```

### 4.8 保存参数

```c
void BLDC_SaveParams(uint8_t addr);
```

将控制器当前参数保存到非易失存储器。该操作不应在主循环中频繁调用，以免缩短存储器寿命。

```c
BLDC_SetAcc(BLDC_ADDR_1, 100);
mspm0_delay_ms(10);
BLDC_SaveParams(BLDC_ADDR_1);
```

### 4.9 清零多圈角度

```c
void BLDC_ClearMultiAngle(uint8_t addr);
```

清除指定电机记录的多圈角度。

```c
BLDC_ClearMultiAngle(BLDC_ADDR_1);
```

### 4.10 设置单圈零点

```c
void BLDC_SetSingleAngleZero(uint8_t addr);
```

将电机当前位置设置为单圈绝对角度零点。执行前应确保云台已经停稳并处于正确的机械零位。

```c
BLDC_SetSpeed(BLDC_ADDR_2, 0);
mspm0_delay_ms(10);
BLDC_SetSingleAngleZero(BLDC_ADDR_2);
```

### 4.11 恢复出厂设置

```c
void BLDC_FactoryReset(uint8_t addr);
```

恢复指定控制器的出厂参数。这可能改变工作模式、地址或其他参数，应谨慎调用。

```c
BLDC_FactoryReset(BLDC_ADDR_1);
```

### 4.12 修改电机地址

```c
void BLDC_SetAddress(uint8_t addr, uint8_t new_addr);
```

将地址为 `addr` 的控制器修改为 `new_addr`。修改时总线上最好只连接一个待修改控制器，避免地址冲突。

```c
BLDC_SetAddress(BLDC_ADDR_1, 0x03);
```

修改地址后，工程中的 `BLDC_ADDR_1`/`BLDC_ADDR_2` 宏不会自动变化；如需长期使用新地址，应同步修改应用代码或地址宏。

## 5. 状态反馈函数

### `void BLDC_ReqFeedback(uint8_t addr, uint8_t type)`

请求指定电机返回一类实时数据。

可用反馈类型：

| 宏 | 反馈内容 | 保存位置 |
|---|---|---|
| `FB_SPEED` | 实时速度 | `BLDC_Motor1.speed` / `BLDC_Motor2.speed` |
| `FB_MULTI_ANGLE` | 多圈角度 | `.multi_angle` |
| `FB_SINGLE_ANGLE` | 单圈角度 | `.single_angle` |
| `FB_ACC` | 加速度 | `.acc` |
| `FB_VOLTAGE` | 母线电压 | `.voltage` |

接收中断完成校验和解析后，会更新下面两个全局变量：

```c
extern volatile BLDC_MotorData_t BLDC_Motor1;
extern volatile BLDC_MotorData_t BLDC_Motor2;
```

数据结构如下：

```c
typedef struct {
    int16_t  speed;         // RPM
    int32_t  multi_angle;   // 0.1°
    uint16_t single_angle;  // 0.1°
    int16_t  acc;           // 转/s²
    uint16_t voltage;       // 0.01 V
    uint8_t  data_ready;    // 收到新数据后置 1
} BLDC_MotorData_t;
```

读取速度示例：

```c
BLDC_Motor1.data_ready = 0;
BLDC_ReqFeedback(BLDC_ADDR_1, FB_SPEED);

// 后续在主循环中检查，避免阻塞等待
if (BLDC_Motor1.data_ready != 0U) {
    int16_t speed_rpm = BLDC_Motor1.speed;
    BLDC_Motor1.data_ready = 0U;
    // 使用 speed_rpm
}
```

依次请求两台电机时，命令之间建议保留约 10 ms 间隔：

```c
BLDC_ReqFeedback(BLDC_ADDR_1, FB_SPEED);
mspm0_delay_ms(10);
BLDC_ReqFeedback(BLDC_ADDR_2, FB_SPEED);
```

## 6. 底层通信函数

以下函数通常由 `BLDC_*` API 内部调用，普通应用不需要直接使用。

### `void BLDC_SendCmd(uint8_t addr, uint8_t cmd, uint8_t *data, uint8_t len)`

组装并发送完整 F32C 协议帧，包括帧头、地址、功能码、数据、BCC 和帧尾。

### `uint8_t Calc_BCC(uint8_t *data, uint8_t len)`

计算 BLDC 协议使用的逐字节异或校验值。

### `void BLDC_ParseRxData(uint8_t rx_byte)`

逐字节解析 9 字节反馈帧。由 UART1 RX 中断调用，不应在主循环中重复调用。

### `void usart1_send(uint8_t data)`

通过云台 UART 发送一个字节。

### `void USART1_SEND(uint8_t *data, uint8_t len)`

通过云台 UART 发送一个字节数组。

### `void uart1_send_data(uint8_t data)`

`usart1_send()` 的兼容包装函数。

### `void uart1_send_SendArray(uint8_t *data, uint8_t len)`

`USART1_SEND()` 的兼容包装函数。

### `uint8_t BCC_Sum1(uint8_t *usart_data, unsigned char count)`

兼容旧参考工程的 BCC 异或校验函数。

### `void UART_GIMBAL_INST_IRQHandler(void)`

云台 UART 接收中断函数。宏展开后的实际中断符号为 `UART1_IRQHandler`，由中断向量自动调用。

## 7. 常用控制示例

### 两个电机速度控制

```c
SYSCFG_DL_init();
SysTick_Init();
Gimbal_Init();

BLDC_SetSpeed(BLDC_ADDR_1, 10);
mspm0_delay_ms(10);
BLDC_SetSpeed(BLDC_ADDR_2, -10);
```

### 停止两个电机

```c
BLDC_SetSpeed(BLDC_ADDR_1, 0);
mspm0_delay_ms(10);
BLDC_SetSpeed(BLDC_ADDR_2, 0);
```

如果需要同时关闭输出：

```c
mspm0_delay_ms(10);
BLDC_Disable(BLDC_ADDR_1);
mspm0_delay_ms(10);
BLDC_Disable(BLDC_ADDR_2);
```

### 速度模式切换到位置模式

```c
BLDC_SetSpeed(BLDC_ADDR_1, 0);
mspm0_delay_ms(10);
BLDC_SetMode(BLDC_ADDR_1, MODE_SINGLE_POS);
mspm0_delay_ms(1);
BLDC_SetSingleAngle(BLDC_ADDR_1, 1800);  // 180.0°
```

## 8. 使用注意事项

1. 必须先执行 `SysTick_Init()`，否则 `Gimbal_Init()` 中的毫秒延时无法结束。
2. 必须先执行 `Gimbal_Init()`，再发送速度或位置命令。
3. 同一 UART 总线上的电机地址不能重复。
4. 连续发送不同电机命令时建议间隔 10 ms；初始化和模式切换命令至少间隔 1 ms。
5. 调试位置模式前，应限制云台机械行程，防止撞到限位。
6. 第一次测试建议使用低转速，并将云台或车辆架空。
7. `BLDC_SaveParams()`、`BLDC_FactoryReset()`、`BLDC_SetAddress()` 和零点设置函数不应在周期循环中反复调用。
8. UART1 的 PA8/PA9 已分配给云台，不能同时连接旧蓝牙模块或其他串口设备。
9. OLED 显示继续使用 BalanceCarNew 原有的 OLED 驱动，不需要引用参考工程中的 OLED 文件。

