#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <stdint.h>

/* Legacy Bluetooth application API, transported by Hostcom on PA25/PA26. */
void Bluetooth_Init(void);
void Bluetooth_SendString(const char *text, uint16_t max_len);
void Bluetooth_SendData(float value1, float value2);

#endif
