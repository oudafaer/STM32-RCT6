#include "stm32f10x.h"                  // Device header
#include "lcd.h"
#include "PS2.h"
#include "delay.h"
#include "usart.h"

int main(void)
{ 
	u16 adcx;
	u16 adcy;
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	//串口初始化为9600
	SYS_init(4);
	IO_init();
	SPI_BLK_1;
	SPI_SCK_0;
	LCD_Init();
	TFT_clear();
	Adc_Init();
	LCD_ShowString(0,0,"ADC_CH1_VAL:",RED,WHITE,16,0);	      
	LCD_ShowString(0,20,"ADC_CH1_VOL:0.000V",RED,WHITE,16,1);
	LCD_ShowString(0,40,"ADC_CH1_VAL:",RED,WHITE,16,0);	      
	LCD_ShowString(0,60,"ADC_CH1_VOL:0.000V",RED,WHITE,16,1);	
	while(1)
	{
		adcx=Get_Adc_Average(ADC_Channel_2,10);
		LCD_ShowIntNum(96,0,adcx,4,RED,WHITE,16);//显示ADC的值

		
		adcy=Get_Adc_Average(ADC_Channel_3,10);
		LCD_ShowIntNum(96,40,adcy,4,RED,WHITE,16);//显示ADC的值
		
	}
}
