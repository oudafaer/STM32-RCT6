#include "stm32f10x.h"                  // Device header
#include "sys.h"
#include "delay.h"
#include "onewire.h"

//�������͸�λ����
void Onewire_Rst()
{
	Onewire_IO_OUT();
	Onewire_DQ_OUT=0;
	delay_us(520);
	Onewire_DQ_OUT=1;
	delay_us(20);
}
//��������Ӧ������
//����1:δ��⵽DS18B20�Ĵ���
//����0:����
u8 Onewire_Check(void)
{
	u8 retry=0;
	/*1.����������*/
	Onewire_IO_IN();
	while(Onewire_DQ_IN&&retry<200)//�ȴ��ӻ��������� ��60~240 us ��Ӧ��λ�źţ�
	{
		retry++;
		delay_us(1);
	}
	if(retry>=200)return 1;	/*2.���ӻ��Ƿ��ͷ�����*/	
	else retry=0;
	Onewire_IO_IN();
    while (!Onewire_DQ_IN&&retry<240)//�жϴӻ��Ƿ��ͷ����ߣ�60~240 us ��Ӧ��λ�ź�֮����ͷ����ߣ�
	{
		retry++;
		delay_us(1);
	};
	if(retry>=240)return 1;	    
	return 0;	
}

//�Ӵӻ���ȡһ��λ
//����ֵ��1/0
u8 Onewire_Read_Bit(void) 			 // read one bit
{
	u8 data;
	Onewire_IO_OUT();
	Onewire_DQ_OUT=0;
	delay_us(2);
	Onewire_DQ_OUT=1;
	Onewire_IO_IN();
	delay_us(12);
	if(Onewire_DQ_IN)data=1;
	else data=0;
	delay_us(52);
	return data;
}

//�Ӵӻ���ȡһ���ֽ�
//����ֵ������������
u8 Onewire_Read_Byte(void)    // read one byte
{
	u8 i,j,data;
	data=0;
	for(i=0;i<8;i++)
	{
		j=Onewire_Read_Bit();
		data=(j<<7)|(data>>1);
	}
	return data;
}
/*
u8 Onewire_Read_Byte(void)
{
	u8 i,data=0;
	for(i=0;i<8;i++)
	{
		Onewire_IO_OUT();//��ʼ��Ϊ���ģʽ
		Onewire_DQ_OUT=0;
		delay_us(2);//�����������߶�����ʱ��϶2us	
		Onewire_DQ_OUT=1;//�ͷ����ߣ�׼����ȡλ����
		Onewire_IO_IN();//��ʼ��Ϊ����ģʽ
		delay_us(10);//�ȴ��Ի����������
		data>>=1;//��λ��0��Ĭ����0Ϊ׼
		if(Onewire_DQ_IN)data|=0x80;
		delay_us(60); //��ʱȷ���������������Ѿ���ȥ���ǳ���Ҫ��
		Onewire_DQ_OUT=1;//�ͷ�����׼����ȡ��һλλ����
	}
	return data;
}
*/
//дһ���ֽڵ��ӻ�
//dat��Ҫд����ֽ�
void Onewire_Write_Byte(u8 dat)     
{
	u8 i;
	u8 wei;
	Onewire_IO_OUT();
	for(i=0;i<8;i++)
	{
		wei=dat&0x01;
		dat=dat>>1;
		if(wei)
		{
			Onewire_DQ_OUT=0;
			delay_us(2);
			Onewire_DQ_OUT=1;
			delay_us(60);
		}
		else
		{
			Onewire_DQ_OUT=0;
			delay_us(60);
			Onewire_DQ_OUT=1;
			delay_us(2);
		}
	}
}
//��ʼ�������ߵ�IO�� DQ ͬʱ���ӻ��Ĵ���
//����1:������
//����0:����    	 
void Onewire_Init(void)
{
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PORTA��ʱ�� 
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				//PORTA0 �������
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);

 	GPIO_SetBits(GPIOA,GPIO_Pin_0);    //���1
	delay_init();
}
