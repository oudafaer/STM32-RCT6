#include "oled.h"
#include "oledfont.h"
#include "sys.h"

/*��������*/
#define OLED_W_SCL(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_8, (BitAction)(x))
#define OLED_W_SDA(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_9, (BitAction)(x))

/*���ų�ʼ��*/
void OLED_I2C_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}

void delay_ma(unsigned int ms)
{
	unsigned int a;
	while(ms)
	{
		a=1800;
		while(a--);
		ms--;
	}
	return;
}

//iic start
void IIC_Start()
{
	OLED_W_SCL(1);
	OLED_W_SDA(1);
	OLED_W_SDA(0);
	OLED_W_SCL(0);
	
}

void IIC_Stop()
{
	OLED_W_SCL(1);
	OLED_W_SDA(0);
	OLED_W_SDA(1);
}

void IIC_Wait_Ack()
{
	OLED_W_SCL(1);
	OLED_W_SCL(0);
}
//iic write byte
void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	unsigned char m,da;
	da=IIC_Byte;
	OLED_W_SCL(0);
	for(i=0;i<8;i++)
	{
		m=da;
		m=m&0x80;
		if(m==0x80)
		{
			OLED_W_SDA(1);
		}
		else OLED_W_SDA(0);
		da=da<<1;
		OLED_W_SCL(1);
		OLED_W_SCL(0);
	}
}
//iic write command
void Write_IIC_Command(unsigned char IIC_Command)
{
	IIC_Start();
	Write_IIC_Byte(0x78);
	IIC_Wait_Ack();
	Write_IIC_Byte(0x00);
	IIC_Wait_Ack();
	Write_IIC_Byte(IIC_Command);
	IIC_Wait_Ack();
	IIC_Stop();
}
//iic weite Data
void Write_IIC_Data(unsigned char IIC_Data)
{
	IIC_Start();
	Write_IIC_Byte(0x78);
	IIC_Wait_Ack();
	Write_IIC_Byte(0x40);
	IIC_Wait_Ack();
	Write_IIC_Byte(IIC_Data);
	IIC_Wait_Ack();
	IIC_Stop();
}
//д���������
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
	{
		Write_IIC_Data(dat);
	}
	else
	{
		Write_IIC_Command(dat);
	}
}
// ����ͼƬ
void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_WR_Byte(0xb0+m,0);		//page0-page1
		OLED_WR_Byte(0x00,0);		//low column start address
		OLED_WR_Byte(0x10,0);		//high column start address
		for(n=0;n<128;n++)
			{
				OLED_WR_Byte(fill_Data,1);
			}
	}
}
//��ʱ����
void Delay_50ms(unsigned int Del_50ms)
{
	unsigned int m;
	for(;Del_50ms>0;Del_50ms--)
		for(m=6245;m>0;m--);
}
void Delay_1ms(unsigned int Del_1ms)
{
	unsigned char j;
	while(Del_1ms--)
	{	
		for(j=0;j<123;j++);
	}
}
//��������
void OLED_Set_Pos(unsigned char x,unsigned char y)
{
	OLED_WR_Byte(0xb0+y,0);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,0);
	OLED_WR_Byte((x&0x0f),0);
}
//oled��ʾ
void OLED_Open(void)
{
	OLED_WR_Byte(0X8D,0);  //SET DCDC����
	OLED_WR_Byte(0X14,0);  //DCDC ON
	OLED_WR_Byte(0XAF,0);  //DISPLAY ON
}
void OLED_Off(void)
{
	OLED_WR_Byte(0X8D,0);  //SET DCDC����
	OLED_WR_Byte(0X10,0);  //DCDC ON
	OLED_WR_Byte(0XAF,0);  //DISPLAY ON
}
//��������  
void OLED_Clear(void)  
{  
	unsigned char i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,0);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,0);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,0);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)
		{
			OLED_WR_Byte(0,1); 
		} 
	} //������ʾ
}
//ָ��λ����ʾ�ַ�
//x:0~27
//y:0~63
//Size:ѡ������ 16/12
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr,unsigned char Char_Size)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//�õ�ƫ�ƺ��ֵ			
		if(x>128-1){x=0;y=y+2;}
		if(Char_Size ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],1);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],1);
			}
			else {	
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
				OLED_WR_Byte(F6x8[c][i],1);
				
			}
}
//m*n����
unsigned long oled_pow(unsigned char m,unsigned char n)
{
	unsigned long result=1;
	while(n--)result*=m;
	return result;
}
//��ʾ��������
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned long num,unsigned char len,unsigned char size2)
{         	
	unsigned char t,temp;
	unsigned char enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
} 
//��ʾһ���ַ��Ŵ�
void OLED_ShowString(unsigned char x,unsigned char y,unsigned char *chr,unsigned char Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],Char_Size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}
//��ʾ����
void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char no)
{      			    
	unsigned char t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_Byte(Hzk[2*no][t],1);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte(Hzk[2*no+1][t],1);
				adder+=1;
      }					
}
//��ʾͼƬ
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],1);	    	
	    }
	}
} 
//��ʼ��SSD1306					    
void OLED_Init(void)
{
	OLED_I2C_Init();
	OLED_WR_Byte(0xAE,0);//--�ر���ʾ
	OLED_WR_Byte(0x00,0);//---set low column address
	OLED_WR_Byte(0x10,0);//---set high column address
	OLED_WR_Byte(0x40,0);//--set start line address  
	OLED_WR_Byte(0xB0,0);//--set page address
	OLED_WR_Byte(0x81,0); // �Աȶ�����
	OLED_WR_Byte(0xff,0);//--128   
	OLED_WR_Byte(0xA1,0);//set segment remap 
	OLED_WR_Byte(0xA6,0);//--normal / reverse
	OLED_WR_Byte(0xA8,0);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3F,0);//--1/32 duty
	OLED_WR_Byte(0xC8,0);//Com scan direction
	OLED_WR_Byte(0xD3,0);//-set display offset
	OLED_WR_Byte(0x00,0);//
	
	OLED_WR_Byte(0xD5,0);//set osc division
	OLED_WR_Byte(0x80,0);//
	
	OLED_WR_Byte(0xD8,0);//set area color mode off
	OLED_WR_Byte(0x05,0);//
	
	OLED_WR_Byte(0xD9,0);//Set Pre-Charge Period
	OLED_WR_Byte(0xF1,0);//
	
	OLED_WR_Byte(0xDA,0);//set com pin configuartion
	OLED_WR_Byte(0x12,0);//
	
	OLED_WR_Byte(0xDB,0);//set Vcomh
	OLED_WR_Byte(0x30,0);//
	
	OLED_WR_Byte(0x8D,0);//set charge pump enable
	OLED_WR_Byte(0x14,0);//
	
	OLED_WR_Byte(0xAF,0);//--turn on oled panel
} 
