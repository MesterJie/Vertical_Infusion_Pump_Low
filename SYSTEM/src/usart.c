#include "usart.h"

#if SYSTEM_SUPPORT_OS
#include "FreeRTOS.h"	//FreeRTOS使用		  
#include "task.h"
#endif

#pragma  import(__use_no_semihosting)


//标准库需要的支持函数
struct __FILE
{
    int handle;
};

FILE __stdout;
//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
    x = x;
}

//重定义fputc函数
int fputc(int ch, FILE *f)
{
    while((USART1->STS & 1<<6) == 0); //循环发送,直到发送完毕
    USART1->DT = (ch & (uint16_t)0x00FF);
    return ch;	  
}

void UARTx_Init(USART_Type * UARTn,u32 baud)
{
    //GPIO端口设置
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
	 
 
		
    //UART 初始化设置
    UART_InitStructure.USART_BaudRate = baud;//串口波特率
    UART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    UART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
    UART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
    UART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    UART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
    USART_Init(UARTn, &UART_InitStructure); 		//初始化串口
    USART_Cmd(UARTn, ENABLE);                    //使能串口

#ifdef  UART1_IRQ	
    
    NVIC_InitStructure.NVIC_IRQChannel = UART1_IRQn;//确定好触发中断的方式后要进行中断设置才能生效
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1 ; 	 //抢占优先级1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			 //子优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				 //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);
#endif

#ifdef  UART2_IRQ

    NVIC_InitStructure.NVIC_IRQChannel = UART2_IRQn;//要想要多个触发中断的方式都生效必须将他们都进行中断设置
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1 ; 	 //抢占优先级1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			 //子优先级1
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



