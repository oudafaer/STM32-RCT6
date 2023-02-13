#ifndef __DS18B20_H
#define __DS18B20_H	 
#include "sys.h"
void DS18B20_Start(void);// ds1820 start convert
u8 DS18B20_Init(void);
short DS18B20_Get_Temp(void);	 				


#endif
