#include "stm32f10x.h"                  // Device header
#include "Beep.h"
#include "delay.h"

int main()
{
	Beep_Init();
	while(1)
	{
		Beep=0;
		delay_ms(5000);
	}
}
