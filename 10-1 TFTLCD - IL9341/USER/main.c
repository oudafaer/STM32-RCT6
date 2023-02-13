#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "tftlcd.h"


 int main(void)
 { 
	u8 lcd_id[12];			//存放LCD ID字符串	
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口
 	LCD_Init();
	POINT_COLOR=RED; 
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将LCD ID打印到lcd_id数组。
	LCD_Clear(BLUE);
  	while(1) 
	{		 
		POINT_COLOR=RED;	  
		LCD_ShowString(30,40,200,24,24,"STM32f103rct6");	
 		LCD_ShowString(30,70,200,16,16,lcd_id);		//显示LCD ID	      					 
		LCD_ShowString(30,90,200,12,12,"2022/4/5");	      					 
		LED0=!LED0;	 
		delay_ms(1000);	
	} 
}
