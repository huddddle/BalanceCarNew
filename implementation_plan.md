# 平衡车：云台支持 + 串口通信重构

## 背景分析

通过对项目的全面梳理，当前的串口资源如下：

| 逻辑名 (syscfg)                                           | 硬件外设  | 引脚                  | 波特率                | 当前用途                                        |
| ------------------------------------------------------ | ----- | ------------------- | ------------------ | ------------------------------------------- |
| `UART_WIT`                                             | UART0 | PA11 (RX only)      | 115200             | WIT IMU（DMA接收）                              |
| `UART_1` (syscfg) / `UART_BT` (ti_msp_dl_config.h 旧生成) | UART1 | PA8(TX) / PA9(RX)   | 9600/115200 (不同步!) | 云台BLDC（uart_callback.c）/ 蓝牙（bluetooth.c）冲突！ |
| `UART_VISION`                                          | UART3 | PA25(RX) / PA26(TX) | 115200             | 视觉追踪（DMA接收）                                 |
| `UART_0` (hostcom)                                     | UART3 | PA25/PA26           | 115200             | Hostcom（DMA TX/RX）与VISION冲突！                |

> [!CAUTION]
> **发现两处严重冲突：**
> 1. `**UART_BT` (ti_msp_dl_config.h) vs `UART_1` (syscfg)** — 同一硬件UART1/PA8-PA9，syscfg配置为115200（云台），而旧生成文件还保留了9600波特率的蓝牙配置。bluetooth.c和uart_callback.c（云台收发）都在用同一UART。
> 2. `**UART_0` (hostcom.c) vs `UART_VISION**` — 都指向UART3/PA25-PA26，hostcom只负责TX+DMA，vision_tracking只负责RX+DMA，实际上可以**共存**：hostcom TX用UART3，vision RX用UART3，这是允许的（TX和RX方向不同）。

## 设计决策

> [!IMPORTANT]
> **核心架构决定：**
> - **PA8(TX)/PA9(RX) = UART1 硬件 → 专用于云台BLDC**，在syscfg重命名为 `UART_GIMBAL`
> - **移除 `uart_callback.c` 的底层UART发送** → 改为调用 `hostcom` 作为底层驱动层（但云台用的是UART1，hostcom用的是UART3，实际上需要为云台建立独立的底层发送函数）
> - **Bluetooth** 目前使用 `UART_BT_INST`（UART1/PA8/PA9），与云台完全冲突 → **bluetooth.c 的底层发送改为走 Hostcom（UART3/PA25/PA26）**
> - **Hostcom** 保持使用 UART3（PA25/PA26）作为底层，是所有上层应用的统一出口

> [!NOTE]
> **UART3 TX（PA26）分配给 Hostcom，UART3 RX（PA25）同时被 VisionTracking 的 DMA 使用——这在硬件上完全合法，UART收发方向独立，不冲突。**

### 最终串口分配

| 硬件    | 引脚                | 名称                       | 用途                                                     |
| ----- | ----------------- | ------------------------ | ------------------------------------------------------ |
| UART0 | PA11 (RX)         | `UART_WIT`               | WIT IMU（只读，DMA）                                        |
| UART1 | PA8(TX)/PA9(RX)   | `UART_GIMBAL`            | 云台BLDC双向通信，115200，中断接收                                 |
| UART3 | PA25(RX)/PA26(TX) | `UART_0` / `UART_VISION` | TX→Hostcom输出，RX→Vision（走Hostcom）协议，进行少量移植，告诉我视觉应该发送的格式 |

---

## 拟修改文件清单

### 1. SysCfg 配置

#### [MODIFY] [mspm0-modules.syscfg](file://d:\Electric\My_TI_Workspace\BalanceCarNew\mspm0-modules.syscfg)

将 `UART2`（当前名称 `UART_1`，对应 UART1 硬件，PA8/PA9）重命名为 `UART_GIMBAL`，配置115200波特率，启用RX中断。

### 2. GBControl 驱动层（云台核心）

#### [MODIFY] [uart_callback.c](file://d:\Electric\My_TI_Workspace\BalanceCarNew\Drivers\GBControl\uart_callback.c)

- **完全重写**：删除旧的 `UART_1_INST` 底层发送包装，改为直接操作 `UART_GIMBAL_INST`
- 注册 `UART_GIMBAL_INST_IRQHandler` 用于接收云台反馈（替换原 `UART_1_INST_IRQHandler`）
- 保留 `BLDC_ParseRxData()` 回调的调用

#### [MODIFY] [uart_callback.h](file://d:\Electric\My_TI_Workspace\BalanceCarNew\Drivers\GBControl\uart_callback.h)

- 更新函数声明，去除旧的 `UART_1` 命名

#### [MODIFY] [DataScope_DP.C](file://d:\Electric\My_TI_Workspace\BalanceCarNew\Drivers\GBControl\DataScope_DP.C)

- 更新 `BLDC_SendCmd()` 底层调用，使用 `UART_GIMBAL_INST` 直接发送（不再通过旧的uart_callback）

### 3. Hostcom 底层驱动（统一发送出口）

#### [MODIFY] [hostcom.h](file://d:\Electric\My_TI_Workspace\BalanceCarNew\Drivers\Hostcom\hostcom.h)

- 保留原有 `Host_Send()` 格式化接口（重要，请勿更改，底层也不要改，上层直接调用这个函数）

#### [MODIFY] [hostcom.c](file://d:\Electric\My_TI_Workspace\BalanceCarNew\Drivers\Hostcom\hostcom.c)

- 保留与hostcom原来的 `UART_0_INST`

### 4. Bluetooth 驱动（应用层，改用Hostcom底层）

#### [MODIFY] [bluetooth.c](file://d:\Electric\My_TI_Workspace\BalanceCarNew\Drivers\Bluetooth\bluetooth.c)

- 将 `DL_UART_transmitDataBlocking(UART_BT_INST, ...)` 替换为 `对`
  `Host_Send()的包装`

#### [MODIFY] [bluetooth.h](file://d:\Electric\My_TI_Workspace\BalanceCarNew\Drivers\Bluetooth\bluetooth.h)

- 去除 `UART_BT_INST` 依赖

### 5. control.h（syscfg配置教程）

#### [MODIFY] [control.h](file://d:\Electric\My_TI_Workspace\BalanceCarNew\Drivers\GBControl\control.h)

- 在文件开头增加**详细的 SysConfig 配置步骤注释**，描述如何配置 `UART_GIMBAL`（PA8/PA9，UART1，115200，TX+RX，无DMA，启用RX中断）

### 6. main.c（初始化云台）

#### [MODIFY] [main.c](file://d:\Electric\My_TI_Workspace\BalanceCarNew\main.c)

- 添加 `#include "DataScope_DP.h"` 和 `#include "uart_callback.h"` 
- 在 `SYSCFG_DL_init()` 之后添加云台初始化代码：启用 UART_GIMBAL NVIC 中断，发送使能指令

---

> [!IMPORTANT]
> 1. 蓝牙模块已拆除/弃用，可以直接删除 bluetooth.c 的发送调用
> 2. **Hostcom 发送格式** — 当前 `Host_Send()` 的格式是 `$var1,var2,var3#`（12字节定长）。保持兼容，上位机协议一致。
> `**UART_0_INST` vs `UART_VISION_INST**` — hostcom.c 目前使用的是 `UART_0_INST`（syscfg 中的 `UART_0`，实际也是UART3）。由于 `UART_VISION_INST` 也是UART3，生成的 `ti_msp_dl_config.h` 里两者实际上是同一个寄存器，直接改名即可，无需改硬件配置。统一用改名为`UART_3`
