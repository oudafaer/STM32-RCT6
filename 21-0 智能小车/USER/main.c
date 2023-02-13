#include "motor.h"
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
#include <string.h>


int main(void)
{
	int key;
	u8 lcd_id[12];			//���LCD ID�ַ���	
	delay_init();	    	 //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2	 
	MOTOR_GPIO_Init();
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
 	LCD_Init();
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//��LCD ID��ӡ��lcd_id���顣	
	LCD_ShowString(30,110,200,16,16,lcd_id);		//��ʾLCD ID	      					 
	LCD_ShowString(30,130,200,16,16,"2022/4/27");	  
	LED0=1;
	while(1)
	{
		MOTOR_Display(KEY_Scan());
		key=KEY_Scan();
		LCD_ShowNum(30,150,key,1,16);
	}	
}
