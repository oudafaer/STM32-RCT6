#ifndef __PWM_H
#define __PWM_H
#include "sys.h"

void TIM1_PWM_Init(u16 arr,u16 psc);
void PWM_SetCompare4(u16 Compare4);
void Servo_SetAngle(float Angle);
#endif

