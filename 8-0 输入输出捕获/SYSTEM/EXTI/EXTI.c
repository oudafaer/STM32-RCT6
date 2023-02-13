#include "stm32f10x.h"                  // Device header

void EXTI_InitStart(void)
{
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource10);  //����PB10Ϊ�ⲿ�ж�
	
	EXTI_InitTypeDef EXTI_InitStructure;  //�����ⲿ�жϲ����ṹ��
	EXTI_InitStructure.EXTI_Line=EXTI_Line10;   //�����ж���
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;   //����Ϊ�ж���Ӧ
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising_Falling;  //����Ϊ�½��ش���
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;   //�����ж��ߵ���״̬��ENABLE=����
	EXTI_Init(&EXTI_InitStructure);   //��ʼ���ⲿ�ж�
}
