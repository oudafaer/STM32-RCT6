#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "tftlcd.h"
#include "rtc.h"

int main(void)
{
	u8 t;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	delay_init();
	uart_init(9600);	 	//串口初始化为9600	
	LCD_Init();				//初始化LCD
	POINT_COLOR=RED;//设置字体为红色 
	while(RTC_Init())
	{
		LCD_ShowString(60,130,200,16,16,"RTC ERROR!   ");	
		delay_ms(800);
		LCD_ShowString(60,130,200,16,16,"RTC Trying...");		
	}
	POINT_COLOR=RED;//设置字体为红色					 
	LCD_ShowString(0,32,200,16,16,"    -  -     ");	   
	LCD_ShowString(0,16,200,16,16,"  :  :  ");
	while(1)
	{
		if(t!=calendar.sec)
		{
			t=calendar.sec;
			LCD_ShowNum(0,32,calendar.w_year,4,16);									  
			LCD_ShowNum(40,32,calendar.w_month,2,16);									  
			LCD_ShowNum(64,32,calendar.w_date,2,16);
			LCD_ShowNum(0,16,calendar.hour,2,16);									  
			LCD_ShowNum(24,16,calendar.min,2,16);									  
			LCD_ShowNum(48,16,calendar.sec,2,16);			
			switch(calendar.week)
			{
				case 0:
					LCD_ShowString(0,0,200,16,16,"Sunday   ");
					break;
				case 1:
					LCD_ShowString(0,0,200,16,16,"Monday   ");
					break;
				case 2:
					LCD_ShowString(0,0,200,16,16,"Tuesday  ");
					break;
				case 3:
					LCD_ShowString(0,0,200,16,16,"Wednesday");
					break;
				case 4:
					LCD_ShowString(0,0,200,16,16,"Thursday ");
					break;
				case 5:
					LCD_ShowString(0,0,200,16,16,"Friday   ");
					break;
				case 6:
					LCD_ShowString(0,0,200,16,16,"Saturday ");
					break;  
			}		
		}
		delay_ms(10);
	}
}	
