#include "stm32f10x.h"                  // Device header


void NVIC_InitStart(uint16_t pree,uint16_t Sub)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel=WWDG_IRQn;  //指定中断通道来开启或关闭
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=pree; //设置外部抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=Sub;  //设置外部中断响应优先级
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;  //指定中断通道使能还是失能
	
	NVIC_Init(&NVIC_InitStruct);  //启动中断	
	
}
