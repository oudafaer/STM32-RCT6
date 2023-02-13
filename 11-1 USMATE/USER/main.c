#include "LED.h"
#include "OLED.h"
#include "usmart.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2	 
	LED_Init();
	OLED_Init();
	delay_init();
	uart_init(9600);	 	//串口初始化为9600
	usmart_dev.init(72); 	//初始化USMART
	OLED_ShowString(1,1,"for freedom!");
	while(1)
	{
		
		LED0=!LED0;					 
		delay_ms(500);				
	}
}
