#include "onewire.h"
#include "ds18b20.h"


//��ʼ�¶�ת��
void DS18B20_Start(void)// ds1820 start convert
{   						               
    Onewire_Rst();	   
	Onewire_Check();	 
    Onewire_Write_Byte(0xcc);// skip rom
    Onewire_Write_Byte(0x44);// convert
}
u8 DS18B20_Init(void)
{
	Onewire_Init();
	Onewire_Rst();
	return Onewire_Check();
}
//��ds18b20�õ��¶�ֵ
//���ȣ�0.1C
//����ֵ���¶�ֵ ��-550~1250�� 
short DS18B20_Get_Temp(void)
{
    u8 temp;
    u8 TL,TH;
	short tem;
    DS18B20_Start ();                    // ds1820 start convert
    Onewire_Rst();
    Onewire_Check();	 
    Onewire_Write_Byte(0xcc);// skip rom
    Onewire_Write_Byte(0xbe);// convert	    
    TL=Onewire_Read_Byte(); // LSB   
    TH=Onewire_Read_Byte(); // MSB  
	
    if(TH>7)
    {
        TH=~TH;
        TL=~TL; 
        temp=0;//�¶�Ϊ��  
    }else temp=1;//�¶�Ϊ��	  	  
    tem=TH; //��ø߰�λ
    tem<<=8;    
    tem+=TL;//��õװ�λ
    tem=(float)tem*0.625;//ת��     
	if(temp)return tem; //�����¶�ֵ
	else return -tem;    
} 

