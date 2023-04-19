#include "usart.h"

#if SYSTEM_SUPPORT_OS
#include "FreeRTOS.h"	//FreeRTOSʹ��		  
#include "task.h"
#endif

#pragma  import(__use_no_semihosting)


//��׼����Ҫ��֧�ֺ���
struct __FILE
{
    int handle;
};

FILE __stdout;
//����_sys_exit()�Ա���ʹ�ð�����ģʽ
void _sys_exit(int x)
{
    x = x;
}

//�ض���fputc����
int fputc(int ch, FILE *f)
{
    while((USART1->STS & 1<<6) == 0); //ѭ������,ֱ���������
    USART1->DT = (ch & (uint16_t)0x00FF);
    return ch;	  
}

void UARTx_Init(USART_Type * UARTn,u32 baud)
{
    //GPIO�˿�����
    GPIO_InitType GPIO_InitStructure;
    USART_InitType UART_InitStructure;

	
    if(UARTn == USART1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_USART1, ENABLE);		
                
        GPIO_InitStructure.GPIO_Pins = GPIO_Pins_10;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_Pull = GPIO_Pull_PU;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        GPIO_PinAFConfig(GPIOA, GPIO_PinsSource10, GPIO_AF_1); 
    
        GPIO_InitStructure.GPIO_Pins = GPIO_Pins_9; 
        GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_OutType = GPIO_OutType_PP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        GPIO_PinAFConfig(GPIOA, GPIO_PinsSource9, GPIO_AF_1);        
    }
    else if(UARTn == USART2)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_USART2,ENABLE);

		GPIO_InitStructure.GPIO_Pins = GPIO_Pins_3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_Pull = GPIO_Pull_PU;
        GPIO_Init(GPIOA,&GPIO_InitStructure);
        GPIO_PinAFConfig(GPIOA, GPIO_PinsSource3, GPIO_AF_1); 
		
		GPIO_InitStructure.GPIO_Pins = GPIO_Pins_2;
        GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_OutType = GPIO_OutType_PP;
        GPIO_Init(GPIOA,&GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOA, GPIO_PinsSource2, GPIO_AF_1);   
    }
	 
 
		
    //UART ��ʼ������
    UART_InitStructure.USART_BaudRate = baud;//���ڲ�����
    UART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    UART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    UART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    UART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    UART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Init(UARTn, &UART_InitStructure); 		//��ʼ������
    USART_Cmd(UARTn, ENABLE);                    //ʹ�ܴ���

#ifdef  UART1_IRQ	
    
    NVIC_InitStructure.NVIC_IRQChannel = UART1_IRQn;//ȷ���ô����жϵķ�ʽ��Ҫ�����ж����ò�����Ч
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1 ; 	 //��ռ���ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			 //�����ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				 //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);
#endif

#ifdef  UART2_IRQ

    NVIC_InitStructure.NVIC_IRQChannel = UART2_IRQn;//Ҫ��Ҫ��������жϵķ�ʽ����Ч���뽫���Ƕ������ж�����
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1 ; 	 //��ռ���ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			 //�����ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
    NVIC_Init(&NVIC_InitStructure);
#endif


}

void UARTx_SendStr(USART_Type * USARTn,char *str)
{
	while(*str!='\0')
	{
		USARTn->DT = *str++;
		while(!(USARTn->STS & 1<<6));
	}
}

void UARTx_SendData(USART_Type * USARTn,uint8_t *data,uint8_t cnt)
{	   
	for(uint8_t i = 0;i < cnt;i++)
	{
		USARTn->DT = *data++;
		while(!(USARTn->STS & 1<<6));
	}
}



