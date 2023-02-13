#ifndef __OLED_H
#define __OLED_H 

#include "sys.h"
#include "stdlib.h"	


//-----------------OLED端口定义---------------- 

#define OLED_SCL_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_12)//SCL
#define OLED_SCL_Set() GPIO_SetBits(GPIOB,GPIO_Pin_12)

#define OLED_SDA_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_13)//DIN
#define OLED_SDA_Set() GPIO_SetBits(GPIOB,GPIO_Pin_13)

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

#define u8 unsigned char
#define u32 unsigned int

extern u8 OLED_GRAM[128][8];

void I2C_Start(void);//开始位
void I2C_Stop(void);//停止位
void I2C_WaitACK(void);//等待应答
void Send_Byte(u8 dat);//发送8位数据

void OLED_Init(void);//OLED的初始化
void OLED_WR_BP(u8 x,u8 y);//配置写入数据的起始位置
void OLED_Clear(void);//清屏函数
void OLED_Refresh(void);//更新显存到OLED	
void OLED_WR_Byte(u8 dat,u8 mode);//发送一个字节
void OLED_Point_Test(u8 x,u8 y,u8 dat);//点测试

///////////////功能函数//////////////////
void OLED_DrawPoint(u8 x,u8 y);//画点
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2);//画线
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1);////显示2个数字
void OLED_ClearPoint(u8 x,u8 y);//清除点
void OLED_ShowPicture(u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[]);//显示图片
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1);//显示数字
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1);//显示字符
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1);//显示字符串



#endif
