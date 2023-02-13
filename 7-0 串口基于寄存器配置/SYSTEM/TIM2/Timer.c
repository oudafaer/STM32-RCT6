#include "stm32f10x.h"                  // Device header
#include "NVIC.h"

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 		 //开启RCC内部时钟
	
	TIM_InternalClockConfig(TIM2);  							 //选择内部时钟TIM2驱动时基单元
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_Prescaler=7200-1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=10000-1;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);                                                  //时基单元初始化
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);                          //更新中断标志位
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	NVIC_InitStart();
	TIM_Cmd(TIM2,ENABLE);                                        //初始化定时器TIM2
}
