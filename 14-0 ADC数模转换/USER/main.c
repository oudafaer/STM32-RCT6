#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "adc.h"

int main(void)
{
	u16 adcx;
	float temp;
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	LCD_Init();
 	Adc_Init();		  		//ADC��ʼ��	    

	//��ʾ��ʾ��Ϣ
	POINT_COLOR=RED;//��������Ϊ��ɫ
	LCD_ShowString(0,0,200,16,16,"ADC_CH1_VAL:");	      
	LCD_ShowString(0,20,200,16,16,"ADC_CH1_VOL:0.000V");	    
	while(1)
	{
		adcx=Get_Adc_Average(ADC_Channel_1,10);
		LCD_ShowxNum(96,0,adcx,4,16,0);//��ʾADC��ֵ
		temp=(float)adcx*(3.3/4096);
		adcx=temp;
		LCD_ShowxNum(96,20,adcx,1,16,0);//��ʾ��ѹֵ
		temp-=adcx;
		temp*=1000;
		LCD_ShowxNum(112,20,temp,3,16,0X80);
		delay_ms(250);	
	}
	
}

