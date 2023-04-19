#include "dma.h"



void DMACHx_Init(DMA_Channel_Type* DMAy_Channelx,u32 cpar,u32 cmar,u16 cndtr)
{
		DMA_InitType   DMA_InitStruct;
	
		RCC_AHBPeriphClockCmd(RCC_AHBPERIPH_DMA1,ENABLE);
		
		DMA_InitStruct.DMA_BufferSize = cndtr;							//设置数据传输数量
		DMA_InitStruct.DMA_Direction= DMA_DIR_PERIPHERALSRC;		  //数据的传输方向(从外设到存储器)
		DMA_InitStruct.DMA_MTOM = DMA_MEMTOMEM_DISABLE;					 //关闭从存储器到存储器传输
		DMA_InitStruct.DMA_MemoryBaseAddr = cmar;					//存储器基地址	
		DMA_InitStruct.DMA_MemoryDataWidth = DMA_MEMORYDATAWIDTH_HALFWORD;	//存储器数据宽度
		DMA_InitStruct.DMA_MemoryInc = DMA_MEMORYINC_ENABLE;		//存储器地址增加
		DMA_InitStruct.DMA_Mode = DMA_MODE_CIRCULAR;		//打开循环模式(当数据传输的数量变为0时，会自动恢复为初值)
		
		DMA_InitStruct.DMA_PeripheralBaseAddr = cpar;		//外设基地址
		DMA_InitStruct.DMA_PeripheralDataWidth = DMA_PERIPHERALDATAWIDTH_HALFWORD;		//外设数据宽度
		DMA_InitStruct.DMA_PeripheralInc = DMA_PERIPHERALINC_DISABLE;		//外设地址增加
		DMA_InitStruct.DMA_Priority = DMA_PRIORITY_VERYHIGH;		//优先级设置
		DMA_Init(DMAy_Channelx,&DMA_InitStruct);
		DMA_ChannelEnable(DMAy_Channelx, ENABLE);	
}

void UARTx_DMACHx_Init(DMA_Channel_Type* DMAy_Channelx,u32 cpar,u32 cmar,u16 cndtr)
{
		DMA_InitType   DMA_InitStruct;
	
		RCC_AHBPeriphClockCmd(RCC_AHBPERIPH_DMA1,ENABLE);
		
		DMA_InitStruct.DMA_BufferSize = cndtr;							//设置数据传输数量
		DMA_InitStruct.DMA_Direction= DMA_DIR_PERIPHERALSRC;		  			//数据的传输方向(从外设到存储器)
		DMA_InitStruct.DMA_MTOM = DMA_MEMTOMEM_DISABLE;					 	//关闭从存储器到存储器传输
		DMA_InitStruct.DMA_MemoryBaseAddr = cmar;						//存储器基地址	
		DMA_InitStruct.DMA_MemoryDataWidth = DMA_MEMORYDATAWIDTH_BYTE;	//存储器数据宽度
		DMA_InitStruct.DMA_MemoryInc = DMA_MEMORYINC_ENABLE;			//存储器地址增加
		DMA_InitStruct.DMA_Mode = DMA_MODE_CIRCULAR;		               
		
		DMA_InitStruct.DMA_PeripheralBaseAddr = cpar;							//外设基地址
		DMA_InitStruct.DMA_PeripheralDataWidth = DMA_PERIPHERALDATAWIDTH_BYTE;	//外设数据宽度
		DMA_InitStruct.DMA_PeripheralInc = DMA_PERIPHERALINC_DISABLE;			//外设地址不增加
		DMA_InitStruct.DMA_Priority = DMA_PRIORITY_VERYHIGH;					//优先级设置
		DMA_Init(DMAy_Channelx,&DMA_InitStruct);
		DMA_ChannelEnable(DMAy_Channelx, ENABLE);	

}
