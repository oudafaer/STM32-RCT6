#include "pwm.h"

void TIM1_PWM_Init(u16 arr,u16 psc)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); 		 //����RCC�ڲ�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);        //����APB2�ڲ�ʱ��

	
	GPIO_InitTypeDef GPIO_InitStructure;                         //����ṹ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;              //����Ϊ�����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	                  //GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;             //����ٶ�
	GPIO_Init(GPIOA, &GPIO_InitStructure);                        //��ʼ��GPIOA��PIN_7
	
	TIM_InternalClockConfig(TIM5);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;            	 //����ʱ����Ԫ�����ṹ��
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;                       //����Ԥ��Ƶ����ֵ��PSC����ȡֵ��Χ��0��65535��
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;         //ѡ�����ģʽΪ���ϼ���
	TIM_TimeBaseInitStructure.TIM_Period=arr;                          //�����Զ���������ֵ ��ARR����ȡֵ��Χ��0��65535��
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;              //�����ظ���������ֵ����0Ϊ�ر�
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);              //��ʼ��ʱ����Ԫ
                                 	                            //��ʱƵ��=72M/��PSC+1��/(ARR+1),��72M����7200��Ƶ=10K��10KƵ���¼�10000����=1s
	
	
	TIM_OCInitTypeDef TIM_OCInitStructure;                         //�����ʼ���ȽϽṹ�嵥Ԫ
	TIM_OCStructInit(&TIM_OCInitStructure);                        //���ṹ���������ʼֵ�������ٶԽṹ�������������
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;                 //��������Ƚ�ģʽ
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;        //��������Ƚϼ��ԣ��߼���
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;     //�������ʹ��
	TIM_OCInitStructure.TIM_Pulse=0;                                  //���ã�CCR��
	TIM_OC3Init(TIM5,&TIM_OCInitStructure);                         //��ʼ������Ƚϵ�Ԫ	

	TIM_Cmd(TIM5, ENABLE);  //ʹ��TIM1                                        //��ʼ����ʱ��TIM3
}

/*PWMƵ��=CK_PSC/��PSC+1��/��ARR+1��
  PWMռ�ձ�=CCR/(ARR+1)
  PWM�ֱ���=1/��ARR+1��
*/
void PWM_SetCompare4(u16 Compare4)
{
	TIM_SetCompare3(TIM5, Compare4);
}
void Servo_SetAngle(float Angle)
{
	PWM_SetCompare4(Angle / 180 * 200 + 50);
}
