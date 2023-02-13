#include "pwm.h"
#include "led.h"

void TIM1_PWM_Init(u16 arr,u16 psc)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 		 //����RCC�ڲ�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);        //����APB2�ڲ�ʱ��

	
	GPIO_InitTypeDef GPIO_InitStructure;                         //����ṹ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;              //����Ϊ�����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	                  //GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;             //����ٶ�
	GPIO_Init(GPIOA, &GPIO_InitStructure);                        //��ʼ��GPIOA��PIN_7
	
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;            	 //����ʱ����Ԫ�����ṹ��
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;                       //����Ԥ��Ƶ����ֵ��PSC����ȡֵ��Χ��0��65535��
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;         //ѡ�����ģʽΪ���ϼ���
	TIM_TimeBaseInitStruct.TIM_Period=arr;                          //�����Զ���������ֵ ��ARR����ȡֵ��Χ��0��65535��
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;              //�����ظ���������ֵ����0Ϊ�ر�
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);              //��ʼ��ʱ����Ԫ
                                 	                            //��ʱƵ��=72M/��PSC+1��/(ARR+1),��72M����7200��Ƶ=10K��10KƵ���¼�10000����=1s
	
	
	TIM_OCInitTypeDef TIM_OCInitStruct;                         //�����ʼ���ȽϽṹ�嵥Ԫ
	TIM_OCStructInit(&TIM_OCInitStruct);                        //���ṹ���������ʼֵ�������ٶԽṹ�������������
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM2;                 //��������Ƚ�ģʽ
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;        //��������Ƚϼ��ԣ��߼���
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;     //�������ʹ��
	TIM_OCInitStruct.TIM_Pulse=0;                                  //���ã�CCR��
	TIM_OC1Init(TIM1,&TIM_OCInitStruct);                         //��ʼ������Ƚϵ�Ԫ
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE �����ʹ��	
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	 	
	TIM_ARRPreloadConfig(TIM1, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���

	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1                                        //��ʼ����ʱ��TIM3
}

/*PWMƵ��=CK_PSC/��PSC+1��/��ARR+1��
  PWMռ�ձ�=CCR/(ARR+1)
  PWM�ֱ���=1/��ARR+1��
*/
