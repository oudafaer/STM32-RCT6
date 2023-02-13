#include "stm32f10x.h"                  // Device header
#include "lcd.h"
#include "bmp.h"

int main(void)
{ 

	SYS_init(4);
	IO_init();
	SPI_BLK_1;
	SPI_SCK_0;
	LCD_Init();
	TFT_clear();
	
	LCD_ShowPicture(0,0,240,240,gImage_1);
	while(1)
	{
		

	}
}
