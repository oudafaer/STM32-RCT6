#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
#include "usart.h"

int main(void)
{	
	delay_init();	    	      //��ʱ������ʼ��	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 	
	OLED_Init();			       //��ʼ��OLED 
	OLED_Clear();
	OLED_Vertical();
	OLED_ShowString(20,2,"oudafa");                    //���Ժ���	
	while(1) 
	{
		
	}	  	
}
