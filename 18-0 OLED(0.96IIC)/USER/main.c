#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "bmp.h"

int main()
{
	OLED_Init();
	OLED_Clear();
	OLED_ShowChar(1,1,'A',16);
	while(1)
	{
	}
}
