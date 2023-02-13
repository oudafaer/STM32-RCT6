#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "ds18b20.h" 
#include "tftlcd.h"


int main()
{
	u8 t=0;			    
	short temperature;   
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口
 	LCD_Init();	
	while(DS18B20_Init())
	{
		LCD_ShowString(60,130,200,16,16,"DS18B20 wating");
		delay_ms(200);
		LCD_Fill(60,130,239,130+16,WHITE);
 		delay_ms(200);
	}
	LCD_ShowString(60,130,200,16,16,"DS18B20 OK");
	POINT_COLOR=RED;//设置字体为蓝色 
 	LCD_ShowString(60,150,200,16,16,"Temp:   . C");
	while(1)
	{	    	    
 		if(t%10==0)//每100ms读取一次
		{									  
			temperature=DS18B20_Get_Temp();	
			if(temperature<0)
			{
				LCD_ShowChar(60+40,150,'-',16,0);			//显示负号
				temperature=-temperature;					//转为正数
			}else LCD_ShowChar(60+40,150,' ',16,0);			//去掉负号
			LCD_ShowNum(60+40+8,150,temperature/10,2,16);	//显示正数部分	    
   			LCD_ShowNum(60+40+32,150,temperature%10,1,16);	//显示小数部分 		   
		}				   
	 	delay_ms(10);
		t++;
		if(t==20)
		{
			t=0;
			LED0=!LED0;
		}
	}
}

