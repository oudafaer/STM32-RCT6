#include "pwm.h"
#include "led.h"

void TIM1_PWM_Init(u16 arr,u16 psc)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 		 //开启RCC内部时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);        //开启APB2内部时钟

	
	GPIO_InitTypeDef GPIO_InitStructure;                         //定义结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;              //设置为复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	                  //GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;             //输出速度
	GPIO_Init(GPIOA, &GPIO_InitStructure);                        //初始化GPIOA，PIN_7
	
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;            	 //定义时基单元参数结构体
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;                       //设置预分频器的值（PSC）（取值范围在0到65535）
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;         //选择计数模式为向上计数
	TIM_TimeBaseInitStruct.TIM_Period=arr;                          //设置自动重组器的值 （ARR）（取值范围在0到65535）
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;              //设置重复计数器的值，给0为关闭
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);              //初始化时基单元
                                 	                            //定时频率=72M/（PSC+1）/(ARR+1),对72M进行7200分频=10K，10K频率下记10000个数=1s
	
	
	TIM_OCInitTypeDef TIM_OCInitStruct;                         //定义初始化比较结构体单元
	TIM_OCStructInit(&TIM_OCInitStruct);                        //给结构体变量赋初始值，后面再对结构体参数进行配置
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM2;                 //设置输出比较模式
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;        //设置输出比较极性，高极性
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;     //设置输出使能
	TIM_OCInitStruct.TIM_Pulse=0;                                  //设置（CCR）
	TIM_OC1Init(TIM1,&TIM_OCInitStruct);                         //初始化输出比较单元
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE 主输出使能	
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1预装载使能	 	
	TIM_ARRPreloadConfig(TIM1, ENABLE); //使能TIMx在ARR上的预装载寄存器

	TIM_Cmd(TIM1, ENABLE);  //使能TIM1                                        //初始化定时器TIM3
}

/*PWM频率=CK_PSC/（PSC+1）/（ARR+1）
  PWM占空比=CCR/(ARR+1)
  PWM分辨率=1/（ARR+1）
*/
