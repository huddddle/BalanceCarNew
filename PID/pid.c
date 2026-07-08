#include "pid.h"
#include "Motor.h"
#include"global.h"

// PID结构体
PID SpeedPID = {1, 0.005, 0}; // 4,0.02,0//////////1,0.05,0
PID TurnPID = {1, 0, 0};

static float PID_Limit(float value, float limit)
{
  if (limit <= 0.0f) {
    return value;
  }

  if (value > limit) {
    return limit;
  }
  if (value < -limit) {
    return -limit;
  }
  return value;
}

float Loca_PID(LocaPID_t *controller, float error)
{
  if (controller == 0) {
    return 0.0f;
  }

  controller->integral += error;
  controller->integral = PID_Limit(controller->integral, controller->integral_limit);

  float output = controller->gain.Kp * error +
                 controller->gain.Ki * controller->integral +
                 controller->gain.Kd * (error - controller->last_error);

  controller->last_error = error;
  output = PID_Limit(output, controller->output_limit);

  if (controller->output_deadband > 0.0f &&
      output < controller->output_deadband &&
      output > -controller->output_deadband) {
    return 0.0f;
  }

  return output;
}

void Loca_PID_Reset(LocaPID_t *controller)
{
  if (controller == 0) {
    return;
  }

  controller->integral = 0.0f;
  controller->last_error = 0.0f;
}

// 速度PID控制器 (改为标准增量式算法)
int Speed(PID *Example, int True_Speed, int Target_Speed) {
  static int Error = 0, Last_Error = 0, Last_Last_Error = 0;
  float Delta_PWM = 0;

  Error = Target_Speed - True_Speed; // 计算当前偏差

  // 增量式公式: Delta = Kp*(E - E1) + Ki*E + Kd*(E - 2*E1 + E2)
  Delta_PWM = Example->Kp * (Error - Last_Error) + 
              Example->Ki * Error + 
              Example->Kd * (Error - 2 * Last_Error + Last_Last_Error);

  Last_Last_Error = Last_Error;
  Last_Error = Error;

  return (int)Delta_PWM;
}

