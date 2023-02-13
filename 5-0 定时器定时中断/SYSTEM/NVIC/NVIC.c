#include "stm32f10x.h"                  // Device header

void NVIC_InitStart(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�����ж����ȼ�����
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn;  //ָ���ж�ͨ����������ر�
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2; //�����ⲿ��ռ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;  //�����ⲿ�ж���Ӧ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;  //ָ���ж�ͨ��ʹ�ܻ���ʧ��
	
	NVIC_Init(&NVIC_InitStruct);  //�����ж�
}
