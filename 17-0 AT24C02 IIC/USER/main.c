#include "24CXX.h"
#include "key.h"
#include "delay.h"
#include "lcd.h"
#include "myiic.h"
#include "usart.h"



//Ҫд�뵽24c02���ַ�������
const u8 TEXT[]={"for freedom"};
#define SIZE sizeof(TEXT)	

int main()
{
	u8 key;
	u8 date[SIZE];
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2		
	KEY_Init();				//������ʼ��		 	
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	LCD_Init();	
	AT24CXX_Init();
	POINT_COLOR=RED;	
	while(AT24CXX_Check())
	{
		LCD_ShowString(60,10,200,16,16,"24C02 die!   ");
		delay_ms(500);
		LCD_ShowString(60,10,200,16,16,"Please Check!");
		delay_ms(500);		
	}
	POINT_COLOR=BLUE;
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY0_PRES)
		{
			LCD_Fill(0,170,239,319,WHITE);//������� 			
			LCD_ShowString(60,30,200,16,16,"Start Write 24C02!");
			delay_ms(10);
			AT24CXX_Write(0,(u8*)TEXT,SIZE);
			LCD_ShowString(60,30,200,16,16,"24C02 Write ok!   ");
		}
		if(key==KEY1_PRES)
		{
			LCD_ShowString(60,30,200,16,16,"Start Read 24C02!");
			AT24CXX_Read(0,date,SIZE);
			LCD_ShowString(60,30,200,16,16,"Read Date Is!    ");
			LCD_ShowString(60,50,200,16,16,date);//��ʾ�������ַ���
		}
	}
}
