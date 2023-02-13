#ifndef __LED_H
#define __LED_H	 
#include "SYS.h"
//LED驱动代码	   
									  
#define LED0 PAout(8)	// PA8
#define LED1 PDout(2)	// PD2	

void LED_Init(void);//初始化

		 				    
#endif
