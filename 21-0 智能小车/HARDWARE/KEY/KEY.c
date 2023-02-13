#include "KEY.h"
#include "delay.h"
#include "stm32f10x.h"                  // Device header
#include "usart.h"
#include <string.h>

u8 KEY_Scan(void)
{	
	int num;
	if(USART_RX_STA==1)//接收到一帧数据
	{
		//切记清空标志和大小还有空间，准备下次接收
		USART_RX_STA=0;	
		USART_RX_STA=0;
		memset(USART_RX_BUF,0,USART_REC_LEN);//USART_REC_LEN需要清空，再装新数据，否则新旧都在一起
		if(USART_ReceiveData(USART1) == '1')
		{
			num=1;
		}
		else if(USART_ReceiveData(USART1) == '2')
		{
			num=2;
		}
		else if(USART_ReceiveData(USART1) == '3')
		{
			num=3;
		}
		else if(USART_ReceiveData(USART1) == '4')
		{
			num=4;
		}
		else
		{
			num=0;
		}
	}
	return num;
}

