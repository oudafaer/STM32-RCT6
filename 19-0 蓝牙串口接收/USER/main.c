#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "tftlcd.h"
#include "key.h"
#include <string.h>


int main()
{
	u8 key=0;
	u8 num=0;
	u8 lcd_id[12];			//存放LCD ID字符串	
	delay_init();	    	 //延时函数初始化	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2	 
	uart_init(9600);	 	//串口初始化为115200
	LED_Init();		  		//初始化与LED连接的硬件接口
 	LCD_Init();
	KEY_Init();
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将LCD ID打印到lcd_id数组。	
	LCD_ShowString(30,110,200,16,16,lcd_id);		//显示LCD ID	      					 
	LCD_ShowString(30,130,200,16,16,"2022/4/27");
	  
	LED0=1;
	while(1)
	{
		key=KEY_Scan(0);
		if(key)
		{
			switch(key)
			{
				case KEY0_PRES :   num++; printf("%s\r\n","KEY0"); break;
				case KEY1_PRES :   num--;  printf("%s\r\n","KEY1"); break;
				case WKUP_PRES :   num=0; printf("%s\r\n","WKUP");  break;
			}
		}
		if(USART_RX_STA==1)//接收到一帧数据
		{
			LCD_ShowString(30,150,200,16,16,"Receive Data:");		
			LCD_Fill(30,170,239,170+16,WHITE); 
			LED0=!LED0;
			LCD_ShowString(30,170,200,16,16,USART_RX_BUF);	
			//切记清空标志和大小还有空间，准备下次接收
			USART_RX_STA=0;	
			USART_RX_STA=0;
			memset(USART_RX_BUF,0,USART_REC_LEN);//USART_REC_LEN需要清空，再装新数据，否则新旧都在一起
			
			if(USART_ReceiveData(USART1) == 'A')
			{
				printf("%s\r\n","RES");
			}
		}
	}
}
