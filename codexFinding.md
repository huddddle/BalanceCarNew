# balance() 实现记录

## 本次修改

- 只修改了 `Move/move.c` 中的 `balance()` 函数体。
- `balance()` 使用现有工程里的 `wit_data.pitch` 作为姿态输入。代码中没有发现名为 `wit.pitch` 的变量，WIT 数据结构在 `global.h` 中定义为 `WIT_Data_t wit_data`。
- 直立环采用 PD 控制：
  - 第一次进入 `balance()` 时，把当前 `wit_data.pitch` 记录为目标直立角 `target_pitch`。
  - 后续用 `pitch_error = wit_data.pitch - target_pitch` 计算角度误差。
  - 用本次误差和上次误差之差作为微分项。
  - 输出 PWM 同时给左右轮，实现最基础的直立控制。
- 增加了 35 度倾倒保护，误差过大时直接调用 `TB6612_Motor_Stop()`。

## 当前参数

- `Kp_balance = 35.0f`
- `Kd_balance = 220.0f`
- `fall_limit = 35.0f`
- `max_balance_pwm = 850`
- `min_effective_pwm = 20`

这些值是起步参数，需要上车后根据实际重心、电机、轮胎和 WIT 安装方向继续调整。

## 调试建议

1. 启动任务前，先手扶小车在直立平衡位置，再进入 `assignment1()`，因为当前目标 pitch 是第一次调用 `balance()` 时记录的值。
2. 如果车身向前倒时轮子也向前跑，导致越倒越快，说明控制方向反了，需要把 `balance_pwm` 的符号取反，或调换 `Left_Control/Right_Control` 的方向逻辑。建议只在 `balance()` 内改，先不要动电机驱动文件。
3. 调参顺序建议先调 `Kp_balance`，让车有明显回正趋势；再逐步增加 `Kd_balance` 抑制抖动。若快速抽搐，先降 `Kd_balance`；若软趴趴扶不住，先升 `Kp_balance`。
4. 当前只是直立环，没有速度环和转向环。车能短时间站住后，下一步建议加入速度环，用编码器速度抑制小车持续漂移。
5. 我发现 `Drivers/Motor/Motor.c` 里的 `Right_Control()` 在 `speed <= 0` 时会强制改成 `10`，所以用 `Right_Control(1, 0)` 不能真正让右电机完全停转。本次没有改函数外代码，而是在 `balance()` 的小输出和倾倒保护里直接使用 `TB6612_Motor_Stop()`。
