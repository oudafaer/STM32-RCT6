#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "key.h"
#include "sys.h"

int main()
{
	u8 key;
	LED_Init();
	KEY_Init();
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY0_PRES)LED0=~LED0;
		if(key==KEY1_PRES)LED1=~LED1;
	}
}
