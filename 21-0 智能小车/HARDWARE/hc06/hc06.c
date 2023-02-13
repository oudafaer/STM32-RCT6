#include "usart.h"
#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "motor.h"
#include <string.h>
#inlcude ""

void HC06_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	
}
void HC06Display(void)
{
	u8 num;
	if(USART_RX_STA==1)//���յ�һ֡����
	{
		LCD_ShowString(30,170,200,16,16,USART_RX_BUF);	
		//�м���ձ�־�ʹ�С���пռ䣬׼���´ν���
		USART_RX_STA=0;	
		USART_RX_STA=0;
		memset(USART_RX_BUF,0,USART_REC_LEN);//USART_REC_LEN��Ҫ��գ���װ�����ݣ������¾ɶ���һ��
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
