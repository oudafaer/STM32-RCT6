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
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	//串口初始化为9600
 	LCD_Init();
 	T_Adc_Init();		  		//ADC初始化
	//显示提示信息											      
	POINT_COLOR=RED;//设置字体为红色
	LCD_ShowString(0,0,200,16,16,"TEMP_VAL:");	      
	LCD_ShowString(0,20,200,16,16,"TEMP_VOL:0.000V");	      
	LCD_ShowString(0,40,200,16,16,"TEMPERATE:00.00C");	
	while(1)
	{
		adcx=T_Get_Adc_Average(ADC_CH_TEMP,10);
		LCD_ShowxNum(72,0,adcx,4,16,0);//显示ADC的值
		temp=(float)adcx*(3.3/4096);
		wemdu=temp;//保存温度传感器的电压值
		adcx=temp;
		LCD_ShowxNum(72,20,adcx,1,16,0);     		//显示电压值整数部分
		temp-=(u8)temp;				    			//减掉整数部分		  
		LCD_ShowxNum(88,20,temp*1000,3,16,0X80);	//显示电压小数部分
 		wemdu=(1.43-wemdu)/0.0043+25;		//计算出当前温度值	 
		LCD_ShowxNum(80,40,(u8)wemdu,2,16,0); //显示温度整数部分
		wemdu-=(u8)wemdu;	  
		LCD_ShowxNum(104,40,wemdu*100,2,16,0X80);//显示温度小数部分
		delay_ms(250);
	}
}
