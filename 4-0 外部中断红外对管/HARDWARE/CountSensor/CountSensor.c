#include "stm32f10x.h"                  // Device header
#include "EXTI.h"
#include "NVIC.h"


//定义中断响应次数
uint16_t CountSensor_count;


void CountSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  //rcc开启外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;   //定义结构体
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //上拉输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //输出速度50hz
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//引脚设置
	GPIO_Init(GPIOB, &GPIO_InitStructure);    //初始化GPIO
	
	EXTI_InitStart();                         //初始化外部中断
	NVIC_InitStart();                         //初始化NVIC 
		
}
//外部中断函数
void EXTI15_10_IRQHandler(void)
{
	if ( (EXTI_GetITStatus(EXTI_Line10)) == SET)  //判断是否是中断10通道，然后执行中断函数
	{
		CountSensor_count++;
		EXTI_ClearITPendingBit(EXTI_Line10); //清除中断标志位，跳出中断
	}
	
}
//返回计数值
uint16_t CountSensor_Get(void)
{
	return CountSensor_count;
}
