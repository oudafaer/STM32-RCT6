#include "wkup.h"
#include "delay.h"
#include "sys.h"
#include "wkup.h"
#include "exti.h"
#include "nvic.h"

void Sys_Standby(void)
{
	//��ΪҪ���õ�Դ���ƼĴ��������Ա�����ʹ�ܵ�Դʱ�ӡ�
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE); //ʹ�� PWR ����ʱ��
	
	//ʹ��ʱ��֮��������� PWR_CSR �� EWUP λ��ʹ�� WK_UP ���ڽ� CPU �Ӵ���ģʽ���ѡ�
	PWR_WakeUpPinCmd(ENABLE); //ʹ�ܻ��ѹܽŹ���
	
	/*ͨ�� PWR_CR ���� PDDS λ��ʹ�� CPU �������˯��ʱ�������ģʽ�����ִ�� WFI ָ�ʼ�������ģʽ�����ȴ� WK_UP�жϵĵ���*/
	PWR_EnterSTANDBYMode();	
}
//ϵͳ�������ģʽ
void Sys_Enter_Standby(void)
{
	RCC_APB2PeriphResetCmd(0X01FC,DISABLE); //��λ���� IO ��
	Sys_Standby();	
}
//��� WKUP �ŵ��ź�
//����ֵ 1:�������� 3s ����
// 0:����Ĵ���
u8 Check_WKUP(void)
{
	u8 t=0;	//��¼���µ�ʱ��
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

//PA0 WKUP ���ѳ�ʼ��
void WKUP_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);//ʹ�� GPIOA �͸��ù���ʱ��
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	//��ʼ��IO
	
	EXTI_InitStart();
	NVIC_InitStart(2,2);
	
	if(Check_WKUP()==0) Sys_Standby();    //���ǿ���,�������ģʽ  
}

void EXTI0_IRQHandler(void)
{ 		    		    				     		    
	EXTI_ClearITPendingBit(EXTI_Line0); // ���LINE10�ϵ��жϱ�־λ		  
	if(Check_WKUP())//�ػ�?
	{		  
		Sys_Enter_Standby();  
	}
} 
