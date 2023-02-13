#ifndef __SPI_H
#define __SPI_H			  	 
#include "sys.h"
#include "stdlib.h"	    

//-----------------OLED端口定义---------------- 

#define SPI_CS_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_3)//CS
#define SPI_CS_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_3)

#define SPI_RST_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_4)//RES
#define SPI_RST_Set() GPIO_SetBits(GPIOA,GPIO_Pin_4)

#define SPI_DC_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_5)//DC
#define SPI_DC_Set() GPIO_SetBits(GPIOA,GPIO_Pin_5)

#define SPI_SCLK_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_6)//CLK
#define SPI_SCLK_Set() GPIO_SetBits(GPIOA,GPIO_Pin_6)

#define SPI_SDIN_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_7)//DIN
#define SPI_SDIN_Set() GPIO_SetBits(GPIOA,GPIO_Pin_7)

 		     
#define SPI_CMD  0	//写命令
#define SPI_DATA 1	//写数据



#endif  
