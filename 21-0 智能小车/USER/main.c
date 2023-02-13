#include "motor.h"
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
#include <string.h>


int main(void)
{
	int key;
	u8 lcd_id[12];			//存放LCD ID字符串	
	delay_init();	    	 //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2	 
	MOTOR_GPIO_Init();
	uart_init(9600);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口
 	LCD_Init();
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将LCD ID打印到lcd_id数组。	
	LCD_ShowString(30,110,200,16,16,lcd_id);		//显示LCD ID	      					 
	LCD_ShowString(30,130,200,16,16,"2022/4/27");	  
	LED0=1;
	while(1)
	{
		MOTOR_Display(KEY_Scan());
		key=KEY_Scan();
		LCD_ShowNum(30,150,key,1,16);
	}	
}
