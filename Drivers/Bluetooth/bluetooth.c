#include "bluetooth.h"
#include "hostcom.h"
#include <stdio.h>

static void Bluetooth_WaitAndSend(char type, const char *value, char tag)
{
    while (gDMADone_TX == false) {
    }
    (void)Host_Send(type, value, tag);
}

static void Bluetooth_SendScaled(char type, float value)
{
    char encoded[16];
    long scaled = (long)(value * 100.0f);

    if (scaled > 99999L) {
        scaled = 99999L;
    } else if (scaled < -99999L) {
        scaled = -99999L;
    }

    snprintf(encoded, sizeof(encoded), "%+06ld", scaled);
    Bluetooth_WaitAndSend(type, encoded, 'D');
}

void Bluetooth_Init(void)
{
}

void Bluetooth_SendString(const char *text, uint16_t max_len)
{
    uint16_t index = 0U;
    char encoded[7];

    if (text == NULL) {
        return;
    }

    while ((text[index] != '\0') && (index < max_len)) {
        snprintf(encoded, sizeof(encoded), "+%05u",
            (unsigned)(uint8_t)text[index]);
        Bluetooth_WaitAndSend('S', encoded,
            (text[index + 1U] == '\0') ? 'E' : 'C');
        index++;
    }
}

void Bluetooth_SendData(float value1, float value2)
{
    Bluetooth_SendScaled('1', value1);
    Bluetooth_SendScaled('2', value2);
}
