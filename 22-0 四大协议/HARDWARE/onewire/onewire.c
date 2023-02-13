#include "stm32f10x.h"                  // Device header
#include "sys.h"
#include "delay.h"
#include "onewire.h"

//主机发送复位脉冲
void Onewire_Rst()
{
	Onewire_IO_OUT();
	Onewire_DQ_OUT=0;
	delay_us(520);
	Onewire_DQ_OUT=1;
	delay_us(20);
}
//主机接收应答脉冲
//返回1:未检测到DS18B20的存在
//返回0:存在
u8 Onewire_Check(void)
{
	u8 retry=0;
	/*1.检测存在脉冲*/
	Onewire_IO_IN();
	while(Onewire_DQ_IN&&retry<200)//等待从机拉低总线 （60~240 us 响应复位信号）
	{
		retry++;
		delay_us(1);
	}
	if(retry>=200)return 1;	/*2.检测从机是否释放总线*/	
	else retry=0;
	Onewire_IO_IN();
    while (!Onewire_DQ_IN&&retry<240)//判断从机是否释放总线（60~240 us 响应复位信号之后会释放总线）
	{
		retry++;
		delay_us(1);
	};
	if(retry>=240)return 1;	    
	return 0;	
}

//从从机读取一个位
//返回值：1/0
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

//从从机读取一个字节
//返回值：读到的数据
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
		Onewire_IO_OUT();//初始化为输出模式
		Onewire_DQ_OUT=0;
		delay_us(2);//主机拉低总线读数据时间隙2us	
		Onewire_DQ_OUT=1;//释放总线，准备读取位数据
		Onewire_IO_IN();//初始化为输入模式
		delay_us(10);//等待丛机的数据输出
		data>>=1;//高位补0，默认以0为准
		if(Onewire_DQ_IN)data|=0x80;
		delay_us(60); //延时确保主机采样周期已经过去（非常重要）
		Onewire_DQ_OUT=1;//释放总线准备读取下一位位数据
	}
	return data;
}
*/
//写一个字节到从机
//dat：要写入的字节
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
//初始化单总线的IO口 DQ 同时检测从机的存在
//返回1:不存在
//返回0:存在    	 
void Onewire_Init(void)
{
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PORTA口时钟 
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				//PORTA0 推挽输出
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);

 	GPIO_SetBits(GPIOA,GPIO_Pin_0);    //输出1
	delay_init();
}
