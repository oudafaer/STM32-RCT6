#ifndef __IIC_H
#define __IIC_H 

#include "sys.h"
#include "stdlib.h"	


//-----------------OLED端口定义---------------- 

#define IIC_SCL_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_12)//SCL
#define IIC_SCL_Set() GPIO_SetBits(GPIOB,GPIO_Pin_12)

#define IIC_SDA_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_13)//DIN
#define IIC_SDA_Set() GPIO_SetBits(GPIOB,GPIO_Pin_13)

#define IIC_CMD  0	//写命令
#define IIC_DATA 1	//写数据

#define u8 unsigned char
#define u32 unsigned int


void IIC_Start(void);//开始位
void IIC_Stop(void);//停止位
void IIC_WaitACK(void);//等待应答
void Send_Byte(u8 dat);//发送8位数据

void IIC_Init(void);//OLED的初始化


#endif
