#ifndef __COMMUNITE_H
#define __COMMUNITE_H
#include "sys.h"
#include "usart.h"

void Send_ModuleData(u8 *buf,u8 cnt);
void PackWithCheckSum(unsigned char  *pack, int len);                               //串口最后一位数据处理，类似于校验和
unsigned char UnpackWithCheckSum(unsigned char *pack, int len);                     //串口最后一位数据处理，类似于校验和
uint16_t UartDma_GetLeftDataNum(UartType eUart);
uint8_t Protocol_Recv1(Protocol *TagPro,uint8_t *pui8Buffer,uint8_t ui8Len);
int8_t Host_GetFrameLength(uint8_t ui8Head);
void Protocol_HostCmdExec(uint8_t *pui8Frame, uint8_t ui8Len);
uint8_t CalcCheckSum(uint8_t *pcui8Packet,uint32_t ui32Len);
void Protocol_HostUnpack(Protocol *TagPro);
void Protocol_CheckRecv1(Protocol *TagPro);
void Get_UsartPack(Protocol *TagPro);

void Communite_Init(void);
#endif

