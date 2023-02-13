#include "usart.h"
#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "motor.h"
#include <string.h>
#inlcude ""

void HC06_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	
}
void HC06Display(void)
{
	u8 num;
	if(USART_RX_STA==1)//接收到一帧数据
	{
		LCD_ShowString(30,170,200,16,16,USART_RX_BUF);	
		//切记清空标志和大小还有空间，准备下次接收
		USART_RX_STA=0;	
		USART_RX_STA=0;
		memset(USART_RX_BUF,0,USART_REC_LEN);//USART_REC_LEN需要清空，再装新数据，否则新旧都在一起
		num=USART_ReceiveData(USART1);
		
	}
	if(num==0)
	{
		CarStop();
	}
	if(num==1)
	{
		CarGo();
	}
	if(num==2)
	{
		CarBack();
	}
	if(num==3)
	{
		CarRight();
	}	
	if(num==4)
	{
		CarLeft();
	}

}
