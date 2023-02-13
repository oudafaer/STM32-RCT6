#include "wkup.h"
#include "delay.h"
#include "sys.h"
#include "wkup.h"
#include "exti.h"
#include "nvic.h"

void Sys_Standby(void)
{
	//因为要配置电源控制寄存器，所以必须先使能电源时钟。
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE); //使能 PWR 外设时钟
	
	//使能时钟之后后再设置 PWR_CSR 的 EWUP 位，使能 WK_UP 用于将 CPU 从待机模式唤醒。
	PWR_WakeUpPinCmd(ENABLE); //使能唤醒管脚功能
	
	/*通过 PWR_CR 设置 PDDS 位，使得 CPU 进入深度睡眠时进入待机模式，最后执行 WFI 指令开始进入待机模式，并等待 WK_UP中断的到来*/
	PWR_EnterSTANDBYMode();	
}
//系统进入待机模式
void Sys_Enter_Standby(void)
{
	RCC_APB2PeriphResetCmd(0X01FC,DISABLE); //复位所有 IO 口
	Sys_Standby();	
}
//检测 WKUP 脚的信号
//返回值 1:连续按下 3s 以上
// 0:错误的触发
u8 Check_WKUP(void)
{
	u8 t=0;	//记录按下的时间
	while(1)
	{
		if(WKUP_KD)
		{
			t++;
			delay_ms(10);
			if(t>=200)
			{
				return 1;
			}
		}
		else
		{
			return 0;
		}
	}	
}

//PA0 WKUP 唤醒初始化
void WKUP_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);//使能 GPIOA 和复用功能时钟
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	//初始化IO
	
	EXTI_InitStart();
	NVIC_InitStart(2,2);
	
	if(Check_WKUP()==0) Sys_Standby();    //不是开机,进入待机模式  
}

void EXTI0_IRQHandler(void)
{ 		    		    				     		    
	EXTI_ClearITPendingBit(EXTI_Line0); // 清除LINE10上的中断标志位		  
	if(Check_WKUP())//关机?
	{		  
		Sys_Enter_Standby();  
	}
} 
