#include "Motor.h"
#include "global.h"
#include "pid.h"
#include "stdlib.h"

//运动学控制
int32_t Left_count = 0;
int32_t Right_count = 0;
int SpeLeft[1000] = {0};
int SpeRight[1000] = {0};
int l = 0, r = 0; // 定义数组索引index
struct SpeedCondition SpeeCon;
int k1,k2;

void Speed_Init(void)
{
  NVIC_EnableIRQ(Encoder_INT_IRQN);      // 开启编码器的中断
  NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN); // 开启定时器中断
  DL_TimerA_startCounter(TIMER_0_INST);  // 开始启用定时器
}

void SpeedRead(void) {

  static int32_t Last_Left_count;
  static int32_t Last_Right_count;

  if (l == 999 || r == 999) {
    l = 0;
    r = 0;
  }
  if (abs(-Left_count + Last_Left_count) < 2000) {
    SpeLeft[l++] = -Left_count + Last_Left_count;
  }
  if (abs(-Right_count + Last_Right_count) < 2000) {
    SpeRight[r++] = -Right_count + Last_Right_count;
  }

  Last_Left_count = Left_count;
  Last_Right_count = Right_count;
}

void SpeedSet(struct SpeedCondition *Spe) {
  static float Current_PWM_L = 0;
  static float Current_PWM_R = 0;

  // 增量式PID返回的是本次调整的增量，需要累加到原有PWM上
  Current_PWM_L += Speed(&SpeedPID, Spe->True_Speed_Left, Spe->Target_Speed_Left);
  Current_PWM_R += Speed(&SpeedPID, Spe->True_Speed_Right, Spe->Target_Speed_Right);

  // 对总输出进行限幅，防止超出驱动能力
  if (Current_PWM_L > 1000) Current_PWM_L = 1000;
  if (Current_PWM_L < -1000) Current_PWM_L = -1000;
  if (Current_PWM_R > 1000) Current_PWM_R = 1000;
  if (Current_PWM_R < -1000) Current_PWM_R = -1000;

  k1 = (int)Current_PWM_L;
  k2 = (int)Current_PWM_R;

  // 执行控制
  if (k1 > 0) Left_Control(1, k1);
  else Left_Control(0, -k1);

  if (k2 > 0) Right_Control(1, k2);
  else Right_Control(0, -k2);
}
//    Speed Controller
    // SpeeCon.Target_Speed_Left = 500;
    // SpeeCon.Target_Speed_Right = 500;
    // if (r != 0)
    //   SpeeCon.True_Speed_Right = SpeRight[r - 1];
    // if (l != 0)
    //   SpeeCon.True_Speed_Left = SpeLeft[l - 1];
    // SpeedSet(&SpeeCon);

