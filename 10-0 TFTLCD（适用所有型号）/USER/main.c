#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "tftlcd.h"


 int main(void)
 { 
	u8 lcd_id[12];			//���LCD ID�ַ���	
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
 	LCD_Init();
	POINT_COLOR=RED; 
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//��LCD ID��ӡ��lcd_id���顣
	LCD_Clear(BLUE);
  	while(1) 
	{		 
		POINT_COLOR=RED;	  
		LCD_ShowString(30,40,200,24,24,"STM32f103rct6");	
 		LCD_ShowString(30,70,200,16,16,lcd_id);		//��ʾLCD ID	      					 
		LCD_ShowString(30,90,200,12,12,"2022/4/5");	      					 
		LED0=!LED0;	 
		delay_ms(1000);	
	} 
}
