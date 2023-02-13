#ifndef __CountSensor_H
#define __CountSensor_H

void CountSensor_Init(void);
void EXTI15_10_IRQHandler(void);
uint16_t CountSensor_Get(void);

#endif
