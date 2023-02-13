#include "dma.h"


DMA_InitTypeDef DMA_InitStruct;
u16 DMA1_MEM_LEN;//����DMAÿ�����ݴ��͵ĳ��� 	    

//�Ӵ洢��->����ģʽ/8λ���ݿ��/�洢������ģʽ
//DMA_CHx:DMAͨ��CHx
//cpar:�����ַ
//cmar:�洢����ַ
//cndtr:���ݴ�����

void MYDMA_Config(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
{
 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//ʹ��DMA����
	DMA1_MEM_LEN=cndtr;
    DMA_DeInit(DMA_CHx);   //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
	DMA_InitStruct.DMA_Mode=DMA_Mode_Normal;  //��������������ģʽ
	DMA_InitStruct.DMA_BufferSize= cndtr;  //DMAͨ����DMA����Ĵ�С
	DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralDST;  //���ݴ��䷽�򣬴��ڴ��ȡ���͵�����
	DMA_InitStruct.DMA_M2M=DMA_M2M_Disable;  //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_InitStruct.DMA_MemoryBaseAddr=cmar;  //DMA�ڴ����ַ
	DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte; //���ݿ��Ϊ8λ
	DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;  //�ڴ��ַ�Ĵ�������
	DMA_InitStruct.DMA_PeripheralBaseAddr=cpar;  //DMA����ADC����ַ
	DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;  //���ݿ��Ϊ8λ
	DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
	DMA_InitStruct.DMA_Priority=DMA_Priority_Medium; //DMAͨ�� xӵ�������ȼ� 
	
	DMA_Init(DMA_CHx,&DMA_InitStruct);
}
 
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx)
{
	DMA_Cmd(DMA1_Channel4,DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel4,DMA1_MEM_LEN);//DMAͨ����DMA����Ĵ�С
	DMA_Cmd(DMA1_Channel4,ENABLE);
}
