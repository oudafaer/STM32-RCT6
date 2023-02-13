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
	u8 mode=0;     //ģʽѡ��
	u8 res;	  	//ģʽ������ѡ��
	u32 shudu;     //��������ٶȲ���
	char RX_BUF[200]; //���ջ�����
	u16 t;            //���ݳ���
	u16 adcx;         //ADC����ֵ
	float temp;       //��ѹת���м����
	delay_init();      //������ʱ����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�  	
	PWM_Init();        //����PWM��ARR=2000 - 1��PSC=720 - 1����Ƶ��Ϊ50HZ
	OLED_Init();       //oled����
	Adc_Init();         //ADC����
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	OLED_DrawBMP(0,0,127,8,BMP1);   //���ؿ�ʼ����
	while (1)
	{
		if(USART_RX_STA&0x8000)  //�жϴ����Ƿ���ɽ���
		{
			OLED_Clear();         //����
			t=USART_RX_STA&0x3FFF;   //�õ��������ݳ���
			for(u8 i=0;i<t;i++)     
			{
				RX_BUF[i]=USART_RX_BUF[i];   //�����ݻ��浽RX_BUF
				while((USART1->SR&0X40)==0); 
			}
			printf("\r\n ���ճɹ� \r\n");     //��ӡ���������ʾ
			USART_RX_STA=0;                  //���ձ�־λ�ֶ���0
			if(!(strcmp(RX_BUF,"ģʽһ")))   //�жϽ����ַ���
			{
				mode=1;                     //��Ӧģʽѡ��
				res=0;                      //��Ӧ����ѡ��
				memset(RX_BUF,0,strlen(RX_BUF)); //���ջ���������
			}
			else if(!(strcmp(RX_BUF,"ģʽ��"))) //�жϽ����ַ���
			{
				mode=2;                          //��Ӧģʽѡ��
				res=0;                          //��Ӧ����ѡ��
				memset(RX_BUF,0,strlen(RX_BUF)); //���ջ���������
			}
			else if(!(strcmp(RX_BUF,"ģʽ��"))) //�жϽ����ַ���
			{
				mode=3;                         //��Ӧģʽѡ��
				res=0;                          //��Ӧ����ѡ��
				memset(RX_BUF,0,strlen(RX_BUF)); //���ջ���������
			}
			else if(!(strcmp(RX_BUF,"ģʽ��"))) //�жϽ����ַ���
			{
				mode=4;                         //��Ӧģʽѡ��
				res=0;                          //��Ӧ����ѡ��
				memset(RX_BUF,0,strlen(RX_BUF)); //���ջ���������
			}
			else if(!(strcmp(RX_BUF,"����1"))) //�жϽ����ַ���
			{
				res=1;                          //��Ӧ����ѡ��
				memset(RX_BUF,0,strlen(RX_BUF)); //���ջ���������
			}
			else if(!(strcmp(RX_BUF,"����2"))) //�жϽ����ַ���
			{
				res=2;                           //��Ӧ����ѡ��
				memset(RX_BUF,0,strlen(RX_BUF)); //���ջ���������
			}
			else if(!(strcmp(RX_BUF,"����3"))) //�жϽ����ַ���
			{
				res=3;                            //��Ӧ����ѡ��
				memset(RX_BUF,0,strlen(RX_BUF)); //���ջ���������
			}
			else if(!(strcmp(RX_BUF,"����4"))) //�жϽ����ַ���
			{
				res=4;                           //��Ӧ����ѡ��
				memset(RX_BUF,0,strlen(RX_BUF)); //���ջ���������
			}
			else if(!(strcmp(RX_BUF,"�Ƕ�A"))) //�жϽ����ַ���
			{
				res=5;                          //��Ӧ����ѡ��
				memset(RX_BUF,0,strlen(RX_BUF)); //���ջ���������
			}
			else if(!(strcmp(RX_BUF,"�Ƕ�B"))) //�жϽ����ַ���
			{
				res=6;                        //��Ӧ����ѡ��
				memset(RX_BUF,0,strlen(RX_BUF)); //���ջ���������
			}
			else if(!(strcmp(RX_BUF,"�Ƕ�C"))) //�жϽ����ַ���
			{
				res=7;                         //��Ӧ����ѡ��
				memset(RX_BUF,0,strlen(RX_BUF)); //���ջ���������
			}
			else if(!(strcmp(RX_BUF,"��������"))) //�жϽ����ַ���
			{
				res=8;                            //��Ӧ����ѡ��
				memset(RX_BUF,0,strlen(RX_BUF)); //���ջ���������
			}
			else  //�жϽ����ַ���
			{
				OLED_DrawBMP(0,0,127,8,BMP4);
				memset(RX_BUF,0,strlen(RX_BUF)); //���ջ���������
			}
			
		}
		if(mode==1) //ģʽһ����ƣ����ƽ��к�����
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
		else if(mode==2)//ģʽ���������45�ȵ�135�Ƚ��������˶�
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
		else if(mode==4)       //ģʽ�ģ���0~5V��ѹ���м�⣬�������ڵ�Ƭ���˿�ֻ�ܼ�⵽3.3V�����Բ����˵����ѹ
		{
			//ADC����ѹ
			OLED_ShowString(0,0,"ADC:");
			OLED_ShowCHinese(0,2,10);
			OLED_ShowCHinese(18,2,11);
			OLED_ShowCHinese(36,2,12);			
			adcx=Get_Adc_Average(ADC_Channel_0,25);
			OLED_ShowNum(32,0,adcx,4,16);//��ʾADC��ֵ
			temp=(float)adcx*(5.0/4095);
			adcx=temp;
			OLED_ShowNum(54,2,adcx,1,16);//��ʾ��ѹֵ
			temp-=adcx;
			temp*=1000;
			OLED_ShowChar(62,2,'.');
			OLED_ShowNum(70,2,temp,2,16);
			delay_ms(250);				
			
		}
		else if(mode==3 && res==0)//ģʽ����ʼ����
		{
			OLED_DrawBMP(0,0,127,8,BMP);
		}
		else if(mode==3 && res==1) //ģʽ�����п���1������������20
		{
			OLED_ShowCHinese(0,0,8);
			OLED_ShowCHinese(18,0,9);
			OLED_ShowString(32,0,":");
			OLED_ShowNum(54,0,20,3,16);
			OLED_ShowString(78,0,"%");
			PWM_SetCompare3(2);
			PWM_SetCompare4(2);
		}
		else if(mode==3 && res==2)//ģʽ�����п���2������������40
		{
			OLED_ShowCHinese(0,0,8);
			OLED_ShowCHinese(18,0,9);
			OLED_ShowString(32,0,":");
			OLED_ShowNum(54,0,40,3,16);
			OLED_ShowString(78,0,"%");
			PWM_SetCompare3(8000);
			PWM_SetCompare4(8000);	
		}
		else if(mode==3 && res==3)//ģʽ�����п���3������������60
		{
			OLED_ShowCHinese(0,0,8);
			OLED_ShowCHinese(18,0,9);
			OLED_ShowString(32,0,":");
			OLED_ShowNum(54,0,60,3,16);
			OLED_ShowString(78,0,"%");
			PWM_SetCompare3(12000);
			PWM_SetCompare4(12000);	
		}
		else if(mode==3 && res==4)//ģʽ�����п���4������������80
		{
			OLED_ShowCHinese(0,0,8);
			OLED_ShowCHinese(18,0,9);
			OLED_ShowString(32,0,":");
			OLED_ShowNum(54,0,80,3,16);
			OLED_ShowString(78,0,"%");
			PWM_SetCompare3(16000);
			PWM_SetCompare4(16000);
		}
		else if(mode==3 && res==5)//ģʽ�����п���5������Ƕ�45
		{
			OLED_ShowCHinese(0,0,4);
			OLED_ShowCHinese(18,0,5);
			OLED_ShowCHinese(36,0,6);
			OLED_ShowCHinese(54,0,7);
			OLED_ShowNum(70,0,45,3,16);
			PWM_SetCompare2(1000);
		}
		else if(mode==3 && res==6)//ģʽ�����п���6������Ƕ�90
		{
			OLED_ShowCHinese(0,0,4);
			OLED_ShowCHinese(18,0,5);
			OLED_ShowCHinese(36,0,6);
			OLED_ShowCHinese(54,0,7);
			OLED_ShowNum(70,0,90,3,16);
			PWM_SetCompare2(1500);
		}
		else if(mode==3 && res==7)//ģʽ�����п���7������Ƕ�135
		{
			OLED_ShowCHinese(0,0,4);
			OLED_ShowCHinese(18,0,5);
			OLED_ShowCHinese(36,0,6);
			OLED_ShowCHinese(54,0,7);
			OLED_ShowNum(70,0,145,3,16);
			PWM_SetCompare2(2000);
		}
		else if(mode==3 && res==8)//ģʽ�����п���8������0��200������
		{
			OLED_ShowCHinese(0,0,13);
			OLED_ShowCHinese(18,0,14);
			OLED_ShowCHinese(36,0,15);
			OLED_ShowCHinese(54,0,16);
			OLED_ShowCHinese(72,0,17);
			for(t=0;t<200;t++)
			{
				USART1->DR=t;
				while((USART1->SR&0X40)==0);//�ȴ����ͽ���
				delay_ms(5);
			}
			res=0;                //������ɺ󣬿��Ʊ�־λ����
			OLED_Clear();         //����
		}
	}
}
