#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "bmp.h"
#include "delay.h"

int main()
{
	OLED_Init();
	OLED_Clear();
	while(1)
	{
		OLED_Refresh();
		OLED_ShowChar(0,0,'A',16);
	}
}
