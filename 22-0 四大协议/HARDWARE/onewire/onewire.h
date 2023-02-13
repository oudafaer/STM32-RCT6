#ifndef __ONEWIRE_H
#define __ONEWIRE_H 
#include "sys.h"   


//IO方向设置
#define Onewire_IO_IN()  {GPIOA->CRL&=0XFFFFFFF0;GPIOA->CRL|=8<<0;}
#define Onewire_IO_OUT() {GPIOA->CRL&=0XFFFFFFF0;GPIOA->CRL|=3<<0;}
////IO操作函数											   
#define	Onewire_DQ_OUT PAout(0) //数据端口	PA0
#define	Onewire_DQ_IN  PAin(0)  //数据端口	PA0 

//主机发送复位脉冲
void Onewire_Rst(void);
u8 Onewire_Check(void);
u8 Onewire_Read_Bit(void);
u8 Onewire_Read_Byte(void);
void Onewire_Write_Byte(u8 dat);
void Onewire_Init(void);

#endif
