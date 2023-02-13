#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "key.h"
#include "dma.h"


const u8 text[]={"DMAʵ��"};
#define text_len sizeof(text)-1
u8 sendtext[(text_len+2)*52];


int main()
{
	u16 i;
	u8 t=0;
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	KEY_Init();				//������ʼ��	
	MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)sendtext,(text_len+2)*52);
	uart_init(9800);
	for(i=0;i<(text_len+2)*52;i++)
	{
		if(t>=text_len)
		{
			sendtext[i++]=0x0d;
			sendtext[i]=0x0a;
			t=0;
		}
		else 
		{
			sendtext[i]=text[t++];
		}
	}
	i=0;
	while(1)
	{
		t=KEY_Scan(0);
		if(t==KEY0_PRES)
		{
			USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
			MYDMA_Enable(DMA1_Channel4);//��ʼһ��DMA���䣡	 
			
		}
	}
}
