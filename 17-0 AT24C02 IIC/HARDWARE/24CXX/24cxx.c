#include "24cxx.h"
#include "myiic.h"
#include "delay.h"

void AT24CXX_Init()
{
	IIC_Init();
}
//在AT24CXX指定地址读出一个数据
//ReadAddr:开始读数的地址  
//返回值  :读到的数据
u8 AT24CXX_ReadOneByte(u16 ReadAddr)
{
	u8 temp;
	MYIIC_Start();
	MYIIC_Send_Byte(0XA0+((ReadAddr/256)<<1));
	MYIIC_Wait_Ack(); 
    MYIIC_Send_Byte(ReadAddr%256);   //发送低地址
	MYIIC_Wait_Ack();	    
	MYIIC_Start();  	 	   
	MYIIC_Send_Byte(0XA1);           //进入接收模式			   
	MYIIC_Wait_Ack();	 
    temp=MYIIC_Read_Byte(0);		   
    MYIIC_Stop();//产生一个停止条件	    
	return temp;	
	
}
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
{
	MYIIC_Start();
	MYIIC_Send_Byte(0XA0+((WriteAddr/256)<<1));
	MYIIC_Wait_Ack(); 
    MYIIC_Send_Byte(WriteAddr%256);   //发送低地址
	MYIIC_Wait_Ack();	    
	MYIIC_Send_Byte(DataToWrite);     //发送字节							   
	MYIIC_Wait_Ack();  		    	   
    MYIIC_Stop();//产生一个停止条件 
	delay_ms(10);	
}
//在AT24CXX里面的指定地址开始写入长度为Len的数据
//该函数用于写入16bit或者32bit的数据.
//WriteAddr  :开始写入的地址  
//DataToWrite:数据数组首地址
//Len        :要写入数据的长度2,4
void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
{  
	u8 t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr,(DataToWrite>>(8*t))&0xff);
	}
}
//在AT24CXX里面的指定地址开始读出长度为Len的数据
//该函数用于读出16bit或者32bit的数据.
//ReadAddr   :开始读出的地址 
//返回值     :数据
//Len        :要读出数据的长度2,4
u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len)
{
	u8 t;
	u32 temp;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1);
	}
	return temp;
}
//检查AT24CXX是否正常
//这里用了24XX的最后一个地址(255)来存储标志字.
//如果用其他24C系列,这个地址要修改
//返回1:检测失败
//返回0:检测成功
u8 AT24CXX_Check(void)
{
	u32 temp;
	temp=AT24CXX_ReadOneByte(255);
	if(temp==0x52)return 0;
	else
	{
		AT24CXX_WriteOneByte(255,0x52);
		temp=AT24CXX_ReadOneByte(255);
		if(temp==0x52)return 0;
	}
	return 1;
}
//在AT24CXX里面的指定地址开始读出指定个数的数据
//ReadAddr :开始读出的地址 对24c02为0~255
//pBuffer  :数据数组首地址
//NumToRead:要读出数据的个数
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	while(NumToRead)
	{		
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);
		NumToRead--;
	}
}
//在AT24CXX里面的指定地址开始写入指定个数的数据
//WriteAddr :开始写入的地址 对24c02为0~255
//pBuffer   :数据数组首地址
//NumToWrite:要写入数据的个数
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}
