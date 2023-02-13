#include "stm32f10x.h"                  // Device header
#include "delay.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	//����ṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA,ENABLE); //��������
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU; //�������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//��������ٶ�	
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;   //��������
	GPIO_Init(GPIOC,&GPIO_InitStructure);   //��ʼ��	
	
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;   //��������
	GPIO_Init(GPIOA,&GPIO_InitStructure);   //��ʼ��
}

uint8_t KEY_GetNum(void)
{
	uint8_t KeyNum=0;
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5) == 0)
	{
		delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5) == 0);
		delay_ms(20);
		KeyNum=1;
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15) == 0)
	{
		delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15) == 0);
		delay_ms(20);
		KeyNum=2;
	}	
	return KeyNum;
}
