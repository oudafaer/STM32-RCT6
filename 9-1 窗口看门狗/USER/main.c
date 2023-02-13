#include "led.h"
#include "delay.h"
#include "sys.h"
#include "wwdg.h"


 int main(void)
 {
 
	delay_init();	    
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
 	LED_Init(); 
	LED0=1;
	delay_ms(300);	  
	WWDG_Init(0X7F,0X5F,WWDG_Prescaler_8);   
 	while(1)
	{
		LED0=0;			  	   
	}	 
 }


