#include "24cxx.h"
#include "myiic.h"
#include "delay.h"

void AT24CXX_Init()
{
	IIC_Init();
}
//��AT24CXXָ����ַ����һ������
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����������
u8 AT24CXX_ReadOneByte(u16 ReadAddr)
{
	u8 temp;
	MYIIC_Start();
	MYIIC_Send_Byte(0XA0+((ReadAddr/256)<<1));
	MYIIC_Wait_Ack(); 
    MYIIC_Send_Byte(ReadAddr%256);   //���͵͵�ַ
	MYIIC_Wait_Ack();	    
	MYIIC_Start();  	 	   
	MYIIC_Send_Byte(0XA1);           //�������ģʽ			   
	MYIIC_Wait_Ack();	 
    temp=MYIIC_Read_Byte(0);		   
    MYIIC_Stop();//����һ��ֹͣ����	    
	return temp;	
	
}
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
{
	MYIIC_Start();
	MYIIC_Send_Byte(0XA0+((WriteAddr/256)<<1));
	MYIIC_Wait_Ack(); 
    MYIIC_Send_Byte(WriteAddr%256);   //���͵͵�ַ
	MYIIC_Wait_Ack();	    
	MYIIC_Send_Byte(DataToWrite);     //�����ֽ�							   
	MYIIC_Wait_Ack();  		    	   
    MYIIC_Stop();//����һ��ֹͣ���� 
	delay_ms(10);	
}
//��AT24CXX�����ָ����ַ��ʼд�볤��ΪLen������
//�ú�������д��16bit����32bit������.
//WriteAddr  :��ʼд��ĵ�ַ  
//DataToWrite:���������׵�ַ
//Len        :Ҫд�����ݵĳ���2,4
void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
{  
	u8 t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr,(DataToWrite>>(8*t))&0xff);
	}
}
//��AT24CXX�����ָ����ַ��ʼ��������ΪLen������
//�ú������ڶ���16bit����32bit������.
//ReadAddr   :��ʼ�����ĵ�ַ 
//����ֵ     :����
//Len        :Ҫ�������ݵĳ���2,4
u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len)
{
	u8 t;
	u32 temp;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1);
	}
	return temp;
}
//���AT24CXX�Ƿ�����
//��������24XX�����һ����ַ(255)���洢��־��.
//���������24Cϵ��,�����ַҪ�޸�
//����1:���ʧ��
//����0:���ɹ�
u8 AT24CXX_Check(void)
{
	u32 temp;
	temp=AT24CXX_ReadOneByte(255);
	if(temp==0x52)return 0;
	else
	{
		AT24CXX_WriteOneByte(255,0x52);
		temp=AT24CXX_ReadOneByte(255);
		if(temp==0x52)return 0;
	}
	return 1;
}
//��AT24CXX�����ָ����ַ��ʼ����ָ������������
//ReadAddr :��ʼ�����ĵ�ַ ��24c02Ϊ0~255
//pBuffer  :���������׵�ַ
//NumToRead:Ҫ�������ݵĸ���
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	while(NumToRead)
	{		
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);
		NumToRead--;
	}
}
//��AT24CXX�����ָ����ַ��ʼд��ָ������������
//WriteAddr :��ʼд��ĵ�ַ ��24c02Ϊ0~255
//pBuffer   :���������׵�ַ
//NumToWrite:Ҫд�����ݵĸ���
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}
