#include "KEY.h"
#include "delay.h"
#include "stm32f10x.h"                  // Device header
#include "usart.h"
#include <string.h>
#include "ps2.h"

u8 KEY_Scan(void)
{
	u8 num;
	u16 adcx;
	u16 adcy;
	adcx=Get_Adc_Average(ADC_Channel_2,10);	
	adcy=Get_Adc_Average(ADC_Channel_3,10);
	if(adcx<2000 || adcx>2200 || adcy<2000 || adcy>2200 )
	{
		if( adcy<1000 )
		{
			num=1;
		}
		else if(adcy>3000 )
		{
			num=2;
		}
		else if(adcx>3000 )
		{
			num=3;
		}
		else if(adcx<1000 )
		{
			num=4;
		}
	}
	return num;
}

