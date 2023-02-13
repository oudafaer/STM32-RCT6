#include "oled.h"
#include "delay.h"
#include "front.h"

u8 OLED_GRAM[128][8];//����ӳ��


void delay(u32 t)//������ʱ
{
	while(t--);
}

void I2C_Start(void)//��ʼλ
{
	OLED_SDA_Set();
	OLED_SCL_Set();//SCL,SDA������Ϊ�ߵ�ƽ
	delay_us(1);
	OLED_SDA_Clr();//��������
	delay_us(1);
	OLED_SCL_Clr();//���ݿɱ�
}

void I2C_Stop(void)//ֹͣλ
{
	 OLED_SCL_Clr();
	 OLED_SDA_Clr();
	 delay_us(1);
	 OLED_SCL_Set();
	 OLED_SDA_Set();//�͵�ƽ���ߵ�ƽ
	 delay_us(1);
}

void I2C_WaitACK(void)//�ȴ�Ӧ��ÿд��һ���ֽڵ����ݶ�Ҫ�ȴ�Ӧ��
{
	 OLED_SCL_Clr();
	 OLED_SDA_Clr();//��Ϊ�͵�ƽ����ʱSDA���ݿɱ�
	 delay_us(1);
	 OLED_SCL_Set();//SCL����Ϊ�ߣ���ʱSDAд������
	 delay_us(1);//�ȴ�д�����
     OLED_SCL_Clr();//���ݴ�ʱ�ɱ�	
}

void Send_Byte(u8 dat)//����8λ����
{
	u8 i;
	for(i=0;i<8;i++)
	{
	    OLED_SCL_Clr();//����Ϊ�͵�ƽ����ʱ���ݿɱ�
		if(dat&0x80)//1λΪ�棬SDA�øߣ���д��1
		{
			OLED_SDA_Set();//д��1
		}
		else
		{
			OLED_SDA_Clr();//д��0
		}
        OLED_SCL_Set();//���ݱ�д��
		delay(1);
		OLED_SCL_Clr();//����Ϊ�͵�ƽ����ʱ���ݿɱ�
	    delay(1);
		dat<<=1;//��������һλ��������һλ���ݵ�д��
	}
}


//����һ���ֽ�
//��SSD1306д��һ���ֽڡ�
//mode:����/�����־ 0,��ʾ����;1,��ʾ����;
void OLED_WR_Byte(u8 dat,u8 mode)
{
	I2C_Start();//��ʼ
	Send_Byte(0x78);//�ӻ���ַ
	I2C_WaitACK();//�ȴ�Ӧ��
	if(mode) 
		Send_Byte(0x40);//��������
	else
		Send_Byte(0x00);//��������
	I2C_WaitACK();//�ȴ�Ӧ��
	Send_Byte(dat);
    I2C_WaitACK();//�ȴ�Ӧ��
	I2C_Stop();//�ر�
}
//�����Դ浽OLED	��������Ҫ���Դ������е�����ʵ�ֺ���
void OLED_Refresh(void)
{
	u8 i,n;
	for(i=0;i<8;i++)
	{
	   OLED_WR_Byte(0xb0+i,OLED_CMD); //��������ʼ��ַ,ҳ��
	   OLED_WR_Byte(0x00,OLED_CMD);   //���õ�����ʼ��ַ
	   OLED_WR_Byte(0x10,OLED_CMD);   //���ø�����ʼ��ַ
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
			 OLED_GRAM[n][i]=0;//�����������
			}
  }
	OLED_Refresh();//������ʾ
}

void OLED_SetPos(u8 x,u8 y)//�������꣬yΪҳ��
{
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte(x&0x0f,OLED_CMD);
}

void OLED_Point_Test(u8 x,u8 y,u8 dat)//�����
{
   OLED_SetPos(x,y);
   OLED_WR_Byte(dat,OLED_DATA);
}

//���� 
//x:0~127
//y:0~63
void OLED_DrawPoint(u8 x,u8 y)
{
	u8 i,m,n;
	i=y/8;
	m=y%8;
	n=1<<m;
	OLED_GRAM[x][i]|=n;//���Դ���º���ʵ����ʾ
}

//���һ����
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


//����
//x:0~128
//y:0~64
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2)
{
	u8 i,k,k1,k2;
	if(x1==x2)    //������
	{
			for(i=0;i<(y2-y1);i++)
			{
				OLED_DrawPoint(x1,y1+i);
			}
  }
	else if(y1==y2)   //������
	{
			for(i=0;i<(x2-x1);i++)
			{
				OLED_DrawPoint(x1+i,y1);
			}
  }
	else      //��б��
	{
		k1=y2-y1;
		k2=x2-x1;
		k=k1*10/k2;//б��
		for(i=0;i<(x2-x1);i++)
			{
			  OLED_DrawPoint(x1+i,y1+i*k/10);
			}
	}
}
void OLED_ShowPicture(u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[])//��ʾͼƬ
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
//����д�����ݵ���ʼλ��
void OLED_WR_BP(u8 x,u8 y)
{
	OLED_WR_Byte(0xb0+y,OLED_CMD);//��������ʼ��ַ
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


//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//size:ѡ������ 12/16/24
//ȡģ��ʽ ����ʽ
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1)
{
	u8 i,m,temp,size2,chr1;
	u8 y0=y;
	size2=(size1/8+((size1%8)?1:0))*(size1/2);  //�õ�����һ���ַ���Ӧ������ռ���ֽ���
	chr1=chr-' ';  //����ƫ�ƺ��ֵ
	for(i=0;i<size2;i++)
	{
        temp=asc2_1608[chr1][i]; //����1608����
		for(m=0;m<8;m++)           //д������
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

//��ʾ�ַ���
//x,y:�������  
//size1:�����С 
//*chr:�ַ�����ʼ��ַ 
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1)
{
	while((*chr>=' ')&&(*chr<='~'))//�ж��ǲ��ǷǷ��ַ�!
	{
		OLED_ShowChar(x,y,*chr,size1);
		x+=size1/2;
		if(x>128-size1)  //����
		{
			x=0;
			y+=2;
    }
		chr++;
  }
}
////��ʾ2������
////x,y :�������	 
////len :���ֵ�λ��
////size:�����С
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
void OLED_Init(void)//OLED�ĳ�ʼ��
{
	//delay_ms(500);
	GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��A�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //��ʼ��GPIOG12
 	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //��ʼ��GPIOG12
 	GPIO_SetBits(GPIOB,GPIO_Pin_13);
	
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel//�ر�oled���
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address//���õ��е�ַ
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address//���ø��е�ַ
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)������ʼ�ߵ�ַ ����ӳ�� RAM ��ʾ��ʼ��
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register ���öԱȶȿ��ƼĴ���
	OLED_WR_Byte(0xCF,OLED_CMD);// Set SEG Output Current Brightness ���� SEG �����������
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1���� ���� SEG/��ӳ��
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0���·��� 0xc8���� ���� COM/��ɨ�跽��
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display ����������ʾ
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64) ���ö�·���ñȣ�1 �� 64��
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F) ������ʾƫ��ӳ�� RAM ������
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset ��ƫ��
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency ������ʾʱ�ӷָ��/����Ƶ��
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec ���ó��ָ�ȣ���ʱ������Ϊ 100 ֡/��
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period ����Ԥ�����
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock ��Ԥ�������Ϊ 15 ʱ�� + �ŵ�����Ϊ 1 ʱ��
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration ���� com ����Ӳ������
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh ���� vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level ���� VCOM ȡ��ѡ�񼶱�
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02) ����ҳ��Ѱַģʽ ��0x00/0x01/0x02��
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable ���ó�������/����
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable ���ã�0x10������
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5) ����������ʾ�� ��0xa4/0xa5��
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7)  ���÷�����ʾ�� ��0xa6/a7��
	OLED_WR_Byte(0xAF,OLED_CMD);
	OLED_Clear();
	
}	


