# BalanceCarNew 控制环记录与建议

## 本次代码调整

- 直立环角度源应使用 `wit_data.roll`，不是 `wit_data.pitch`。当前 `balance_stand()` 已按 `roll` 计算误差。
- 在 `PID/pid.c` 中新增了位置式 PID 封装函数 `Loca_PID()`，并保留原来的增量式 `Speed()`，避免影响已有速度闭环代码。
- `Loca_PID()` 使用独立的 `LocaPID_t` 状态结构保存积分项和上一次误差，避免直立环、速度环、转向环共用同一组静态误差。
- `LocaPID_t` 现在包含 `integral_limit`、`output_limit` 和 `output_deadband`。最大输出和最小有效输出都集中在 PID 结构体里，控制函数里不再散落多个限幅变量。
- `balance_stand()` 当前仍然只输出直立环 PWM，速度环和转向环没有接入最终电机输出，方便你按顺序调参。
- 在 `balance_stand()` 后面新增了两个暂不调用的计算函数：
  - `balance_speed_pwm(int target_speed)`：用左右编码器速度平均值计算速度环 PWM。
  - `balance_turn_pwm(float target_yaw)`：用 yaw 误差计算转向环 PWM。
- `Move/move.c` 中新增了 `BalanceTimerInit()` 和 `TIMER_Balance_INST_IRQHandler()`。`TIMER_Balance` 目前是 5ms one-shot 定时器，ISR 在 ZERO 事件里执行一次直立环，然后重新启动定时器，形成 200Hz 控制节拍。

## 当前代码结构建议

- 三环最终可以按这个形式叠加：
  - `left_pwm = upright_pwm + speed_pwm + turn_pwm`
  - `right_pwm = upright_pwm + speed_pwm - turn_pwm`
- 现在建议继续只调 `upright_pwm`，不要急着打开速度环。直立环站不稳时，速度环会把问题掩盖掉。
- 速度环函数里我按平衡车常见正反馈思路写了 `speed_error = current_speed - target_speed`。后续一旦接入，第一步必须做极性检查。
- 转向环现在是 yaw 位置式 PID。真正用于平衡车转向时，通常可以先只用 P，之后再根据 `wit_data.gz` 或 yaw 误差变化补 D。

## 你现在现象的判断

你描述的是“有抑制倾斜的回正，但是无法遏制倾倒趋势，无法真正回正”。这通常不是单纯缺少速度环，而是直立环还没有把“追赶重心”的力度和阻尼调到位。

优先检查这几件事：

1. **极性**：车体向前倒时，轮子必须向前追；车体向后倒时，轮子必须向后追。如果方向反了，Kp/Kd 怎么调都救不回来。
2. **机械零点**：`target_roll = -9.0f` 必须是断电手扶时真正临界平衡的角度。如果零点偏了，车会一直认为自己有误差，只能持续跑。
3. **Kp 是否偏小**：如果能感觉到回正，但追不上倒下速度，多数是 Kp 不够，电机没有足够快地追重心。
4. **Kd 是否偏小或方向不合适**：如果车体已经开始倒下，控制还显得迟缓，说明阻尼不够。当前 D 项来自角度误差差分，后续更建议用 `wit_data.gx` 作为 roll 角速度来源。
5. **控制周期**：直立环最好固定在 5ms 左右执行。如果现在放在 `while(1)` 里，OLED、串口、delay 或任务逻辑都会让周期抖动，D 项会跟着乱。

## 关于 `wit_data.gz` 的控制思路

先区分两个概念：`wit_data.roll/yaw` 是角度，`wit_data.gx/gy/gz` 是角速度。角度告诉你“现在偏了多少”，角速度告诉你“正在往哪个方向倒/转，以及倒/转得多快”。平衡车要遏制倾倒趋势，最关键的是利用角速度提前刹住趋势，而不是等角度已经变大以后才补救。

`wit_data.gz` 通常是 Z 轴角速度，也就是 yaw 方向的旋转速度。因此它最适合放在转向环里，用来抑制转向过冲：

```c
turn_pwm = Kp_turn * yaw_error - Kd_turn * wit_data.gz;
```

这个公式的含义是：如果小车还没转到目标方向，`yaw_error` 会给它一个转向力；如果它已经在快速朝目标方向转，`gz` 会提供阻尼，提前收力，防止冲过头。符号不一定永远是减号，因为 WIT 的安装方向和你的左右电机正反定义会影响极性。实车检查方式是：手动让车朝 yaw 增大的方向旋转，观察 `wit_data.gz` 的正负；如果加入 `gz` 后转向更容易发散，就把 D 项符号反过来。

但如果你说的是“直立环无法遏制倾倒趋势”，那不应该优先用 `gz`。直立环现在用的是 `roll`，理论上应该配合 roll 轴角速度，常见对应是 `wit_data.gx`。更稳的直立环写法通常是：

```c
upright_pwm = Kp_up * (wit_data.roll - target_roll) + Kd_up * roll_gyro;
```

这里的 `roll_gyro` 要通过实测确认，常见是 `wit_data.gx`，也可能因为模块安装旋转而变成 `wit_data.gy` 或符号相反。判断方法是：固定车轮，手扶车体沿当前“roll 倾倒方向”快速前后晃动，看 `gx/gy/gz` 哪个变化最大，那个轴就是直立环 D 项应该用的角速度。用陀螺仪角速度做 D 项，比用 `roll_error - last_roll_error` 更直接，延迟更小，对“已经开始倒下”的趋势抑制更有效。

我的建议是：转向环用 `gz`；直立环不要盲目用 `gz`，先找出 roll 对应的 gyro 轴，再把角度差分 D 项替换成对应的 gyro D 项。

## 调参顺序

1. 先只保留直立环，速度环、转向环输出保持不用。
2. 固定 `target_roll`，确认手扶临界点附近 `roll_error` 接近 0。
3. 逐步增加 `Kp_balance`，直到车能明显主动追重心，但开始出现来回抖动。
4. 再逐步增加 `Kd_balance`，让抖动收敛，车体变得有阻尼感。
5. 如果加大 Kd 后反而更快倒，先不要继续加参数，优先检查 D 项极性，或改用 `wit_data.gx`。
6. 直立环能短暂站住后，再接速度环，最后才接转向环。

## 额外代码建议

- `Right_Control()` 中 `speed <= 0` 会被强制改成 `10`，所以 `Right_Control(1, 0)` 不是严格停止。需要停车时优先用 `TB6612_Motor_Stop()`。
- 当前 `balance_stand()` 已经通过 `output_deadband` 让小 PWM 归零，并在零输出时调用 `TB6612_Motor_Stop()`，避免保留上一次 PWM。
- 速度环建议 20Hz 左右执行，不要和 200Hz 直立环同频；编码器速度需要一点采样窗口，否则量化噪声会很明显。
- 位置式 PID 的积分项必须有限幅，尤其速度环打开后，否则积分饱和会让小车突然冲出去。

## TIMER_Balance 不进中断的排查记录

这次只做代码排查，没有直接修改控制代码。当前最可疑的问题不是 SysConfig 没生成定时器，也不是中断函数名字写错，而是 **NVIC 没有真正打开 `TIMER_Balance_INST_INT_IRQN`**。

我看到的关键事实：

1. `mspm0-modules.syscfg` 里 `TIMER_Balance` 已经配置到 `TIMA0`，周期是 `5 ms`，模式是 `PERIODIC_UP`，中断源是 `ZERO`，并且 `timerStartTimer = true`。
2. `Debug/ti_msp_dl_config.h` 里生成的宏是：`TIMER_Balance_INST = TIMA0`，`TIMER_Balance_INST_IRQHandler = TIMA0_IRQHandler`，`TIMER_Balance_INST_INT_IRQN = TIMA0_INT_IRQn`。
3. `Debug/ti_msp_dl_config.c` 里确实调用了 `DL_TimerA_enableInterrupt(TIMER_Balance_INST, DL_TIMERA_INTERRUPT_ZERO_EVENT)`，所以外设内部的 ZERO 中断源已经打开。
4. `Move/move.c` 里写的是 `void TIMER_Balance_INST_IRQHandler(void)`，这个名字会被宏替换成真正的 `TIMA0_IRQHandler`，工程里也没有搜索到第二个 `TIMA0_IRQHandler` 冲突。
5. `Move/move.c` 里有 `BalanceTimerInit()`，它里面才有 `NVIC_EnableIRQ(TIMER_Balance_INST_INT_IRQN)`，但目前没有看到 `main.c` 或 `assignment1()` 调用它。
6. 当前 `assignment1()` 只调用了 `DL_TimerA_startCounter(TIMER_Balance_INST)`，这只能启动/重启定时器计数，不能打开 NVIC，所以 CPU 仍然不会跳进 ISR。

因此当前最可能的原因是：**定时器已经在计数，ZERO 中断标志也可能已经产生，但 `TIMA0_INT_IRQn` 在 NVIC 侧没有 enable，CPU 不会进入 `TIMA0_IRQHandler`。**

建议检查顺序：

1. 先在 `BalanceTimerInit()` 里打断点，确认它有没有被调用。如果没有被调用，那就是首要问题。
2. 再在 `assignment1()` 里打断点。现在它只 start counter，不 enable NVIC；如果你暂时只在任务 1 里启用平衡定时器，应该让任务 1 调用完整初始化函数，而不是只调用 `DL_TimerA_startCounter()`。
3. 在调试器里观察 `TIMER_Balance_INST_INT_IRQN` 对应的 NVIC enable 位。没开的话，`TIMA0_IRQHandler` 不会进。
4. 如果 NVIC 已经打开但仍不进，再看 `TIMER_Balance_INST->CPU_INT` 相关寄存器：`IMASK` 是否有 ZERO，`RIS/MIS` 是否出现 ZERO 标志，`IIDX` 是否能读到 `DL_TIMERA_IIDX_ZERO`。
5. 如果 `IIDX` 有 ZERO 但断点不进 ISR，再回头检查最终 map 文件里是否真的有 `TIMA0_IRQHandler` 符号来自 `Move/move.o`。

还有一个结构上的小提醒：当前 `TIMER_Balance` 已经是 `PERIODIC_UP`，不是之前的 one-shot，所以 ISR 里理论上不需要每次 `DL_TimerA_startCounter(TIMER_Balance_INST)`。这不是“不进中断”的主要原因，但后续建议把“周期定时器”和“单次重启定时器”的逻辑统一，避免重复 start 带来不必要的不确定性。
