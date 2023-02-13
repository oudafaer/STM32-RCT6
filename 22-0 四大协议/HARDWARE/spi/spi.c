#include "spi.h"
#include "stm32f10x.h"                  // Device header
#include "delay.h"

void SPI_WR_Byte(u8 dat,u8 cmd)
{	
	u8 i;			  
	if(cmd)                         //�ж�Ҫ����������������
	{
	  SPI_DC_Set();          
	}
	else 
	{
	  SPI_DC_Clr(); 
	}	 
	SPI_CS_Clr();                 //Ƭѡ�źţ��͵�ƽѡ��
	for(i=0;i<8;i++)              
	{			  
		SPI_SCLK_Clr();             //ʱ���ź�����
		if(dat&0x80)                 //���ݴ��䣬�ȴ������λMSB
		{
		   SPI_SDIN_Set();           
		}
		else 
		{
		   SPI_SDIN_Clr();
		}	
		SPI_SCLK_Set();             //ʱ���ź����ߣ��������������ص�ʱ����		
		dat<<=1;                     //�����ݵ��ұ�һλ�Ƶ����λ׼������		
	}				 		  
	SPI_CS_Set();                 //�������������Ƭѡ�źŽ���Ƭѡ	
	SPI_DC_Set();   	             //��������/�ź�ѡ����Ĭ���Ǵ�������  
} 
void SPI_init(void)
{ 	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	         //ʹ��PC,D,G�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_3;	 //PD3,PD6�������  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		           //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;              //�ٶ�50MHz
 	GPIO_Init(GPIOA, &GPIO_InitStructure);	                      //��ʼ��GPIOPA�˿�
 	GPIO_SetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_3);          	//PD3,PD6 �����

	SPI_RST_Set();                             //��λOLED
	delay_ms(100);
	SPI_RST_Clr();
	delay_ms(100);
	SPI_RST_Set(); 
}
