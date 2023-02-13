#include "wwdg.h"
#include "led.h"
#include "NVIC.h"


//����WWDG������������ֵ,Ĭ��Ϊ���.
u8 WWDG_CNT=0x7f;

void WWDG_Init(u8 tr,u8 wr,u32 fprer)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);
	
	WWDG_SetPrescaler(fprer);    //����Ԥ��Ƶֵ
	
	WWDG_SetWindowValue(wr);   //���ô���ֵ
	
	WWDG_Enable(tr);       //�����ü�������ʼֵ��ʹ�ܿ��Ź�
	
	WWDG_ClearFlag();
	
	NVIC_InitStart(2,3);//��ʼ�����ڿ��Ź� NVIC
	
	WWDG_EnableIT();    //�������ڿ��Ź��ж�
}

//������WWDG��������ֵ
void WWDG_Set_Counter(u8 cnt)
{
    WWDG_Enable(cnt);	 
}

void WWDG_IRQHandler(void)
{
	
	WWDG_SetCounter(0x7F);	  //�������˾��,���ڿ��Ź���������λ
	
	WWDG_ClearFlag();	  //�����ǰ�����жϱ�־λ
	
	LED1=!LED1;
	
	
}
