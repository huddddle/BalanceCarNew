  /**************************************************************************
×÷Õß£ºÆ½ºâÐ¡³µÖ®¼Ò
ÎÒµÄÌÔ±¦Ð¡µê£ºhttp://shop114407458.taobao.com/
**************************************************************************/

#ifndef __DATA_PRTOCOL_H
#define __DATA_PRTOCOL_H
 
#include <stdint.h>
#include <stdbool.h>

// --- Ð­Òé¶¨Òå ---
#define BLDC_HEADER     0x7A
#define BLDC_TAIL       0x7B

// Ä¬ÈÏµØÖ·
#define BLDC_ADDR_1     0x01
#define BLDC_ADDR_2     0x02

// ¹¦ÄÜÂë
#define CMD_ENABLE      0x06
#define CMD_DISABLE     0x05
#define CMD_MODE        0x00
#define CMD_SPEED       0x01
#define CMD_MULTI_POS   0x02
#define CMD_SINGLE_POS  0x03
#define CMD_FEEDBACK    0x0E
#define CMD_ACC         0x07        // ÉèÖÃ¼ÓËÙ¶È (±í 8)
#define CMD_SAVE        0x08        // ±£´æ²ÎÊýµ½ÉÁ´æ (±í 9)
#define CMD_CLEAR_MULTI 0x09        // ¶àÈ¦½Ç¶ÈÇåÁã (±í 10)
#define CMD_SET_ZERO    0x0A        // µ¥È¦¾ø¶Ô½Ç¶ÈÖÃÁã (±í 11)
#define CMD_FACTORY_RST 0x0B        // »Ö¸´³ö³§ÉèÖÃ (±í 12)
#define CMD_SET_ADDR    0x0D        // ÉèÖÃµç»úµØÖ· (±í 13)
// Ä£Ê½
#define MODE_SPEED          0x0000
#define MODE_MULTI_POS      0x0001
#define MODE_SINGLE_POS     0x0002
#define MODE_MULTI_POS_L      0x0003
#define MODE_SINGLE_POS_L     0x0004
// ·´À¡ÀàÐÍ
#define FB_SPEED        0x00
#define FB_MULTI_ANGLE  0x01
#define FB_SINGLE_ANGLE 0x02
#define FB_ACC          0x03
#define FB_VOLTAGE      0x04

// --- µç»úÊý¾Ý½á¹¹Ìå ---
typedef struct {
    int16_t  speed;         // ×ªËÙ (RPM)
    int32_t  multi_angle;   // ¶àÈ¦½Ç¶È (¶È*10)
    uint16_t single_angle;  // µ¥È¦½Ç¶È (¶È*10)
    int16_t  acc;           // ¼ÓËÙ¶È (×ª/s2)
    uint16_t voltage;       // Ä¸ÏßµçÑ¹ (0.01V)
    uint8_t  data_ready;    // Êý¾Ý¸üÐÂ±êÖ¾Î»
} BLDC_MotorData_t;

// --- È«¾Ö±äÁ¿ ---
extern volatile BLDC_MotorData_t BLDC_Motor1;  // µØÖ·0x01
extern volatile BLDC_MotorData_t BLDC_Motor2;  // µØÖ·0x02
uint8_t Calc_BCC(uint8_t *data, uint8_t len);
// --- API ---
void BLDC_SendCmd(uint8_t addr, uint8_t cmd, uint8_t *data, uint8_t len);
void BLDC_Enable(uint8_t addr);
void BLDC_Disable(uint8_t addr);
void BLDC_SetSpeed(uint8_t addr, int16_t rpm);
void BLDC_SetMode(uint8_t addr, uint16_t mode);
void BLDC_ReqFeedback(uint8_t addr, uint8_t type);
void BLDC_SetMultiAngle(uint8_t addr, int32_t angle_x10);
void BLDC_SetSingleAngle(uint8_t addr, uint16_t angle_x10);


// --- ---
void BLDC_SetAcc(uint8_t addr, uint16_t acc);             // ÉèÖÃ¼ÓËÙ¶È (µ¥Î»£º×ª/s2)
void BLDC_SaveParams(uint8_t addr);                       // ±£´æ²ÎÊýµ½ÉÁ´æ
void BLDC_ClearMultiAngle(uint8_t addr);                  // ¶àÈ¦½Ç¶ÈÇåÁã
void BLDC_SetSingleAngleZero(uint8_t addr);               // µ±Ç°Î»ÖÃÉèÎªµ¥È¦Áãµã
void BLDC_FactoryReset(uint8_t addr);                     // »Ö¸´³ö³§ÉèÖÃ
void BLDC_SetAddress(uint8_t addr, uint8_t new_addr);     // ÐÞ¸Äµç»úµØÖ·

// ´®¿ÚÖÐ¶Ï½âÎöº¯Êý£¨ÔÚUSART3_IRQHandlerÖÐµ÷ÓÃ£©
void BLDC_ParseRxData(uint8_t rx_byte);

// ±ã½Ýºê¶¨Òå
//#define BLDC1_Enable()          BLDC_Enable(BLDC_ADDR_1)
//#define BLDC1_Disable()         BLDC_Disable(BLDC_ADDR_1)
//#define BLDC1_SetSpeed(rpm)     BLDC_SetSpeed(BLDC_ADDR_1, rpm)
//#define BLDC1_SetMode(mode)     BLDC_SetMode(BLDC_ADDR_1, mode)
//#define BLDC1_SetMultiAngle(a)  BLDC_SetMultiAngle(BLDC_ADDR_1, a)
//#define BLDC1_SetSingleAngle(a) BLDC_SetSingleAngle(BLDC_ADDR_1, a)
//#define BLDC1_ReqFeedback(t)    BLDC_ReqFeedback(BLDC_ADDR_1, t)

//#define BLDC2_Enable()          BLDC_Enable(BLDC_ADDR_2)
//#define BLDC2_Disable()         BLDC_Disable(BLDC_ADDR_2)
//#define BLDC2_SetSpeed(rpm)     BLDC_SetSpeed(BLDC_ADDR_2, rpm)
//#define BLDC2_SetMode(mode)     BLDC_SetMode(BLDC_ADDR_2, mode)
//#define BLDC2_SetMultiAngle(a)  BLDC_SetMultiAngle(BLDC_ADDR_2, a)
//#define BLDC2_SetSingleAngle(a) BLDC_SetSingleAngle(BLDC_ADDR_2, a)
//#define BLDC2_ReqFeedback(t)    BLDC_ReqFeedback(BLDC_ADDR_2, t)

#endif

