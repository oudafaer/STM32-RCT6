#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "OLED.h"
#include "delay.h"

int main()
{
	delay_init();
	LED_Init();
	OLED_Init();
	OLED_ShowString(1,1,"for freedom!");
	while(1)
	{
		LED0=0;
		LED1=1;
		delay_ms(300);	 //—” ±300ms
		LED0=1;
		LED1=0;
		delay_ms(300);	//—” ±300ms
	}
}
