#include "delay.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//�����Ҫʹ��OS,����������ͷ�ļ�����.

#include "delay.h"
#include "FreeRTOS.h"					//FreeRTOSʹ��		  
#include "task.h"
static u8  fac_us=0;							//us��ʱ������			   
static u16 fac_ms=0;							//ms��ʱ������,��ucos��,����ÿ�����ĵ�ms��

extern void xPortSysTickHandler(void);

//systick �жϷ�����,ʹ�� OS ʱ�õ�
void SysTick_Handler(void)
{ 
 if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)//ϵͳ�Ѿ�����
 {
 xPortSysTickHandler();
 } 
}

//��ʼ���ӳٺ���
//SYSTICK ��ʱ�ӹ̶�Ϊ AHB ʱ�ӣ������������� SYSTICK ʱ��Ƶ��Ϊ AHB/8
//����Ϊ�˼��� FreeRTOS�����Խ� SYSTICK ��ʱ��Ƶ�ʸ�Ϊ AHB ��Ƶ�ʣ�
//SYSCLK:ϵͳʱ��Ƶ��
void delay_init()
{
	u32 reload;
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);//ѡ���ⲿʱ�� HCLK

	fac_us=SystemCoreClock/1000000; //�����Ƿ�ʹ�� OS,fac_us ����Ҫʹ��
	reload=SystemCoreClock/1000000; //ÿ���ӵļ������� ��λΪ M 
	reload*=1000000/configTICK_RATE_HZ; //���� configTICK_RATE_HZ �趨���
	//ʱ�� reload Ϊ 24 λ�Ĵ���,���ֵ:
	//16777216,�� 72M ��,Լ�� 0.233s ����
	fac_ms=1000/configTICK_RATE_HZ; //���� OS ������ʱ�����ٵ�λ 
	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk; //���� SYSTICK �ж�
	SysTick->LOAD=reload; //ÿ 1/configTICK_RATE_HZ ���ж�
	//һ��
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk; //���� SYSTICK 
}
//��ʱ nus
//nus:Ҫ��ʱ�� us ��.
//nus:0~204522252(���ֵ�� 2^32/fac_us@fac_us=168) 
void delay_us(u32 nus)
{
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD; //LOAD ��ֵ 
	ticks=nus*fac_us; //��Ҫ�Ľ�����
	told=SysTick->VAL; //�ս���ʱ�ļ�����ֵ
	while(1)
	{
	tnow=SysTick->VAL;
	if(tnow!=told)
	{
	//����ע��һ�� SYSTICK ��һ���ݼ��ļ������Ϳ�����. 
	if(tnow<told)tcnt+=told-tnow;
	else tcnt+=reload-tnow+told; 
	told=tnow;
	if(tcnt>=ticks)break; //ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
	} 
	}; 
}
//��ʱ nms,�������������
//nms:Ҫ��ʱ�� ms ��
//nms:0~65535
void delay_ms(u32 nms)
{
	if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)//ϵͳ�Ѿ�����
	{
		if(nms>=fac_ms) //��ʱ��ʱ����� OS ������ʱ������
		{ 
			vTaskDelay(nms/fac_ms); //FreeRTOS ��ʱ
		}
		nms%=fac_ms; //OS �Ѿ��޷��ṩ��ôС����ʱ��,
		//������ͨ��ʽ��ʱ 
	}
	delay_us((u32)(nms*1000)); //��ͨ��ʽ��ʱ
}
//��ʱ nms,���������������
//nms:Ҫ��ʱ�� ms ��
void delay_xms(u32 nms)
{
	u32 i;
	for(i=0;i<nms;i++) delay_us(1000);
}



