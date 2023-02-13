#include "stm32f10x.h"                  // Device header


void NVIC_InitStart(uint16_t pree,uint16_t Sub)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel=WWDG_IRQn;  //ָ���ж�ͨ����������ر�
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=pree; //�����ⲿ��ռ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=Sub;  //�����ⲿ�ж���Ӧ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;  //ָ���ж�ͨ��ʹ�ܻ���ʧ��
	
	NVIC_Init(&NVIC_InitStruct);  //�����ж�	
	
}
