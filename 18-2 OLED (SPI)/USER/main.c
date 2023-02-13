#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
#include "usart.h"

int main(void)
{	
	delay_init();	    	      //延时函数初始化	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 	
	OLED_Init();			       //初始化OLED 
	OLED_Clear();
	OLED_Vertical();
	OLED_ShowString(20,2,"oudafa");                    //测试函数	
	while(1) 
	{
		
	}	  	
}
