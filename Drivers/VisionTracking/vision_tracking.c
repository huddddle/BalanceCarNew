#include "vision_tracking.h"
#include "hostcom.h"
#include "oled_hardware_i2c.h"
#include <stdio.h>

VisionData_t vision_data = {0};

void Vision_Init(void)
{
    Host_Receive_Start();

    OLED_Clear();
    OLED_ShowString(0, 0, (uint8_t *)"Raw:", 8);
    OLED_ShowString(0, 2, (uint8_t *)"Err:", 8);
    OLED_ShowString(0, 4, (uint8_t *)"Dat:", 8);
}

void Vision_Update(void)
{
    if (Host_Receive_Process() == false) {
        return;
    }

    vision_data.error = g_Host_Var2;
    vision_data.data = ((g_Host_Var3 >= '0') && (g_Host_Var3 <= '9'))
        ? (uint8_t)(g_Host_Var3 - '0')
        : (uint8_t)g_Host_Var3;
    vision_data.valid = 1U;
    vision_data.updated = 1U;
    vision_data.frame_count++;
    snprintf(vision_data.raw, sizeof(vision_data.raw), "%c,%+06d,%c",
        g_Host_Var1, (int)g_Host_Var2, g_Host_Var3);
}

void Vision_ShowOLED(void)
{
    static char buffer[20];

    snprintf(buffer, sizeof(buffer), "%-11s", vision_data.raw);
    OLED_ShowString(4 * 8, 0, (uint8_t *)buffer, 8);

    snprintf(buffer, sizeof(buffer), "%-6d", vision_data.error);
    OLED_ShowString(4 * 8, 2, (uint8_t *)buffer, 8);

    snprintf(buffer, sizeof(buffer), "%-3u", (unsigned)vision_data.data);
    OLED_ShowString(4 * 8, 4, (uint8_t *)buffer, 8);
}
