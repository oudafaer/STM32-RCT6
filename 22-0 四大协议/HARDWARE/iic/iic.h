#ifndef __IIC_H
#define __IIC_H 

#include "sys.h"
#include "stdlib.h"	


//-----------------OLED�˿ڶ���---------------- 

#define IIC_SCL_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_12)//SCL
#define IIC_SCL_Set() GPIO_SetBits(GPIOB,GPIO_Pin_12)

#define IIC_SDA_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_13)//DIN
#define IIC_SDA_Set() GPIO_SetBits(GPIOB,GPIO_Pin_13)

#define IIC_CMD  0	//д����
#define IIC_DATA 1	//д����

#define u8 unsigned char
#define u32 unsigned int


void IIC_Start(void);//��ʼλ
void IIC_Stop(void);//ֹͣλ
void IIC_WaitACK(void);//�ȴ�Ӧ��
void Send_Byte(u8 dat);//����8λ����

void IIC_Init(void);//OLED�ĳ�ʼ��


#endif
