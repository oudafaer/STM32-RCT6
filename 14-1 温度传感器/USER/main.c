#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "tftlcd.h"
#include "tsensor.h"


int main()
{
	u16 adcx;
	float temp;
	float wemdu;	 
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	LCD_Init();
 	T_Adc_Init();		  		//ADC��ʼ��
	//��ʾ��ʾ��Ϣ											      
	POINT_COLOR=RED;//��������Ϊ��ɫ
	LCD_ShowString(0,0,200,16,16,"TEMP_VAL:");	      
	LCD_ShowString(0,20,200,16,16,"TEMP_VOL:0.000V");	      
	LCD_ShowString(0,40,200,16,16,"TEMPERATE:00.00C");	
	while(1)
	{
		adcx=T_Get_Adc_Average(ADC_CH_TEMP,10);
		LCD_ShowxNum(72,0,adcx,4,16,0);//��ʾADC��ֵ
		temp=(float)adcx*(3.3/4096);
		wemdu=temp;//�����¶ȴ������ĵ�ѹֵ
		adcx=temp;
		LCD_ShowxNum(72,20,adcx,1,16,0);     		//��ʾ��ѹֵ��������
		temp-=(u8)temp;				    			//������������		  
		LCD_ShowxNum(88,20,temp*1000,3,16,0X80);	//��ʾ��ѹС������
 		wemdu=(1.43-wemdu)/0.0043+25;		//�������ǰ�¶�ֵ	 
		LCD_ShowxNum(80,40,(u8)wemdu,2,16,0); //��ʾ�¶���������
		wemdu-=(u8)wemdu;	  
		LCD_ShowxNum(104,40,wemdu*100,2,16,0X80);//��ʾ�¶�С������
		delay_ms(250);
	}
}
