#include "stm32f10x.h"                  // Device header
#include "pwm.h"
#include "key.h"
#include "led.h"

uint8_t KeyNum;
uint8_t Angle;

int main(void)
{
	LED_Init();
	KEY_Init();
	TIM1_PWM_Init(2000-1,720-1);
	while (1)
	{
		KeyNum = KEY_Scan(0);
		if (KeyNum == 1)
		{
			Angle += 30;
			if (Angle > 180)
			{
				Angle = 0;
			}
			LED1=~LED1;
		}
		Servo_SetAngle(Angle);
	}
}
