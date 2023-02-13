#include "stm32f10x.h"                  // Device header

void EXTI_InitStart(void)
{
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);	//中断线0连接GPIOA.0
	
	EXTI_InitTypeDef EXTI_InitStructure;  //定义外部中断参数结构体
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;   //配置中短线
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;   //设置为中断响应
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;  //设置为下降沿触发
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;   //设置中断线的新状态，ENABLE=开启
	EXTI_Init(&EXTI_InitStructure);   //初始化外部中断
}
