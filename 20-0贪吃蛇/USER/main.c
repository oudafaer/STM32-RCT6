#include "stm32f10x.h"
#include "oled.h"
#include "delay.h"
#include "snake.h"
#include "led.h"
#include "timer.h"
#include "bmp.h"
#include "key.h"
#include "usart.h"

int  main()
{	
	
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为9600
	LED_Init();
	OLED_Init();
	TIM3_Int_Init(1999,7199);//500ms
	GUI_Init();//界面初始化
	OLED_ShowPicture(0,0,128,8,BMP2);//开头动画
	delay_ms(1863);
	while(1)
	{
	 Get_Command();
	 Show_Score();
	 GUI_Refresh(map);//刷新地图
	 if(GameOver())
	 {
	   OLED_Clear();
	   OLED_ShowPicture(0,0,128,8,BMP);
	 }
	}
}






