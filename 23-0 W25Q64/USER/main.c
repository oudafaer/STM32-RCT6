#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
#include "spi.h"
#include "flash.h"


  	
//要写入到W25Q64的字符串数组
const u8 TEXT_Buffer[]={"for freedom"};
#define SIZE sizeof(TEXT_Buffer)
	
int main()
{
	u8 key;
	u8 datatemp[SIZE];
	u32 FLASH_SIZE;
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口
 	LCD_Init();
	KEY_Init();				//按键初始化		 	
	SPI_Flash_Init();  		//SPI FLASH 初始化
	FLASH_SIZE=8*1024*1024;	//FLASH 大小为8M字节
	POINT_COLOR=BLUE;		//设置字体为蓝色	
	while(1)
	{
		key=KEY_Scan(0);
		if(key==WKUP_PRES)	//WK_UP 按下,写入W25Q64	
		{
			LCD_ShowString(60,170,200,16,16,"Start Write W25Q64....");
			SPI_Flash_Write((u8*)TEXT_Buffer,FLASH_SIZE-100,SIZE);
			LCD_ShowString(60,170,200,16,16,"W25Q64 Write Finished!");	//提示传送完成
		}
		if(key==KEY0_PRES)	//KEY0 按下,读取字符串并显示
		{
			LCD_ShowString(60,170,200,16,16,"Start Read W25Q64.... ");
			SPI_Flash_Read(datatemp,FLASH_SIZE-100,SIZE);
			LCD_ShowString(60,170,200,16,16,"The Data Readed Is:  ");	//提示传送完成
			LCD_ShowString(60,190,200,16,16,datatemp);
		}
	}
}

