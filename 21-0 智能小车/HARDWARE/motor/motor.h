#ifndef __MOTOR_H
#define	__MOTOR_H

#include "stm32f10x.h"                  // Device header


#define MOTO_Pin12  GPIO_Pin_12
#define MOTO_Pin13  GPIO_Pin_13
#define MOTO_Pin14  GPIO_Pin_14
#define MOTO_Pin15  GPIO_Pin_15

#define IN1_up GPIO_SetBits(GPIOB, GPIO_Pin_12)
#define IN1_down  GPIO_ResetBits(GPIOB,GPIO_Pin_12)

#define IN2_up GPIO_SetBits(GPIOB, GPIO_Pin_13)
#define IN2_down  GPIO_ResetBits(GPIOB,GPIO_Pin_13)

#define IN3_up GPIO_SetBits(GPIOB, GPIO_Pin_14)
#define IN3_down  GPIO_ResetBits(GPIOB,GPIO_Pin_14)

#define IN4_up GPIO_SetBits(GPIOB, GPIO_Pin_15)
#define IN4_down  GPIO_ResetBits(GPIOB,GPIO_Pin_15)



void CarGo(void);
void CarStop(void);
void CarBack(void);
void CarRight(void);
void CarLeft(void);
void MOTOR_GPIO_Init(void);
void MOTOR_Display(u8 key);

#endif
