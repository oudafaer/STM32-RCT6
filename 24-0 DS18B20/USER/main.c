#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "ds18b20.h" 
#include "tftlcd.h"


int main()
{
	u8 t=0;			    
	short temperature;   
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
 	LCD_Init();	
	while(DS18B20_Init())
	{
		LCD_ShowString(60,130,200,16,16,"DS18B20 wating");
		delay_ms(200);
		LCD_Fill(60,130,239,130+16,WHITE);
 		delay_ms(200);
	}
	LCD_ShowString(60,130,200,16,16,"DS18B20 OK");
	POINT_COLOR=RED;//��������Ϊ��ɫ 
 	LCD_ShowString(60,150,200,16,16,"Temp:   . C");
	while(1)
	{	    	    
 		if(t%10==0)//ÿ100ms��ȡһ��
		{									  
			temperature=DS18B20_Get_Temp();	
			if(temperature<0)
			{
				LCD_ShowChar(60+40,150,'-',16,0);			//��ʾ����
				temperature=-temperature;					//תΪ����
			}else LCD_ShowChar(60+40,150,' ',16,0);			//ȥ������
			LCD_ShowNum(60+40+8,150,temperature/10,2,16);	//��ʾ��������	    
   			LCD_ShowNum(60+40+32,150,temperature%10,1,16);	//��ʾС������ 		   
		}				   
	 	delay_ms(10);
		t++;
		if(t==20)
		{
			t=0;
			LED0=!LED0;
		}
	}
}

