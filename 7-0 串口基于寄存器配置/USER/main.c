#include "stm32f10x.h"                  // Device header

void My_USART1_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);           //��������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);            //����GPIOAʱ��

	GPIO_InitTypeDef GPIO_InitStruct;                              //����ṹ��
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;                    //�����������
	GPIO_Init(GPIOA,&GPIO_InitStruct);                           //��ʼ��GPIOA9
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;             //��������
	GPIO_Init(GPIOA,&GPIO_InitStruct);	                        //��ʼ��GPIOA10
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;                //ָ���ж�ͨ����������ر�
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;     //�����ⲿ��ռ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;           //�����ⲿ�ж���Ӧ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;             //ָ���ж�ͨ��ʹ�ܻ���ʧ��
	NVIC_Init(&NVIC_InitStruct);                          //����ָ���Ĳ�����ʼ��VIC�Ĵ���	
	
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate=115200;                    //���ò�����
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;     //�����ֳ�
	USART_InitStruct.USART_StopBits=USART_StopBits_1;        //����ֹͣλ
	USART_InitStruct.USART_Parity=USART_Parity_No;          //��żУ������
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;        //����ģʽΪ����ʹ�ܣ�����ʹ��
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;   //Ӳ�������ùر�
	USART_Init(USART1,&USART_InitStruct);                     //��ʼ������
			
	USART_Cmd(USART1,ENABLE);                                 //����1ʹ��
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);              //���������ж�	
}

void USART1_IRQHandler(void)                	//����1�жϷ������
{
	uint16_t res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE))
	{
		res=USART_ReceiveData(USART1);
		USART_SendData(USART1,res);
	}
}

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�����ж����ȼ�����
	My_USART1_Init();
	while(1);
}
