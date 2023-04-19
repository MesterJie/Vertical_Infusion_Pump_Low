#ifndef _DMA_H
#define _DMA_H

#include "sys.h"


void DMACHx_Init(DMA_Channel_Type* DMAy_Channelx,u32 cpar,u32 cmar,u16 cndtr);
void UARTx_DMACHx_Init(DMA_Channel_Type* DMAy_Channelx,u32 cpar,u32 cmar,u16 cndtr);

#endif

