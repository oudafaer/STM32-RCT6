#include "stm32f10x.h"                  // Device header
#include "EXTI.h"
#include "NVIC.h"


//�����ж���Ӧ����
uint16_t CountSensor_count;


void CountSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  //rcc��������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;   //����ṹ��
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //����ٶ�50hz
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);    //��ʼ��GPIO
	
	EXTI_InitStart();                         //��ʼ���ⲿ�ж�
	NVIC_InitStart();                         //��ʼ��NVIC 
		
}
//�ⲿ�жϺ���
void EXTI15_10_IRQHandler(void)
{
	if ( (EXTI_GetITStatus(EXTI_Line10)) == SET)  //�ж��Ƿ����ж�10ͨ����Ȼ��ִ���жϺ���
	{
		CountSensor_count++;
		EXTI_ClearITPendingBit(EXTI_Line10); //����жϱ�־λ�������ж�
	}
	
}
//���ؼ���ֵ
uint16_t CountSensor_Get(void)
{
	return CountSensor_count;
}
