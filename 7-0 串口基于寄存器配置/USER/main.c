#include "stm32f10x.h"                  // Device header

void My_USART1_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);           //开启串口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);            //开启GPIOA时钟

	GPIO_InitTypeDef GPIO_InitStruct;                              //定义结构体
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;                    //复用推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStruct);                           //初始化GPIOA9
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;             //浮空输入
	GPIO_Init(GPIOA,&GPIO_InitStruct);	                        //初始化GPIOA10
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;                //指定中断通道来开启或关闭
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;     //设置外部抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;           //设置外部中断响应优先级
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;             //指定中断通道使能还是失能
	NVIC_Init(&NVIC_InitStruct);                          //根据指定的参数初始化VIC寄存器	
	
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate=115200;                    //设置波特率
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;     //设置字长
	USART_InitStruct.USART_StopBits=USART_StopBits_1;        //设置停止位
	USART_InitStruct.USART_Parity=USART_Parity_No;          //奇偶校验设置
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;        //设置模式为发送使能，接收使能
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;   //硬件流设置关闭
	USART_Init(USART1,&USART_InitStruct);                     //初始化串口
			
	USART_Cmd(USART1,ENABLE);                                 //串口1使能
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);              //开启接收中断	
}

void USART1_IRQHandler(void)                	//串口1中断服务程序
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //设置中断优先级分组
	My_USART1_Init();
	while(1);
}
