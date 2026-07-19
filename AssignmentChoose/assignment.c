#include "Motor.h"
#include "global.h"
#include "interrupt.h"
#include "move.h"
#include "main.h"
#include "pid.h"
#include "servo.h"
#include "speed.h"
#include "stdio.h"
#include "stdlib.h"
#include "ti_msp_dl_config.h"
#include "turn.h"
#include "assignment.h"
#include "move.h"
#include "bluetooth.h"
#include "control.h"


static SoftTimer_t Assitimer = {0, false};
uint8_t LeftTurnFlag=0;
uint8_t RightTurnFlag=0;
uint8_t TurnOverFlag=0;

//定义距离默认值
float l1 = 9.9;
float l2 = 3.3;

uint8_t assignmentFlag = 0;
uint8_t Number_of_circle = 0;
uint8_t shapeFlag = 0; // 0:圆形, 1:正方形, 2:三角形, 3:椭圆形
const char *shapeStrings[4] = {
    "Triangle", 
    "Square  ", 
    "Circle  ", 
    "Ellipse "
};


void AssignmentChoose(void) 
{
  OLED_Clear();
  Bluetooth_SendString("Please choose assignment\r\n", 50);
  // ----- 第一阶段：选择任务 -----
  while (DL_GPIO_readPins(Assignment_ButtonRight_PORT, Assignment_ButtonRight_PIN)) 
  {
    OLED_ShowString(0, 0, (uint8_t *)"Assignment:", 8);
    sprintf((char *)oled_buffer, "%d", assignmentFlag);
    OLED_ShowString(9 * 8, 0, oled_buffer, 16);

    if (!DL_GPIO_readPins(Assignment_ButtonLeft_PORT, Assignment_ButtonLeft_PIN)) 
    {
      assignmentFlag++;
      assignmentFlag %= 6; // 假设任务编号为 0~5
      mspm0_delay_ms(300); // 延时消抖
    }
  }

  // 等待右键（确认键）完全释放，防止直接穿透到下一个选择界面
  while (!DL_GPIO_readPins(Assignment_ButtonRight_PORT, Assignment_ButtonRight_PIN));
  mspm0_delay_ms(20); // 释放后的去抖
  OLED_Clear();

  // ----- 第二阶段：选择图形 -----
  while (DL_GPIO_readPins(Assignment_ButtonRight_PORT, Assignment_ButtonRight_PIN)) 
  {
    OLED_ShowString(0, 0, (uint8_t *)"Shape:", 8);
    // 在第二行显示对应的图形英文名称
    OLED_ShowString(0, 2, (uint8_t *)shapeStrings[shapeFlag], 16); 

    if (!DL_GPIO_readPins(Assignment_ButtonLeft_PORT, Assignment_ButtonLeft_PIN)) 
    {
      shapeFlag++;
      shapeFlag %= 4; // 共有4种图形
      mspm0_delay_ms(300); // 延时消抖
    }
  }

  // 等待右键再次释放，确保安全退出设置界面
  while (!DL_GPIO_readPins(Assignment_ButtonRight_PORT, Assignment_ButtonRight_PIN));

  OLED_Clear();
  LightAndSound();
  return;
}

int Assig1=0;
void assignment1(void) 
{
  if(!Assig1)
  {
      DL_TimerA_startCounter(TIMER_Balance_INST);
      Assig1++;
  }
  // balance_stand();

}

void assignment2(void) {

  if (turnFlag > 6 || turnFlag < 0) {
    zeroparameter();
    backwords();
    mspm0_delay_ms(500);
    stop();
    LightAndSound();
    return;
  }

  if (LeftTurnFlag == 0 && RightTurnFlag == 0 && TurnOverFlag == 0) {
    Tracking();
  } else {
    if (turnCompleted == 3 && turnFlag == 4) {
      Left_Turn(179);
    } else if (LeftTurnFlag == 1) {
      Left_Turn(89);
    } else if (RightTurnFlag == 1) {
      Right_Turn(87);
    }
  }
}

void assignment3(void) 
{
    if (turnFlag > 4 || turnFlag<0 ) 
  {
    zeroparameter();
    backwords();
    mspm0_delay_ms(500);
    stop();
    LightAndSound();
    Bluetooth_SendData(l1, l2);
    return;
  }
  if (LeftTurnFlag==0&&RightTurnFlag==0&&TurnOverFlag==0)
  {
    Tracking();
  }
  else if(LeftTurnFlag==1)
  {
    Left_Turn(88);
  }
  else if(RightTurnFlag==1)
  {
    Right_Turn(87);
  }
  else if(TurnOverFlag==1)
  {
    Left_Turn(181);
  }
}
void assignment4(void) 
{
  if (turnFlag > 4) 
  {
    stop();
    parking();
    zeroparameter();
    LightAndSound();
    return;
  }
  if (LeftTurnFlag == 0 && RightTurnFlag == 0 && TurnOverFlag == 0) {
    Tracking();
  } else if (LeftTurnFlag == 1) {
    Left_Turn(88.0);
  } else if (RightTurnFlag == 1) {
    Right_Turn(88.0);
  } else if (TurnOverFlag == 1) {
    Left_Turn(181.0);
  }
}

void assignment5(void) 
{
  if (turnFlag > 4 || turnFlag<0 ) 
  {
    zeroparameter();
    backwords();
    mspm0_delay_ms(500);
    stop();
    LightAndSound();
    return;
  }
  if (LeftTurnFlag==0&&RightTurnFlag==0&&TurnOverFlag==0)
  {
    Tracking();
  }
  else if(LeftTurnFlag==1)
  {
    Left_Turn(88);
  }
  else if(RightTurnFlag==1)
  {
    Right_Turn(88);
  }
  else if(TurnOverFlag==1)
  {
    Left_Turn(181);
  }
}

// 云台角度测试：1 号电机在 90.0° 和 120.0° 之间往返。
void assignment0(void)
{
  static uint8_t initialized = 0U;
  static uint8_t move_to_point_b = 1U;
  static unsigned long last_move_ms = 0UL;
  const uint16_t point_a_x10 = 900U;
  const uint16_t point_b_x10 = 1200U;

  if (initialized == 0U)
  {
    /* 先停止两个轴，再将 1 号电机切换到单圈位置模式。 */
    BLDC_SetSpeed(BLDC_ADDR_1, 0);
    mspm0_delay_ms(10);
    BLDC_SetSpeed(BLDC_ADDR_2, 0);
    mspm0_delay_ms(10);
    BLDC_SetMode(BLDC_ADDR_1, MODE_SINGLE_POS);
    mspm0_delay_ms(1);
    BLDC_SetSingleAngle(BLDC_ADDR_1, point_a_x10);

    last_move_ms = tick_ms;
    initialized = 1U;
    return;
  }

  /* 使用 SysTick 做非阻塞计时，不影响主循环的视觉和传感器更新。 */
  if ((unsigned long)(tick_ms - last_move_ms) >= 500UL)
  {
    if (move_to_point_b != 0U)
    {
      BLDC_SetSingleAngle(BLDC_ADDR_1, point_b_x10);
      move_to_point_b = 0U;
    }
    else
    {
      BLDC_SetSingleAngle(BLDC_ADDR_1, point_a_x10);
      move_to_point_b = 1U;
    }

    last_move_ms = tick_ms;
  }
}

void LightAndSound(void)
{
  DL_GPIO_setPins(BEE_PORT, BEE_Bee_Port_PIN );

  DL_GPIO_togglePins(LED_PORT,  LED_USER_LED_PIN);
  delay_ms(200);
  DL_GPIO_togglePins(LED_PORT,  LED_USER_LED_PIN);
  delay_ms(200);
  DL_GPIO_togglePins(LED_PORT,  LED_USER_LED_PIN);
  delay_ms(200);
  DL_GPIO_togglePins(LED_PORT,  LED_USER_LED_PIN);
  delay_ms(200);
  
  DL_GPIO_clearPins(BEE_PORT, BEE_Bee_Port_PIN );
}

void zeroparameter(void)
{
    CrossingFlag = 0;
    LeftTurnFlag = 0;
    RightTurnFlag = 0;
    turnCompleted = 0;
    assignmentFlag = 0;
    TurnOverFlag = 0;
}
