#include "wwdg.h"
#include "led.h"
#include "NVIC.h"


//保存WWDG计数器的设置值,默认为最大.
u8 WWDG_CNT=0x7f;

void WWDG_Init(u8 tr,u8 wr,u32 fprer)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);
	
	WWDG_SetPrescaler(fprer);    //设置预分频值
	
	WWDG_SetWindowValue(wr);   //设置窗口值
	
	WWDG_Enable(tr);       //）设置计数器初始值并使能看门狗
	
	WWDG_ClearFlag();
	
	NVIC_InitStart(2,3);//初始化窗口看门狗 NVIC
	
	WWDG_EnableIT();    //开启窗口看门狗中断
}

//重设置WWDG计数器的值
void WWDG_Set_Counter(u8 cnt)
{
    WWDG_Enable(cnt);	 
}

void WWDG_IRQHandler(void)
{
	
	WWDG_SetCounter(0x7F);	  //当禁掉此句后,窗口看门狗将产生复位
	
	WWDG_ClearFlag();	  //清除提前唤醒中断标志位
	
	LED1=!LED1;
	
	
}
