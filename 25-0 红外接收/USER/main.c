#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "IR.h"   

 int main(void)
 { 
	u8 key;
	u8 *str=0; 	
	delay_init();	    	 //��ʱ������ʼ?
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2	  
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
 	LCD_Init();
	IR_Init();			//������ճ�ʼ��	 
 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
	LCD_ShowString(60,70,200,16,16,"2022/5/10");

   	LCD_ShowString(60,90,200,16,16,"KEYVAL:");	
   	LCD_ShowString(60,11,200,16,16,"KEYCNT:");	
   	LCD_ShowString(60,130,200,16,16,"SYMBOL:");	  		 	  		    							  
	while(1)
	{
		key=IR_Scan();	
		if(key)
		{	 
			LCD_ShowNum(116,130,key,3,16);		//��ʾ��ֵ
			LCD_ShowNum(116,150,RmtCnt,3,16);	//��ʾ��������		  
			switch(key)
			{
				case 0:str="ERROR";break;			   
				case 162:str="POWER";break;	    
				case 98:str="UP";break;	    
				case 2:str="PLAY";break;		 
				case 226:str="ALIENTEK";break;		  
				case 194:str="RIGHT";break;	   
				case 34:str="LEFT";break;		  
				case 224:str="VOL-";break;		  
				case 168:str="DOWN";break;		   
				case 144:str="VOL+";break;		    
				case 104:str="1";break;		  
				case 152:str="2";break;	   
				case 176:str="3";break;	    
				case 48:str="4";break;		    
				case 24:str="5";break;		    
				case 122:str="6";break;		  
				case 16:str="7";break;			   					
				case 56:str="8";break;	 
				case 90:str="9";break;
				case 66:str="0";break;
				case 82:str="DELETE";break;		 
			}
			LCD_Fill(116,170,116+8*8,170+16,WHITE);	//���֮ǰ����ʾ
			LCD_ShowString(116,170,200,16,16,str);	//��ʾSYMBOL
		}
	}
}
