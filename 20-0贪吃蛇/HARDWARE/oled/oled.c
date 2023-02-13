#include "oled.h"
#include "delay.h"
#include "front.h"

u8 OLED_GRAM[128][8];//数组映射


void delay(u32 t)//粗略延时
{
	while(t--);
}

void I2C_Start(void)//开始位
{
	OLED_SDA_Set();
	OLED_SCL_Set();//SCL,SDA都设置为高电平
	delay_us(1);
	OLED_SDA_Clr();//产生跳变
	delay_us(1);
	OLED_SCL_Clr();//数据可变
}

void I2C_Stop(void)//停止位
{
	 OLED_SCL_Clr();
	 OLED_SDA_Clr();
	 delay_us(1);
	 OLED_SCL_Set();
	 OLED_SDA_Set();//低电平跳高电平
	 delay_us(1);
}

void I2C_WaitACK(void)//等待应答，每写完一个字节的数据都要等待应答
{
	 OLED_SCL_Clr();
	 OLED_SDA_Clr();//设为低电平，此时SDA数据可变
	 delay_us(1);
	 OLED_SCL_Set();//SCL设置为高，此时SDA写入数据
	 delay_us(1);//等待写入完成
     OLED_SCL_Clr();//数据此时可变	
}

void Send_Byte(u8 dat)//发送8位数据
{
	u8 i;
	for(i=0;i<8;i++)
	{
	    OLED_SCL_Clr();//设置为低电平，此时数据可变
		if(dat&0x80)//1位为真，SDA置高，即写入1
		{
			OLED_SDA_Set();//写入1
		}
		else
		{
			OLED_SDA_Clr();//写入0
		}
        OLED_SCL_Set();//数据被写入
		delay(1);
		OLED_SCL_Clr();//设置为低电平，此时数据可变
	    delay(1);
		dat<<=1;//数据左移一位，进行下一位数据的写入
	}
}


//发送一个字节
//向SSD1306写入一个字节。
//mode:数据/命令标志 0,表示命令;1,表示数据;
void OLED_WR_Byte(u8 dat,u8 mode)
{
	I2C_Start();//开始
	Send_Byte(0x78);//从机地址
	I2C_WaitACK();//等待应答
	if(mode) 
		Send_Byte(0x40);//发送数据
	else
		Send_Byte(0x00);//发送命令
	I2C_WaitACK();//等待应答
	Send_Byte(dat);
    I2C_WaitACK();//等待应答
	I2C_Stop();//关闭
}
//更新显存到OLED	，至关重要，显存数组中的内容实现函数
void OLED_Refresh(void)
{
	u8 i,n;
	for(i=0;i<8;i++)
	{
	   OLED_WR_Byte(0xb0+i,OLED_CMD); //设置行起始地址,页数
	   OLED_WR_Byte(0x00,OLED_CMD);   //设置低列起始地址
	   OLED_WR_Byte(0x10,OLED_CMD);   //设置高列起始地址
	   for(n=0;n<128;n++)
		 OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA);
  }
}
void OLED_Clear(void)
{
	u8 i,n;
	for(i=0;i<8;i++)
	{
	   for(n=0;n<128;n++)
			{
			 OLED_GRAM[n][i]=0;//清除所有数据
			}
  }
	OLED_Refresh();//更新显示
}

void OLED_SetPos(u8 x,u8 y)//设置坐标，y为页，
{
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte(x&0x0f,OLED_CMD);
}

void OLED_Point_Test(u8 x,u8 y,u8 dat)//点测试
{
   OLED_SetPos(x,y);
   OLED_WR_Byte(dat,OLED_DATA);
}

//画点 
//x:0~127
//y:0~63
void OLED_DrawPoint(u8 x,u8 y)
{
	u8 i,m,n;
	i=y/8;
	m=y%8;
	n=1<<m;
	OLED_GRAM[x][i]|=n;//由显存更新函数实现显示
}

//清除一个点
//x:0~127
//y:0~63
void OLED_ClearPoint(u8 x,u8 y)
{
	u8 i,m,n;
	i=y/8;
	m=y%8;
	n=1<<m;
	OLED_GRAM[x][i]=~OLED_GRAM[x][i];
	OLED_GRAM[x][i]|=n;
	OLED_GRAM[x][i]=~OLED_GRAM[x][i];
}


//画线
//x:0~128
//y:0~64
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2)
{
	u8 i,k,k1,k2;
	if(x1==x2)    //画竖线
	{
			for(i=0;i<(y2-y1);i++)
			{
				OLED_DrawPoint(x1,y1+i);
			}
  }
	else if(y1==y2)   //画横线
	{
			for(i=0;i<(x2-x1);i++)
			{
				OLED_DrawPoint(x1+i,y1);
			}
  }
	else      //画斜线
	{
		k1=y2-y1;
		k2=x2-x1;
		k=k1*10/k2;//斜率
		for(i=0;i<(x2-x1);i++)
			{
			  OLED_DrawPoint(x1+i,y1+i*k/10);
			}
	}
}
void OLED_ShowPicture(u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[])//显示图片
{
	u32 j=0;
	u8 x=0,y=0;
	if(y%8==0)y=0;
	else y+=1;
	for(y=y0;y<y1;y++)
	 {
		 OLED_WR_BP(x0,y);
		 for(x=x0;x<x1;x++)
		 {
			 OLED_WR_Byte(BMP[j],OLED_DATA);
			 j++;
     }
	 }
}
//配置写入数据的起始位置
void OLED_WR_BP(u8 x,u8 y)
{
	OLED_WR_Byte(0xb0+y,OLED_CMD);//设置行起始地址
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD);
}

//m^n
u32 OLED_Pow(u8 m,u8 n)
{
	u32 result=1;
	while(n--)
	{
	  result*=m;
	}
	return result;
}


//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//size:选择字体 12/16/24
//取模方式 逐列式
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1)
{
	u8 i,m,temp,size2,chr1;
	u8 y0=y;
	size2=(size1/8+((size1%8)?1:0))*(size1/2);  //得到字体一个字符对应点阵集所占的字节数
	chr1=chr-' ';  //计算偏移后的值
	for(i=0;i<size2;i++)
	{
        temp=asc2_1608[chr1][i]; //调用1608字体
		for(m=0;m<8;m++)           //写入数据
		{
			if(temp&0x80)OLED_DrawPoint(x,y);
			else OLED_ClearPoint(x,y);
			temp<<=1;
			y++;
			if((y-y0)==size1)
			{
			  y=y0;
			  x++;
			  break;
            }
		}
     }
}

//显示字符串
//x,y:起点坐标  
//size1:字体大小 
//*chr:字符串起始地址 
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1)
{
	while((*chr>=' ')&&(*chr<='~'))//判断是不是非法字符!
	{
		OLED_ShowChar(x,y,*chr,size1);
		x+=size1/2;
		if(x>128-size1)  //换行
		{
			x=0;
			y+=2;
    }
		chr++;
  }
}
////显示2个数字
////x,y :起点坐标	 
////len :数字的位数
////size:字体大小
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1)
{
	u8 t,temp;
	for(t=0;t<len;t++)
	{
		  temp=(num/OLED_Pow(10,len-t-1))%10;
			if(temp==0)
			{
				OLED_ShowChar(x+(size1/2)*t,y,'0',size1);
            }
			else 
			{
			  OLED_ShowChar(x+(size1/2)*t,y,temp+'0',size1);
			}
  }
}
void OLED_Init(void)//OLED的初始化
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
	
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel//关闭oled面板
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address//设置低列地址
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address//设置高列地址
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)设置起始线地址 设置映射 RAM 显示起始行
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register 设置对比度控制寄存器
	OLED_WR_Byte(0xCF,OLED_CMD);// Set SEG Output Current Brightness 设置 SEG 输出电流亮度
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常 设置 SEG/列映射
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常 设置 COM/行扫描方向
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display 设置正常显示
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64) 设置多路复用比（1 到 64）
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F) 设置显示偏移映射 RAM 计数器
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset 不偏移
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency 设置显示时钟分割比/振荡器频率
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec 设置除分割比，将时钟设置为 100 帧/秒
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period 设置预充电期
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock 将预充电设置为 15 时钟 + 放电设置为 1 时钟
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration 设置 com 引脚硬件配置
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh 设置 vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level 设置 VCOM 取消选择级别
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02) 设置页面寻址模式 （0x00/0x01/0x02）
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable 设置充电泵启用/禁用
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable 设置（0x10）禁用
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5) 禁用整个显示打开 （0xa4/0xa5）
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7)  禁用反向显示打开 （0xa6/a7）
	OLED_WR_Byte(0xAF,OLED_CMD);
	OLED_Clear();
	
}	


