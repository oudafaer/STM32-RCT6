#include "spi.h"
#include "stm32f10x.h"                  // Device header
#include "delay.h"

void SPI_WR_Byte(u8 dat,u8 cmd)
{	
	u8 i;			  
	if(cmd)                         //判断要传输的是命令还是数据
	{
	  SPI_DC_Set();          
	}
	else 
	{
	  SPI_DC_Clr(); 
	}	 
	SPI_CS_Clr();                 //片选信号，低电平选中
	for(i=0;i<8;i++)              
	{			  
		SPI_SCLK_Clr();             //时钟信号拉低
		if(dat&0x80)                 //数据传输，先传数最高位MSB
		{
		   SPI_SDIN_Set();           
		}
		else 
		{
		   SPI_SDIN_Clr();
		}	
		SPI_SCLK_Set();             //时钟信号拉高，数据是在上升沿的时候传输		
		dat<<=1;                     //将数据的右边一位移到最高位准备传输		
	}				 		  
	SPI_CS_Set();                 //传输结束，拉高片选信号结束片选	
	SPI_DC_Set();   	             //拉高数据/信号选择线默认是传输数据  
} 
void SPI_init(void)
{ 	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	         //使能PC,D,G端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_3;	 //PD3,PD6推挽输出  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		           //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;              //速度50MHz
 	GPIO_Init(GPIOA, &GPIO_InitStructure);	                      //初始化GPIOPA端口
 	GPIO_SetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_3);          	//PD3,PD6 输出高

	SPI_RST_Set();                             //复位OLED
	delay_ms(100);
	SPI_RST_Clr();
	delay_ms(100);
	SPI_RST_Set(); 
}
