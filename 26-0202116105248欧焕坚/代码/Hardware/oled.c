//******************************************************************************/
#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"  	 
#include "delay.h"

/********************************************************************************
@brief: 向SSD1106写入一个字节。
@param: dat:要写入的数据/命令      cmd:数据/命令标志 0,表示命令;1,表示数据;
@return: none
*********************************************************************************/
void OLED_WR_Byte(u8 dat,u8 cmd)
{	
	u8 i;			  
	if(cmd)                         //判断要传输的是命令还是数据
	{
	  OLED_DC_Set();          
	}
	else 
	{
	  OLED_DC_Clr();
	}	
  
	OLED_CS_Clr();                 //片选信号，低电平选中
	
	for(i=0;i<8;i++)              
	{			  
		OLED_SCLK_Clr();             //时钟信号拉低
		
		if(dat&0x80)                 //数据传输，先传数最高位MSB
		{
		   OLED_SDIN_Set();           
		}
		else 
		{
		   OLED_SDIN_Clr();
		}
		
		OLED_SCLK_Set();             //时钟信号拉高，数据是在上升沿的时候传输
		
		dat<<=1;                     //将数据的右边一位移到最高位准备传输
		
	}				 		  
	OLED_CS_Set();                 //传输结束，拉高片选信号结束片选
	
	OLED_DC_Set();   	             //拉高数据/信号选择线默认是传输数据  
} 

/********************************************************************************
@brief: 设置光标位置  
@param: x,y:光标位置坐标
@return: none
*********************************************************************************/
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); 
} 

/********************************************************************************
@brief: 开显示  
@param: none
@return: none
*********************************************************************************/
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}

/********************************************************************************
@brief: 关显示  
@param: none
@return: none
*********************************************************************************/     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 

/********************************************************************************
@brief: 清屏函数,清完屏,整个屏幕是黑色的!
@param: none
@return: none
*********************************************************************************/
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i = 0;i < 8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址 
		
		for(n = 0;n < 132;n++)
		{
			OLED_WR_Byte(0,OLED_DATA);
		}			
	} 
}

/********************************************************************************
@brief: 显示一个字符   
@param: x,y:显示字符的坐标，x:0-127 y:0-7 chr:要显示的字符
@return: none
*********************************************************************************/
void OLED_ShowChar(u8 x,u8 y,u8 chr)
{      	
	  u8 c=0,i=0;
	
		c = chr - ' ';                    //得到偏移后的值
	
		if(x>Max_Column-1)                //当显示的字符超过x轴范围在下一行显示
      {
			  x = 0;
				y = y+2;
			}
			
		if(SIZE == 16)                    //当字体是16时，在y轴方向上是16位x轴方向上是8位
			{
				OLED_Set_Pos(x,y);           //设置光标位置
				
				for(i=0;i<8;i++)             //先打印上半部分，比如一个|，先打印它的上半部分
				{
				  OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);    
				}
				
				OLED_Set_Pos(x,y+1);         //y的页加一
				
				for(i=0;i<8;i++)
				{
					OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
			
				}
			}
			else                          //6X8字体
			{	
				OLED_Set_Pos(x,y+1);
				
				for(i=0;i<6;i++)
				{
				   OLED_WR_Byte(F6x8[c*6][i],OLED_DATA);	
				}
			}
}

/********************************************************************************
@brief:  m^n
@param:  none
@return: none
*********************************************************************************/
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;
	
	while(n--)
	{
		result *= m;
	}    
	return result;
}	

/********************************************************************************
@brief: 显示数字   
@param: x,y:显示数字的坐标，x:0-127 y:0-7 num:要显示的数字（0-2^31-1） len:数字长度 size:显示数字的字体大小可选16和8
@return: none
*********************************************************************************/ 
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;
	
	for(t=0;t<len;t++)
	{
		temp = (num/oled_pow(10,len-t-1)) % 10; //把要显示的数字的位提取出来，比如要显示1234,要先显示“1”, 1 = (1234/10^(4-0-1))%10. 2 = (1234/10^(4-1-1))%10
		
		if(enshow == 0 && t < (len-1))
		{
			if(temp == 0)
			{
				OLED_ShowChar(x+(size/2) * t,y,' ');
				continue;
			}
			else
			{				
				enshow=1; 
			}	 	 
		}
	 	OLED_ShowChar(x+(size/2) * t,y,temp + '0'); 
	}
} 
/********************************************************************************
@brief: 显示一个字符串 ，只能显示8X16的字符  
@param: x,y:显示字符串的坐标，x:0-127 y:0-7 chr:要显示的字符的指针
@return: none
*********************************************************************************/
void OLED_ShowString(u8 x,u8 y,u8 *chr)
{
	unsigned char j=0;
	
	while (chr[j] != '\0')  //字符串要以‘\0’结束，且只能显示英文字符
	{		
		OLED_ShowChar(x,y,chr[j]);
		
		x += 8;
		
		if(x > 120)
			{
			   x = 0;
			   y += 2;
			}
			j++;
	}
}
/********************************************************************************
@brief: 显示一个汉字   
@param: x,y:显示字符的坐标，x:0-127 y:0-7 HZ:要显示的字符位置
@return: none
*********************************************************************************/
void OLED_ShowCHinese(u8 x,u8 y,u8 HZ)
{      			    
	u8 t;
	
	OLED_Set_Pos(x,y);                    //打印上半部分
	
    for(t=0;t<16;t++)                  //汉字是16X16大小的
		{
				OLED_WR_Byte(Hzk[2*HZ][t],OLED_DATA);
				
     }	
		
		OLED_Set_Pos(x,y+1);	              //打印下半部分
		 
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte(Hzk[2*HZ+1][t],OLED_DATA);
				
      }					
}
/********************************************************************************
@brief: 显示一个图片   
@param: x0,y0:显示图片的的开始坐标x1,y1终止坐标 BMP:要显示的图片指针
@return: none
*********************************************************************************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,const unsigned char *BMP)
{ 	
 unsigned int j = 0;
 unsigned char x,y;
  
  if(y1%8 == 0)
	{		
		y = y1/8;
	}		
  else 
	{
		y = y1/8+1;
	}
	for(y = y0;y < y1;y++)
	{
		OLED_Set_Pos(x0,y);
		
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
	    }
	}
} 

/********************************************************************************
@brief: 初始化OLED，初始化的数据时SSD1306厂家提供
@param: none
@return: none
*********************************************************************************/					    
void OLED_Init(void)
{ 	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	         //使能PC,D,G端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	         //使能PC,D,G端口时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	 //PD3,PD6推挽输出  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		           //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;              //速度50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	                      //初始化GPIOPA端口
 	GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);          	//PD3,PD6 输出高
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	 //PD3,PD6推挽输出  
 	GPIO_Init(GPIOA, &GPIO_InitStructure);	                      //初始化GPIOPA端口
 	GPIO_SetBits(GPIOA,GPIO_Pin_8);          	//PD3,PD6 输出高
	
  OLED_RST_Set();                             //复位OLED
	delay_ms(100);
	OLED_RST_Clr();
	delay_ms(100);
	OLED_RST_Set(); 
	
/**********************8以下是OLED控制芯片默认配置数据******************************/		
	
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	
	OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
	OLED_Clear();
	OLED_Set_Pos(0,0); 	
}  





























