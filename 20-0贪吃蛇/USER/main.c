#include "stm32f10x.h"
#include "oled.h"
#include "delay.h"
#include "snake.h"
#include "led.h"
#include "timer.h"
#include "bmp.h"
#include "key.h"
#include "usart.h"

int  main()
{	
	
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();
	OLED_Init();
	TIM3_Int_Init(1999,7199);//500ms
	GUI_Init();//�����ʼ��
	OLED_ShowPicture(0,0,128,8,BMP2);//��ͷ����
	delay_ms(1863);
	while(1)
	{
	 Get_Command();
	 Show_Score();
	 GUI_Refresh(map);//ˢ�µ�ͼ
	 if(GameOver())
	 {
	   OLED_Clear();
	   OLED_ShowPicture(0,0,128,8,BMP);
	 }
	}
}






