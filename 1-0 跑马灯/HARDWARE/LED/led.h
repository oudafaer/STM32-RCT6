#ifndef __LED_H
#define __LED_H	 
#include "SYS.h"
//LED驱动代码	   
									  
#define LED0 PAout(8)	// PA8
#define LED1 PDout(2)	// PD2	

#define LED2 PAout(2)	// PA8
#define LED3 PAout(3)	// PA8
#define LED4 PAout(4)	// PA8
#define LED5 PAout(5)	// PA8


void LED_Init(void);//初始化

		 				    
#endif
