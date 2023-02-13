#ifndef __OLED_H
#define __OLED_H 

#include "sys.h"
#include "stdlib.h"	


//-----------------OLED�˿ڶ���---------------- 

#define OLED_SCL_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_12)//SCL
#define OLED_SCL_Set() GPIO_SetBits(GPIOB,GPIO_Pin_12)

#define OLED_SDA_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_13)//DIN
#define OLED_SDA_Set() GPIO_SetBits(GPIOB,GPIO_Pin_13)

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

#define u8 unsigned char
#define u32 unsigned int

extern u8 OLED_GRAM[128][8];

void I2C_Start(void);//��ʼλ
void I2C_Stop(void);//ֹͣλ
void I2C_WaitACK(void);//�ȴ�Ӧ��
void Send_Byte(u8 dat);//����8λ����

void OLED_Init(void);//OLED�ĳ�ʼ��
void OLED_WR_BP(u8 x,u8 y);//����д�����ݵ���ʼλ��
void OLED_Clear(void);//��������
void OLED_Refresh(void);//�����Դ浽OLED	
void OLED_WR_Byte(u8 dat,u8 mode);//����һ���ֽ�
void OLED_Point_Test(u8 x,u8 y,u8 dat);//�����

///////////////���ܺ���//////////////////
void OLED_DrawPoint(u8 x,u8 y);//����
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2);//����
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1);////��ʾ2������
void OLED_ClearPoint(u8 x,u8 y);//�����
void OLED_ShowPicture(u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[]);//��ʾͼƬ
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1);//��ʾ����
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1);//��ʾ�ַ�
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1);//��ʾ�ַ���



#endif
