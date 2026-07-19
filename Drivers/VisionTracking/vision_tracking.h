#ifndef VISION_TRACKING_H
#define VISION_TRACKING_H

#include <stdint.h>

/* Vision is an application layer over Hostcom's fixed 12-byte frame. */
typedef struct {
    char raw[16];
    int16_t error;
    uint8_t data;
    uint8_t valid;
    uint8_t updated;
    uint32_t frame_count;
} VisionData_t;

extern VisionData_t vision_data;

void Vision_Init(void);
void Vision_Update(void);
void Vision_ShowOLED(void);

#endif
