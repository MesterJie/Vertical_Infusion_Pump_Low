#ifndef __USART_H
#define __USART_H

#include "sys.h"


void UARTx_Init(USART_Type * UARTn,u32 baud);                                       
void UARTx_SendStr(USART_Type * USARTn,char *str);
void UARTx_SendData(USART_Type * USARTn,uint8_t *data,uint8_t cnt);


#endif


