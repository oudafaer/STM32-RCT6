#include "stm32f10x.h"                  // Device header

void EXTI_InitStart(void)
{
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);	//�ж���0����GPIOA.0
	
	EXTI_InitTypeDef EXTI_InitStructure;  //�����ⲿ�жϲ����ṹ��
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;   //�����ж���
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;   //����Ϊ�ж���Ӧ
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;  //����Ϊ�½��ش���
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;   //�����ж��ߵ���״̬��ENABLE=����
	EXTI_Init(&EXTI_InitStructure);   //��ʼ���ⲿ�ж�
}
