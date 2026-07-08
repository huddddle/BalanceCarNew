#ifndef __PID_H_
#define __PID_H_

#include "wit.h"
#include "global.h"

typedef struct {
    PID gain;
    float integral;
    float last_error;
    float integral_limit;
    float output_limit;
    float output_deadband;
} LocaPID_t;

extern PID TurnPID;

int Speed(PID*Example, int True_Speed, int Target_Speed);
float Loca_PID(LocaPID_t *controller, float error);
void Loca_PID_Reset(LocaPID_t *controller);

#endif
