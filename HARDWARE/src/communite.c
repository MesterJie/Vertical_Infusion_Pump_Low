#include "communite.h"

Protocol tagProtocol[e_Prot_Invalid];
/*dma接收*/
uint8_t a_DmaBuf[UART1_BUF_LEN] = {0};
uint8_t a_TmpBuf[UART1_BUF_LEN] = {0};
uint8_t a_DealBuf[UART1_BUF_LEN] = {0};
UartDma_t s_UartDma = {UART1_BUF_LEN,0,0,0,a_DmaBuf,a_TmpBuf,a_DealBuf};
uint8_t m_ui8UartDmaTxBuffer[e_Prot_Invalid][DMA_BUFF_SIZE];
uint8_t m_ui8UartDmaRxBuffer[e_Prot_Invalid][DMA_BUFF_SIZE];


/*************************
函数功能：发送模块数据
函数形参：buf 要发送的数据
		  cnt 数据长度
**************************/
void Send_ModuleData(u8 *buf,u8 cnt)
{
	PackWithCheckSum(buf,cnt);
	UARTx_SendData(USART1,buf,cnt);
}

void PackWithCheckSum(unsigned char  *pack, int len)
{
    unsigned char   byte;
    int    i;
    unsigned char   checkSum;

    if (2 > len)		
        return;

    checkSum = *(pack);

    if (2 < len)
    {
        byte = 0;
        for (i = len-2; i > 1; i --)
        {
            byte <<= 1;
            *(pack+i) = *(pack+i-1) | 0x80;
            checkSum += *(pack+i);
            byte |= (*(pack+i-1)&0x80) >> 7;
        }
        *(pack+1) = byte | 0x80;
        checkSum += *(pack+1);
    }
    *(pack+len-1) = checkSum | 0x80;
}

unsigned char UnpackWithCheckSum(unsigned char *pack, int len)
{
    unsigned char  byte;
    int    i;
    unsigned char  checkSum;

    if (2 > len)    
        return 0;

    checkSum  = *(pack);

    if(2 < len)
    {
        byte = *(pack+1);
        checkSum += byte;

        for (i = 1; i < len - 2; i ++)
        {
            checkSum += *(pack+i+1);
            *(pack+i) = (*(pack+i+1)&0x7f) | ( (byte&0x1)<<7 );
            byte >>= 1;
        }
    }

    if ((checkSum & 0x7f ) != ((*(pack+len-1)) &0x7f))
        return 0;

    return 1;
}



uint16_t UartDma_GetLeftDataNum(UartType eUart)
{
	uint16_t ui16LeftLen;
	
	switch(eUart)
	{
		case e_Uart_1:
			ui16LeftLen = DMA1_Channel3->TCNT;//传输数据个数
			break;
		case e_Uart_2:
			ui16LeftLen = DMA1_Channel5->TCNT;
			break;
		default:
			ui16LeftLen = 0;
			break;
	}
	
	return ui16LeftLen;
}


/*******************************************************
@函数功能：转移串口通过DMA传进来的数据到uint8_t *pui8Buffer数组中
@函数参数：Protocol *TagPro(DMA搬数据的数组)，uint8_t *pui8Buffer(目的数组)
@函数调用：函数Protocol_CheckRecv1
@函数返回值：ui8Len
********************************************************/
uint8_t Protocol_Recv1(Protocol *TagPro,uint8_t *pui8Buffer,uint8_t ui8Len)
{
	uint8_t ui8CurIndex = UartDma_GetLeftDataNum(TagPro->m_eUart);//DMA剩余传输个数    //128-28
	
	if(ui8CurIndex == TagPro->m_ui8RxBuffIndex) return 0;//DMA未传输数据，返回0
	uint8_t ui8Num = TagPro->m_ui8RxBuffIndex - ui8CurIndex;//两者之间是什么关系，怎么算的？	//包的数据个数
	
	if(TagPro->m_ui8RxBuffIndex < ui8CurIndex)//？
	{
		ui8Num = TagPro->m_ui8RxBuffIndex + DMA_BUFF_SIZE - ui8CurIndex;
	}
	
	if(ui8Len > ui8Num) ui8Len = ui8Num;//DMA传的新数据的长度？
	
	uint16_t ui16Index = DMA_BUFF_SIZE - TagPro->m_ui8RxBuffIndex;//Index代表什么？上次数据的位置？
	for(int i = 0; i < ui8Len; i++)
	{
		pui8Buffer[i] =  m_ui8UartDmaRxBuffer[TagPro->m_eUart][ui16Index];
		ui16Index++;
		if(ui16Index >= DMA_BUFF_SIZE) ui16Index = 0;
	}
	
	TagPro->m_ui8RxBuffIndex = DMA_BUFF_SIZE - ui16Index;//两个Index的区别？
	return ui8Len;
}
int8_t Host_GetFrameLength(uint8_t ui8Head) 
{
	int8_t i8Len;
	
	switch(ui8Head)
	{
		case HEAD1:			//
			i8Len = PACK_SIZE1;
			break;
		case HEAD2:			//
			i8Len = PACK_SIZE2;
			break;
		case HEAD3:			//
			i8Len = PACK_SIZE3;
			break;
		case HEAD4:			//
			i8Len = PACK_SIZE4;
			break;
		case HEAD5:
			i8Len = PACK_SIZE5;
			break;
		case HEAD6:
			i8Len = PACK_SIZE6;
			break;
		default:
			i8Len = 0;
			break;
	}
	
	return i8Len;

}

void Protocol_HostCmdExec(uint8_t *pui8Frame, uint8_t ui8Len)
{
	UnpackWithCheckSum(pui8Frame, ui8Len);
	
	switch(pui8Frame[0])
	{
		case HEAD1:			//
			
			break;
		case HEAD2:			//
			
			break;
		case HEAD3:			//
			
			break;
		case HEAD4:			//
			
			break;
		case HEAD5:
			
			break;
		case HEAD6:
			
			break;
		default:
			break;
    }
}

uint8_t CalcCheckSum(uint8_t *pcui8Packet,uint32_t ui32Len)
{
	uint8_t ui8ChkSum = 0;
	for (int i = 0;i < ui32Len;i++)
	{
		ui8ChkSum += pcui8Packet[i];
	}
	
	return (ui8ChkSum & 0x7F);
}

void Protocol_HostUnpack(Protocol *TagPro)
{
	bool bErr = false;
	uint8_t ui8CmdBody[20];
	
	for(int i = 0; i < TagPro->m_ui8RxBuffLen; i++)
	{
		if((TagPro->m_ui8RxBuffer[i] & 0x80) == 0x80) continue;
		
		int8_t i8FrameLen = Host_GetFrameLength(TagPro->m_ui8RxBuffer[i]);
		if(i8FrameLen == 0) continue;
		
		if(i + i8FrameLen > TagPro->m_ui8RxBuffLen) 
		{
			memmove(TagPro->m_ui8RxBuffer,TagPro->m_ui8RxBuffer + i,TagPro->m_ui8RxBuffLen - i);
			TagPro->m_ui8RxBuffLen -= i;
			return;
		}
		
		bErr = false;
		ui8CmdBody[0] = TagPro->m_ui8RxBuffer[i];
		for(int j = 1; j < i8FrameLen; j++)
		{
			ui8CmdBody[j] = TagPro->m_ui8RxBuffer[i + j];
			if((ui8CmdBody[j] & 0x80) == 0)
			{
				bErr = true;
				break;
			}
		
		}
		
		if(bErr) continue;
		
		if((ui8CmdBody[i8FrameLen - 1] & 0x7F) != CalcCheckSum(ui8CmdBody, i8FrameLen - 1))
		{
			continue;
		}		
		Protocol_HostCmdExec(ui8CmdBody, i8FrameLen);
		i += i8FrameLen - 1;
	}

	TagPro->m_ui8RxBuffLen = 0;
}

/*******************************************************
@函数功能：
@函数参数：
@函数调用：
@函数返回值：
********************************************************/
void Protocol_CheckRecv1(Protocol *TagPro)
{
	uint8_t ui8Buffer[96];
	
	uint8_t ui8Len = Protocol_Recv1(TagPro,ui8Buffer, 96);
	if(ui8Len == 0) return;
	
	 if(TagPro->m_ui8RxBuffLen + ui8Len >= DMA_BUFF_SIZE) 
	{
		TagPro->m_ui8RxBuffLen = 0;
		while(1);
	}
	
	memcpy(TagPro->m_ui8RxBuffer + TagPro->m_ui8RxBuffLen, ui8Buffer, ui8Len);//加上新的数据到TagPro->m_ui8RxBuffer中
	TagPro->m_ui8RxBuffLen += ui8Len;
	TagPro->m_bBuffRenew = true;

}


void Get_UsartPack(Protocol *TagPro)
{
	Protocol_CheckRecv1(TagPro);
	if(TagPro->m_bBuffRenew)
	{
		TagPro->m_bBuffRenew = false;
		
		Protocol_HostUnpack(TagPro);
	}
}

void Communite_Init(void)
{
	tagProtocol[0].m_eUart = e_Uart_1;
	tagProtocol[1].m_eUart = e_Uart_2;

	for(int i = 0; i < e_Prot_Invalid; i++)
	{
		tagProtocol[i].m_bTxBuffer0 = true;		 
		tagProtocol[i].m_ui8RxBuffLen = 0;
		tagProtocol[i].m_ui8TxBuffLen = 0;		
		tagProtocol[i].m_bBuffRenew = false;
		tagProtocol[i].m_bTransferIdle = true;
		tagProtocol[i].m_ui8RxBuffIndex = DMA_BUFF_SIZE;
		memset(tagProtocol[i].m_ui8RxBuffer,  0, DMA_BUFF_SIZE);
		memset(tagProtocol[i].m_ui8TxBuffer0, 0, DMA_BUFF_SIZE);
		memset(tagProtocol[i].m_ui8TxBuffer1, 0, DMA_BUFF_SIZE);
	}
	
}

