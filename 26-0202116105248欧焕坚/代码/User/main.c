#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "OLED.h"
#include "pwm.h"
#include "adc.h"
#include "usart.h"
#include "sys.h"
#include <string.h>
#include "bmp.h"


int main(void)
{
	u8 mode=0;     //模式选择
	u8 res;	  	//模式三控制选择
	u32 shudu;     //舵机控制速度参数
	char RX_BUF[200]; //接收缓存区
	u16 t;            //数据长度
	u16 adcx;         //ADC接收值
	float temp;       //电压转化中间变量
	delay_init();      //启动延时函数
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级  	
	PWM_Init();        //启动PWM，ARR=2000 - 1，PSC=720 - 1，分频后为50HZ
	OLED_Init();       //oled启动
	Adc_Init();         //ADC启动
	uart_init(9600);	 	//串口初始化为9600
	OLED_DrawBMP(0,0,127,8,BMP1);   //加载开始界面
	while (1)
	{
		if(USART_RX_STA&0x8000)  //判断串口是否完成接收
		{
			OLED_Clear();         //清屏
			t=USART_RX_STA&0x3FFF;   //得到接收数据长度
			for(u8 i=0;i<t;i++)     
			{
				RX_BUF[i]=USART_RX_BUF[i];   //将数据缓存到RX_BUF
				while((USART1->SR&0X40)==0); 
			}
			printf("\r\n 接收成功 \r\n");     //打印输出接收提示
			USART_RX_STA=0;                  //接收标志位手动清0
			if(!(strcmp(RX_BUF,"模式一")))   //判断接收字符串
			{
				mode=1;                     //对应模式选择
				res=0;                      //对应控制选择
				memset(RX_BUF,0,strlen(RX_BUF)); //接收缓存区清零
			}
			else if(!(strcmp(RX_BUF,"模式二"))) //判断接收字符串
			{
				mode=2;                          //对应模式选择
				res=0;                          //对应控制选择
				memset(RX_BUF,0,strlen(RX_BUF)); //接收缓存区清零
			}
			else if(!(strcmp(RX_BUF,"模式三"))) //判断接收字符串
			{
				mode=3;                         //对应模式选择
				res=0;                          //对应控制选择
				memset(RX_BUF,0,strlen(RX_BUF)); //接收缓存区清零
			}
			else if(!(strcmp(RX_BUF,"模式四"))) //判断接收字符串
			{
				mode=4;                         //对应模式选择
				res=0;                          //对应控制选择
				memset(RX_BUF,0,strlen(RX_BUF)); //接收缓存区清零
			}
			else if(!(strcmp(RX_BUF,"亮度1"))) //判断接收字符串
			{
				res=1;                          //对应控制选择
				memset(RX_BUF,0,strlen(RX_BUF)); //接收缓存区清零
			}
			else if(!(strcmp(RX_BUF,"亮度2"))) //判断接收字符串
			{
				res=2;                           //对应控制选择
				memset(RX_BUF,0,strlen(RX_BUF)); //接收缓存区清零
			}
			else if(!(strcmp(RX_BUF,"亮度3"))) //判断接收字符串
			{
				res=3;                            //对应控制选择
				memset(RX_BUF,0,strlen(RX_BUF)); //接收缓存区清零
			}
			else if(!(strcmp(RX_BUF,"亮度4"))) //判断接收字符串
			{
				res=4;                           //对应控制选择
				memset(RX_BUF,0,strlen(RX_BUF)); //接收缓存区清零
			}
			else if(!(strcmp(RX_BUF,"角度A"))) //判断接收字符串
			{
				res=5;                          //对应控制选择
				memset(RX_BUF,0,strlen(RX_BUF)); //接收缓存区清零
			}
			else if(!(strcmp(RX_BUF,"角度B"))) //判断接收字符串
			{
				res=6;                        //对应控制选择
				memset(RX_BUF,0,strlen(RX_BUF)); //接收缓存区清零
			}
			else if(!(strcmp(RX_BUF,"角度C"))) //判断接收字符串
			{
				res=7;                         //对应控制选择
				memset(RX_BUF,0,strlen(RX_BUF)); //接收缓存区清零
			}
			else if(!(strcmp(RX_BUF,"发送数据"))) //判断接收字符串
			{
				res=8;                            //对应控制选择
				memset(RX_BUF,0,strlen(RX_BUF)); //接收缓存区清零
			}
			else  //判断接收字符串
			{
				OLED_DrawBMP(0,0,127,8,BMP4);
				memset(RX_BUF,0,strlen(RX_BUF)); //接收缓存区清零
			}
			
		}
		if(mode==1) //模式一：红灯，蓝灯进行呼吸灯
		{
			for (uint16_t i = 0; i <= 1000; i ++)
			{
				OLED_ShowCHinese(0,0,8);
				OLED_ShowCHinese(18,0,9);
				OLED_ShowString(32,0,":");
				OLED_ShowNum(54,0,i/10,3,16);
				OLED_ShowString(78,0,"%");
				PWM_SetCompare3(i*20);
				PWM_SetCompare4(i*14);
			}
			for (uint16_t i = 0; i <= 1000; i ++)
			{
				OLED_ShowCHinese(0,0,8);
				OLED_ShowCHinese(18,0,9);
				OLED_ShowString(32,0,":");
				OLED_ShowNum(54,0,(1000-i)/10,3,16);
				OLED_ShowString(78,0,"%");
				PWM_SetCompare3((1000-i)*20);
				PWM_SetCompare4((1000-i)*14);	
			}			
		}
		else if(mode==2)//模式二：舵机在45度到135度进行往复运动
		{
			shudu=Get_Adc_Average(ADC_Channel_0,10);
			for (uint16_t i = 0; i <= 50; i ++)
			{
				OLED_ShowCHinese(0,0,4);
				OLED_ShowCHinese(18,0,5);
				OLED_ShowCHinese(36,0,6);
				OLED_ShowCHinese(54,0,7);
				OLED_ShowNum(70,0,(1000+(i*20))*0.09-45,3,16);
				PWM_SetCompare2(1000+(i*20));
				delay_us(shudu*3);
			}
			for (uint16_t i = 0; i <= 50; i ++)
			{
				OLED_ShowCHinese(0,0,4);
				OLED_ShowCHinese(18,0,5);
				OLED_ShowCHinese(36,0,6);
				OLED_ShowCHinese(54,0,7);
				OLED_ShowNum(70,0,(2000-(i*20))*0.09-45,3,16);
				PWM_SetCompare2(2000-(i*20));
				delay_us(shudu*3);
			}			
		}
		else if(mode==4)       //模式四：对0~5V电压进行检测，这里由于单片机端口只能检测到3.3V，所以采用了电阻分压
		{
			//ADC检测电压
			OLED_ShowString(0,0,"ADC:");
			OLED_ShowCHinese(0,2,10);
			OLED_ShowCHinese(18,2,11);
			OLED_ShowCHinese(36,2,12);			
			adcx=Get_Adc_Average(ADC_Channel_0,25);
			OLED_ShowNum(32,0,adcx,4,16);//显示ADC的值
			temp=(float)adcx*(5.0/4095);
			adcx=temp;
			OLED_ShowNum(54,2,adcx,1,16);//显示电压值
			temp-=adcx;
			temp*=1000;
			OLED_ShowChar(62,2,'.');
			OLED_ShowNum(70,2,temp,2,16);
			delay_ms(250);				
			
		}
		else if(mode==3 && res==0)//模式三开始界面
		{
			OLED_DrawBMP(0,0,127,8,BMP);
		}
		else if(mode==3 && res==1) //模式三进行控制1：红蓝灯亮度20
		{
			OLED_ShowCHinese(0,0,8);
			OLED_ShowCHinese(18,0,9);
			OLED_ShowString(32,0,":");
			OLED_ShowNum(54,0,20,3,16);
			OLED_ShowString(78,0,"%");
			PWM_SetCompare3(2);
			PWM_SetCompare4(2);
		}
		else if(mode==3 && res==2)//模式三进行控制2：红蓝灯亮度40
		{
			OLED_ShowCHinese(0,0,8);
			OLED_ShowCHinese(18,0,9);
			OLED_ShowString(32,0,":");
			OLED_ShowNum(54,0,40,3,16);
			OLED_ShowString(78,0,"%");
			PWM_SetCompare3(8000);
			PWM_SetCompare4(8000);	
		}
		else if(mode==3 && res==3)//模式三进行控制3：红蓝灯亮度60
		{
			OLED_ShowCHinese(0,0,8);
			OLED_ShowCHinese(18,0,9);
			OLED_ShowString(32,0,":");
			OLED_ShowNum(54,0,60,3,16);
			OLED_ShowString(78,0,"%");
			PWM_SetCompare3(12000);
			PWM_SetCompare4(12000);	
		}
		else if(mode==3 && res==4)//模式三进行控制4：红蓝灯亮度80
		{
			OLED_ShowCHinese(0,0,8);
			OLED_ShowCHinese(18,0,9);
			OLED_ShowString(32,0,":");
			OLED_ShowNum(54,0,80,3,16);
			OLED_ShowString(78,0,"%");
			PWM_SetCompare3(16000);
			PWM_SetCompare4(16000);
		}
		else if(mode==3 && res==5)//模式三进行控制5：舵机角度45
		{
			OLED_ShowCHinese(0,0,4);
			OLED_ShowCHinese(18,0,5);
			OLED_ShowCHinese(36,0,6);
			OLED_ShowCHinese(54,0,7);
			OLED_ShowNum(70,0,45,3,16);
			PWM_SetCompare2(1000);
		}
		else if(mode==3 && res==6)//模式三进行控制6：舵机角度90
		{
			OLED_ShowCHinese(0,0,4);
			OLED_ShowCHinese(18,0,5);
			OLED_ShowCHinese(36,0,6);
			OLED_ShowCHinese(54,0,7);
			OLED_ShowNum(70,0,90,3,16);
			PWM_SetCompare2(1500);
		}
		else if(mode==3 && res==7)//模式三进行控制7：舵机角度135
		{
			OLED_ShowCHinese(0,0,4);
			OLED_ShowCHinese(18,0,5);
			OLED_ShowCHinese(36,0,6);
			OLED_ShowCHinese(54,0,7);
			OLED_ShowNum(70,0,145,3,16);
			PWM_SetCompare2(2000);
		}
		else if(mode==3 && res==8)//模式三进行控制8：发送0到200的数据
		{
			OLED_ShowCHinese(0,0,13);
			OLED_ShowCHinese(18,0,14);
			OLED_ShowCHinese(36,0,15);
			OLED_ShowCHinese(54,0,16);
			OLED_ShowCHinese(72,0,17);
			for(t=0;t<200;t++)
			{
				USART1->DR=t;
				while((USART1->SR&0X40)==0);//等待发送结束
				delay_ms(5);
			}
			res=0;                //传输完成后，控制标志位清零
			OLED_Clear();         //清屏
		}
	}
}
