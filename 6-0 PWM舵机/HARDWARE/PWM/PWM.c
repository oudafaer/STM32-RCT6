#include "pwm.h"

void TIM1_PWM_Init(u16 arr,u16 psc)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); 		 //开启RCC内部时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);        //开启APB2内部时钟

	
	GPIO_InitTypeDef GPIO_InitStructure;                         //定义结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;              //设置为复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	                  //GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;             //输出速度
	GPIO_Init(GPIOA, &GPIO_InitStructure);                        //初始化GPIOA，PIN_7
	
	TIM_InternalClockConfig(TIM5);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;            	 //定义时基单元参数结构体
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;                       //设置预分频器的值（PSC）（取值范围在0到65535）
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;         //选择计数模式为向上计数
	TIM_TimeBaseInitStructure.TIM_Period=arr;                          //设置自动重组器的值 （ARR）（取值范围在0到65535）
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;              //设置重复计数器的值，给0为关闭
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);              //初始化时基单元
                                 	                            //定时频率=72M/（PSC+1）/(ARR+1),对72M进行7200分频=10K，10K频率下记10000个数=1s
	
	
	TIM_OCInitTypeDef TIM_OCInitStructure;                         //定义初始化比较结构体单元
	TIM_OCStructInit(&TIM_OCInitStructure);                        //给结构体变量赋初始值，后面再对结构体参数进行配置
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;                 //设置输出比较模式
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;        //设置输出比较极性，高极性
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;     //设置输出使能
	TIM_OCInitStructure.TIM_Pulse=0;                                  //设置（CCR）
	TIM_OC3Init(TIM5,&TIM_OCInitStructure);                         //初始化输出比较单元	

	TIM_Cmd(TIM5, ENABLE);  //使能TIM1                                        //初始化定时器TIM3
}

/*PWM频率=CK_PSC/（PSC+1）/（ARR+1）
  PWM占空比=CCR/(ARR+1)
  PWM分辨率=1/（ARR+1）
*/
void PWM_SetCompare4(u16 Compare4)
{
	TIM_SetCompare3(TIM5, Compare4);
}
void Servo_SetAngle(float Angle)
{
	PWM_SetCompare4(Angle / 180 * 200 + 50);
}
