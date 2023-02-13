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
	GPIO_InitTypeDef GPIO_InitStructure;       //����һ��GPIO_InitTypeDef���͵Ľṹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);                                	  //����GPIO������ʱ��																   
	GPIO_InitStructure.GPIO_Pin = MOTO_Pin12 | MOTO_Pin13 | MOTO_Pin14 | MOTO_Pin15;  //ѡ��Ҫ���Ƶ�GPIO����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                              //��������ģʽΪͨ��������� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                             //������������Ϊ50MHz 
	GPIO_Init(GPIOB, &GPIO_InitStructure);                                    //���ÿ⺯������ʼ��GPIO	
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
