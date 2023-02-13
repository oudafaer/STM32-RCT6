#include "stm32f10x.h"                  // Device header


//LED��������	      
//��ʼ��PA8��PD2Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	//����ṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD,ENABLE); //��������
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; //�������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//��������ٶ�
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;   //��������
	GPIO_Init(GPIOA,&GPIO_InitStructure);   //��ʼ��
	
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;   //��������
	GPIO_Init(GPIOD,&GPIO_InitStructure);   //��ʼ��	
	
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
	GPIO_SetBits(GPIOD,GPIO_Pin_2);
		
}
 
void LED0_Turn(void)
{
	if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2) == 0)
	{
		GPIO_SetBits(GPIOD,GPIO_Pin_2);
	}
	else
	{
		GPIO_ResetBits(GPIOD,GPIO_Pin_2);
	}
}
void LED1_Turn(void)
{
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8) == 0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_8);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	}
}
