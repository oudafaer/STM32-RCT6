#include "24CXX.h"
#include "key.h"
#include "delay.h"
#include "lcd.h"
#include "myiic.h"
#include "usart.h"



//要写入到24c02的字符串数组
const u8 TEXT[]={"for freedom"};
#define SIZE sizeof(TEXT)	

int main()
{
	u8 key;
	u8 date[SIZE];
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2		
	KEY_Init();				//按键初始化		 	
	uart_init(9600);	 	//串口初始化为9600
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
			LCD_Fill(0,170,239,319,WHITE);//清除半屏 			
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
			LCD_ShowString(60,50,200,16,16,date);//显示读到的字符串
		}
	}
}
