#include "stm32f10x.h"                  // Device header
#include "delay.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	//定义结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA,ENABLE); //外设设置
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU; //设置输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//设置输出速度	
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;   //引脚设置
	GPIO_Init(GPIOC,&GPIO_InitStructure);   //初始化	
	
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;   //引脚设置
	GPIO_Init(GPIOA,&GPIO_InitStructure);   //初始化
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
