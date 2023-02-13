#ifndef __MYIIC_H
#define __MYIIC_H

#include "sys.h"

//IO方向设置
#define SDA_IN()  {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=8<<12;}
#define SDA_OUT() {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=3<<12;}

//IO操作函数	 
#define IIC_SCL    PCout(12) //SCL
#define IIC_SDA    PCout(11) //SDA	 
#define READ_SDA   PCin(11)  //输入SDA 

void IIC_Init(void);
void MYIIC_Start(void);
void MYIIC_Stop(void);
u8 MYIIC_Wait_Ack(void);
void MYIIC_Ack(void);
void MYIIC_NAck(void);
void MYIIC_Send_Byte(u8 txd);
u8 MYIIC_Read_Byte(unsigned char ack);


#endif
