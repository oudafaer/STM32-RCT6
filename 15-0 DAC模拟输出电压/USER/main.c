#include "sys.h"
#include "delay.h"
#include "key.h"
#include "dac.h"
#include "adc.h"
#include "oled.h"

int main()
{
    u16 adcx;
	float temp;
 	u8 t=0;	 
	u16 dianya=0;
	u8 key;
	KEY_Init();				//按键初始化		 	
 	Adc_Init();		  		//ADC初始化
	Dac1_Init();		 	//DAC通道1初始化
	delay_init();
	OLED_Init();
	OLED_Clear();
	DAC_SetChannel1Data(DAC_Align_12b_R, 0);	
	while(1)
	{
		t++;
		OLED_ShowString(0,0,"DAC:",16);
		OLED_ShowString(0,2,"ADC:",16);
		key=KEY_Scan(0);
		if(key==WKUP_PRES)
		{
			if(dianya<4000)dianya+=200;
			DAC_SetChannel1Data(DAC_Align_12b_R, dianya);
		}
		else if(key==KEY1_PRES)
		{
			if(dianya>200)dianya-=200;
			else dianya=0;
			DAC_SetChannel1Data(DAC_Align_12b_R, dianya);
		}
		if(t==10||key==KEY0_PRES||key==WKUP_PRES) 	//WKUP/KEY1按下了,或者定时时间到了
		{
 			adcx=DAC_GetDataOutputValue(DAC_Channel_1);
			temp=(float)adcx*(3.3/4096);			//得到DAC电压值
			adcx=temp;
			OLED_ShowNum(32,0,temp,1,16);
			OLED_ShowChar(40,0,'.',16);
 			temp-=adcx;
			temp*=1000;
			OLED_ShowNum(50,0,temp,3,16);
			
			
 			adcx=Get_Adc_Average(ADC_Channel_1,10);		//得到ADC转换值	  
			temp=(float)adcx*(3.3/4096);			//得到ADC电压值
			adcx=temp;
			OLED_ShowNum(32,2,temp,1,16);
			OLED_ShowChar(40,2,'.',16);
 			temp-=adcx;
			temp*=1000;
			OLED_ShowNum(50,2,temp,3,16);
			t=0;
			delay_ms(10);			
		}
		delay_ms(10);
	}
}
