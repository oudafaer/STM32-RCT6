#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "tftlcd.h"
#include "key.h"
#include <string.h>


int main()
{
	u8 key=0;
	u8 num=0;
	u8 lcd_id[12];			//���LCD ID�ַ���	
	delay_init();	    	 //��ʱ������ʼ��	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2	 
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
 	LCD_Init();
	KEY_Init();
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//��LCD ID��ӡ��lcd_id���顣	
	LCD_ShowString(30,110,200,16,16,lcd_id);		//��ʾLCD ID	      					 
	LCD_ShowString(30,130,200,16,16,"2022/4/27");
	  
	LED0=1;
	while(1)
	{
		key=KEY_Scan(0);
		if(key)
		{
			switch(key)
			{
				case KEY0_PRES :   num++; printf("%s\r\n","KEY0"); break;
				case KEY1_PRES :   num--;  printf("%s\r\n","KEY1"); break;
				case WKUP_PRES :   num=0; printf("%s\r\n","WKUP");  break;
			}
		}
		if(USART_RX_STA==1)//���յ�һ֡����
		{
			LCD_ShowString(30,150,200,16,16,"Receive Data:");		
			LCD_Fill(30,170,239,170+16,WHITE); 
			LED0=!LED0;
			LCD_ShowString(30,170,200,16,16,USART_RX_BUF);	
			//�м���ձ�־�ʹ�С���пռ䣬׼���´ν���
			USART_RX_STA=0;	
			USART_RX_STA=0;
			memset(USART_RX_BUF,0,USART_REC_LEN);//USART_REC_LEN��Ҫ��գ���װ�����ݣ������¾ɶ���һ��
			
			if(USART_ReceiveData(USART1) == 'A')
			{
				printf("%s\r\n","RES");
			}
		}
	}
}
