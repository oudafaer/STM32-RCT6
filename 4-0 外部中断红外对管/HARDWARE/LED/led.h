#ifndef __LED_H
#define __LED_H
#include "SYS.h"

#define LED0 PAout(8)	// PA8
#define LED1 PDout(2)	// PD2	

void LED_Init(void);
#define LED0_no GPIO_SetBits(GPIOA,GPIO_Pin_8)
#define LED0_off GPIO_ResetBits(GPIOA,GPIO_Pin_8)

#define LED1_no GPIO_SetBits(GPIOD,GPIO_Pin_2)
#define LED1_off GPIO_ResetBits(GPIOD,GPIO_Pin_2)

void LED0_Turn(void);
void LED1_Turn(void);


#endif
