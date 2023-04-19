#include "dma.h"



void DMACHx_Init(DMA_Channel_Type* DMAy_Channelx,u32 cpar,u32 cmar,u16 cndtr)
{
		DMA_InitType   DMA_InitStruct;
	
		RCC_AHBPeriphClockCmd(RCC_AHBPERIPH_DMA1,ENABLE);
		
		DMA_InitStruct.DMA_BufferSize = cndtr;							//�������ݴ�������
		DMA_InitStruct.DMA_Direction= DMA_DIR_PERIPHERALSRC;		  //���ݵĴ��䷽��(�����赽�洢��)
		DMA_InitStruct.DMA_MTOM = DMA_MEMTOMEM_DISABLE;					 //�رմӴ洢�����洢������
		DMA_InitStruct.DMA_MemoryBaseAddr = cmar;					//�洢������ַ	
		DMA_InitStruct.DMA_MemoryDataWidth = DMA_MEMORYDATAWIDTH_HALFWORD;	//�洢�����ݿ��
		DMA_InitStruct.DMA_MemoryInc = DMA_MEMORYINC_ENABLE;		//�洢����ַ����
		DMA_InitStruct.DMA_Mode = DMA_MODE_CIRCULAR;		//��ѭ��ģʽ(�����ݴ����������Ϊ0ʱ�����Զ��ָ�Ϊ��ֵ)
		
		DMA_InitStruct.DMA_PeripheralBaseAddr = cpar;		//�������ַ
		DMA_InitStruct.DMA_PeripheralDataWidth = DMA_PERIPHERALDATAWIDTH_HALFWORD;		//�������ݿ��
		DMA_InitStruct.DMA_PeripheralInc = DMA_PERIPHERALINC_DISABLE;		//�����ַ����
		DMA_InitStruct.DMA_Priority = DMA_PRIORITY_VERYHIGH;		//���ȼ�����
		DMA_Init(DMAy_Channelx,&DMA_InitStruct);
		DMA_ChannelEnable(DMAy_Channelx, ENABLE);	
}

void UARTx_DMACHx_Init(DMA_Channel_Type* DMAy_Channelx,u32 cpar,u32 cmar,u16 cndtr)
{
		DMA_InitType   DMA_InitStruct;
	
		RCC_AHBPeriphClockCmd(RCC_AHBPERIPH_DMA1,ENABLE);
		
		DMA_InitStruct.DMA_BufferSize = cndtr;							//�������ݴ�������
		DMA_InitStruct.DMA_Direction= DMA_DIR_PERIPHERALSRC;		  			//���ݵĴ��䷽��(�����赽�洢��)
		DMA_InitStruct.DMA_MTOM = DMA_MEMTOMEM_DISABLE;					 	//�رմӴ洢�����洢������
		DMA_InitStruct.DMA_MemoryBaseAddr = cmar;						//�洢������ַ	
		DMA_InitStruct.DMA_MemoryDataWidth = DMA_MEMORYDATAWIDTH_BYTE;	//�洢�����ݿ��
		DMA_InitStruct.DMA_MemoryInc = DMA_MEMORYINC_ENABLE;			//�洢����ַ����
		DMA_InitStruct.DMA_Mode = DMA_MODE_CIRCULAR;		               
		
		DMA_InitStruct.DMA_PeripheralBaseAddr = cpar;							//�������ַ
		DMA_InitStruct.DMA_PeripheralDataWidth = DMA_PERIPHERALDATAWIDTH_BYTE;	//�������ݿ��
		DMA_InitStruct.DMA_PeripheralInc = DMA_PERIPHERALINC_DISABLE;			//�����ַ������
		DMA_InitStruct.DMA_Priority = DMA_PRIORITY_VERYHIGH;					//���ȼ�����
		DMA_Init(DMAy_Channelx,&DMA_InitStruct);
		DMA_ChannelEnable(DMAy_Channelx, ENABLE);	

}
