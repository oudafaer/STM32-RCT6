#include "motor.h"


void CarGo(void)
{
	IN1_up;
	IN2_down;
	IN3_up;
	IN4_down;
}

void CarStop(void)
{
	IN1_up;
	IN2_up;
	IN3_up;
	IN4_up;
}

void CarBack(void)
{
	IN1_down;
	IN2_up;
	IN3_down;
	IN4_up;
}

void CarRight(void)
{
	IN1_up;
	IN2_down;
	IN3_down;
	IN4_up;
}


void CarLeft(void)
{
	IN1_down;
	IN2_up;
	IN3_up;
	IN4_down;
}


void MOTOR_GPIO_Init(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;       //定义一个GPIO_InitTypeDef类型的结构体
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);                                	  //开启GPIO的外设时钟																   
	GPIO_InitStructure.GPIO_Pin = MOTO_Pin12 | MOTO_Pin13 | MOTO_Pin14 | MOTO_Pin15;  //选择要控制的GPIO引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                              //设置引脚模式为通用推挽输出 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                             //设置引脚速率为50MHz 
	GPIO_Init(GPIOB, &GPIO_InitStructure);                                    //调用库函数，初始化GPIO	
}
void MOTOR_Display(u8 key)
{

	if(key)
	{
		switch(key)
		{
			case 1:CarGo();
                   break;
			case 2:CarStop();
                   break;
			case 3:CarBack();
                   break;
			case 4:CarRight();
                   break;
			case 5:CarRight();
                   break;
		}
    }
}
