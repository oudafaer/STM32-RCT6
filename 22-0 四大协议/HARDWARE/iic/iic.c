#include "stm32f10x.h"                  // Device header
#include "IIC.h"
#include "delay.h"

void IIC_Init(void)//OLED�ĳ�ʼ��
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
}

void delay(u32 t)//������ʱ
{
	while(t--);
}

void IIC_Start(void)//��ʼλ
{
	IIC_SDA_Set();
	IIC_SCL_Set();//SCL,SDA������Ϊ�ߵ�ƽ
	delay_us(1);
	IIC_SDA_Clr();//��������
	delay_us(1);
	IIC_SCL_Clr();//���ݿɱ�
}

void IIC_Stop(void)//ֹͣλ
{
	 IIC_SCL_Clr();
	 IIC_SDA_Clr();
	 delay_us(1);
	 IIC_SCL_Set();
	 IIC_SDA_Set();//�͵�ƽ���ߵ�ƽ
	 delay_us(1);
}

void IIC_WaitACK(void)//�ȴ�Ӧ��ÿд��һ���ֽڵ����ݶ�Ҫ�ȴ�Ӧ��
{
	 IIC_SCL_Clr();
	 IIC_SDA_Clr();//��Ϊ�͵�ƽ����ʱSDA���ݿɱ�
	 delay_us(1);
	 IIC_SCL_Set();//SCL����Ϊ�ߣ���ʱSDAд������
	 delay_us(1);//�ȴ�д�����
     IIC_SCL_Clr();//���ݴ�ʱ�ɱ�	
}

void Send_Byte(u8 dat)//����8λ����
{
	u8 i;
	for(i=0;i<8;i++)
	{
	    IIC_SCL_Clr();//����Ϊ�͵�ƽ����ʱ���ݿɱ�
		if(dat&0x80)//1λΪ�棬SDA�øߣ���д��1
		{
			IIC_SDA_Set();//д��1
		}
		else
		{
			IIC_SDA_Clr();//д��0
		}
        IIC_SCL_Set();//���ݱ�д��
		delay(1);
		IIC_SCL_Clr();//����Ϊ�͵�ƽ����ʱ���ݿɱ�
	    delay(1);
		dat<<=1;//��������һλ��������һλ���ݵ�д��
	}
}


//����һ���ֽ�
//��SSD1306д��һ���ֽڡ�
//mode:����/�����־ 0,��ʾ����;1,��ʾ����;
void IIC_WR_Byte(u8 dat,u8 mode)
{
	IIC_Start();//��ʼ
	Send_Byte(0x78);//�ӻ���ַ
	IIC_WaitACK();//�ȴ�Ӧ��
	if(mode) 
		Send_Byte(0x40);//��������
	else
		Send_Byte(0x00);//��������
	IIC_WaitACK();//�ȴ�Ӧ��
	Send_Byte(dat);
    IIC_WaitACK();//�ȴ�Ӧ��
	IIC_Stop();//�ر�
}
