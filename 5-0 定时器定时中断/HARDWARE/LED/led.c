#include "stm32f10x.h"                  // Device header


//LED驱动代码	      
//初始化PA8和PD2为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	//定义结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD,ENABLE); //外设设置
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; //设置输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//设置输出速度
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;   //引脚设置
	GPIO_Init(GPIOA,&GPIO_InitStructure);   //初始化
	
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;   //引脚设置
	GPIO_Init(GPIOD,&GPIO_InitStructure);   //初始化	
	
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
