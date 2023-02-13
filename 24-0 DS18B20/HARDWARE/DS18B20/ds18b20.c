#include "onewire.h"
#include "ds18b20.h"


//开始温度转换
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
//从ds18b20得到温度值
//精度：0.1C
//返回值：温度值 （-550~1250） 
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
        temp=0;//温度为负  
    }else temp=1;//温度为正	  	  
    tem=TH; //获得高八位
    tem<<=8;    
    tem+=TL;//获得底八位
    tem=(float)tem*0.625;//转换     
	if(temp)return tem; //返回温度值
	else return -tem;    
} 

