#include "dma.h"


DMA_InitTypeDef DMA_InitStruct;
u16 DMA1_MEM_LEN;//保存DMA每次数据传送的长度 	    

//从存储器->外设模式/8位数据宽度/存储器增量模式
//DMA_CHx:DMA通道CHx
//cpar:外设地址
//cmar:存储器地址
//cndtr:数据传输量

void MYDMA_Config(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
{
 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA传输
	DMA1_MEM_LEN=cndtr;
    DMA_DeInit(DMA_CHx);   //将DMA的通道1寄存器重设为缺省值
	DMA_InitStruct.DMA_Mode=DMA_Mode_Normal;  //工作在正常缓存模式
	DMA_InitStruct.DMA_BufferSize= cndtr;  //DMA通道的DMA缓存的大小
	DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralDST;  //数据传输方向，从内存读取发送到外设
	DMA_InitStruct.DMA_M2M=DMA_M2M_Disable;  //DMA通道x没有设置为内存到内存传输
	DMA_InitStruct.DMA_MemoryBaseAddr=cmar;  //DMA内存基地址
	DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte; //数据宽度为8位
	DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;  //内存地址寄存器递增
	DMA_InitStruct.DMA_PeripheralBaseAddr=cpar;  //DMA外设ADC基地址
	DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;  //数据宽度为8位
	DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;  //外设地址寄存器不变
	DMA_InitStruct.DMA_Priority=DMA_Priority_Medium; //DMA通道 x拥有中优先级 
	
	DMA_Init(DMA_CHx,&DMA_InitStruct);
}
 
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx)
{
	DMA_Cmd(DMA1_Channel4,DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel4,DMA1_MEM_LEN);//DMA通道的DMA缓存的大小
	DMA_Cmd(DMA1_Channel4,ENABLE);
}
