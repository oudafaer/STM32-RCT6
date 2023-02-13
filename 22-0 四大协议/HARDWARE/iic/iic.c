#include "stm32f10x.h"                  // Device header
#include "IIC.h"
#include "delay.h"

void IIC_Init(void)//OLED的初始化
{
	//delay_ms(500);
	GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能A端口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //初始化GPIOG12
 	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //初始化GPIOG12
 	GPIO_SetBits(GPIOB,GPIO_Pin_13);
}

void delay(u32 t)//粗略延时
{
	while(t--);
}

void IIC_Start(void)//开始位
{
	IIC_SDA_Set();
	IIC_SCL_Set();//SCL,SDA都设置为高电平
	delay_us(1);
	IIC_SDA_Clr();//产生跳变
	delay_us(1);
	IIC_SCL_Clr();//数据可变
}

void IIC_Stop(void)//停止位
{
	 IIC_SCL_Clr();
	 IIC_SDA_Clr();
	 delay_us(1);
	 IIC_SCL_Set();
	 IIC_SDA_Set();//低电平跳高电平
	 delay_us(1);
}

void IIC_WaitACK(void)//等待应答，每写完一个字节的数据都要等待应答
{
	 IIC_SCL_Clr();
	 IIC_SDA_Clr();//设为低电平，此时SDA数据可变
	 delay_us(1);
	 IIC_SCL_Set();//SCL设置为高，此时SDA写入数据
	 delay_us(1);//等待写入完成
     IIC_SCL_Clr();//数据此时可变	
}

void Send_Byte(u8 dat)//发送8位数据
{
	u8 i;
	for(i=0;i<8;i++)
	{
	    IIC_SCL_Clr();//设置为低电平，此时数据可变
		if(dat&0x80)//1位为真，SDA置高，即写入1
		{
			IIC_SDA_Set();//写入1
		}
		else
		{
			IIC_SDA_Clr();//写入0
		}
        IIC_SCL_Set();//数据被写入
		delay(1);
		IIC_SCL_Clr();//设置为低电平，此时数据可变
	    delay(1);
		dat<<=1;//数据左移一位，进行下一位数据的写入
	}
}


//发送一个字节
//向SSD1306写入一个字节。
//mode:数据/命令标志 0,表示命令;1,表示数据;
void IIC_WR_Byte(u8 dat,u8 mode)
{
	IIC_Start();//开始
	Send_Byte(0x78);//从机地址
	IIC_WaitACK();//等待应答
	if(mode) 
		Send_Byte(0x40);//发送数据
	else
		Send_Byte(0x00);//发送命令
	IIC_WaitACK();//等待应答
	Send_Byte(dat);
    IIC_WaitACK();//等待应答
	IIC_Stop();//关闭
}
