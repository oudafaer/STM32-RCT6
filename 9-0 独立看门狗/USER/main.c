#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "IWDG.h"


 int main(void)
 {	
 
	delay_init();	    	 //��ʱ������ʼ��	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2 
	uart_init(9600);	 //���ڳ�ʼ��Ϊ9600
	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ� 
	KEY_Init();          //������ʼ��	 
	delay_ms(300);   	 //���˿��õ���
	IWDG_Init(4,625);    //���Ƶ��Ϊ64,����ֵΪ625,���ʱ��Ϊ1s	   
	LED0=0;				 //����LED0
	while(1)
	{
		if(KEY_Scan(0)==KEY1_PRES)IWDG_Feed();//���WK_UP����,��ι��
		delay_ms(10);
	};
}
