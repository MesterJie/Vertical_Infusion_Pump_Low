/**
******************************************************************************
* @file    sys.h
* @author  AE Team
* @version V1.1.0
* @date    28/08/2019
* @brief   This file contains all the sys inc file for the library.
******************************************************************************
* @copy
*/


#ifndef __SYS_H
#define __SYS_H

#include "at32f4xx.h"
#include "stdbool.h"
#include "string.h"
#include "stdint.h"
#include "stdio.h"
#include "at32f4xx_gpio_ex.h"

#define SYSTEM_SUPPORT_OS		1    

/*********************************************************HARDER_LED***********************************************************/
#define SYS_LED_PORT			GPIOB
#define SYS_LED_PIN				GPIO_Pins_13

#define AC_LED_PORT             GPIOB
#define AC_LED_PIN              GPIO_Pins_5

#define BAT_LED_PORT            GPIOB
#define BAT_LED_PIN             GPIO_Pins_6


#define SYS_LED_ON()				GPIO_SetBits(SYS_LED_PORT, SYS_LED_PIN)			
#define SYS_LED_OFF()				GPIO_ResetBits(SYS_LED_PORT, SYS_LED_PIN)

#define AC_LED_ON()				    GPIO_SetBits(AC_LED_PORT, AC_LED_PIN)			
#define AC_LED_OFF()				GPIO_ResetBits(AC_LED_PORT, AC_LED_PIN)

#define BAT_LED_ON()				GPIO_SetBits(BAT_LED_PORT, BAT_LED_PIN)			
#define BAT_LED_OFF()				GPIO_ResetBits(BAT_LED_PORT, BAT_LED_PIN)

/*********************************************************HARDER_COMMUNITE***********************************************************/
#define UART1_BUF_LEN           256
#define DMA_BUFF_SIZE           120

#define HEAD1                   0x11
#define HEAD2                   0x12
#define HEAD3                   0x13
#define HEAD4                   0x14
#define HEAD5                   0x15
#define HEAD6                   0x16

#define PACK_SIZE1              10
#define PACK_SIZE2              10
#define PACK_SIZE3              10
#define PACK_SIZE4              10
#define PACK_SIZE5              10
#define PACK_SIZE6              10

typedef enum
{
	e_Uart_1 = 0,
	e_Uart_2,
	e_Uart_Invalid,
}UartType;

typedef enum
{
	e_Prot_Uart1 = 0,
	e_Prot_Uart2,
	e_Prot_Invalid,
}ProtocolType;

typedef struct
{
	bool			m_bTxBuffer0;	//如果不采用DMA发送,这部分代码可以忽略,下同
	bool			m_bTransferIdle;
	uint8_t 		m_ui8TxBuffer0[DMA_BUFF_SIZE];	
	uint8_t 		m_ui8TxBuffer1[DMA_BUFF_SIZE];
	uint8_t 		m_ui8TxBuffLen;
	
	bool			m_bBuffRenew;
	uint8_t			m_ui8RxBuffer[DMA_BUFF_SIZE];
	uint8_t			m_ui8RxBuffLen;
	uint8_t 		m_ui8RxBuffIndex;
	
	UartType		m_eUart;
}Protocol;
//用于串口的DMA数据传输过程的判断条件和参数
typedef struct
{
    uint16_t LastDmacnt;
    uint16_t NowDmacnt;
    uint16_t DmaBufIndex;
    uint16_t DealBufIndex;
    uint8_t  *pDmaBuf;
    uint8_t  *pTmpBuf;
    uint8_t  *pDealBuf;   
}UartDma_t;

extern Protocol tagProtocol[e_Prot_Invalid];
/*dma接收*/
extern uint8_t a_DmaBuf[UART1_BUF_LEN];
extern uint8_t a_TmpBuf[UART1_BUF_LEN];
extern uint8_t a_DealBuf[UART1_BUF_LEN];
extern UartDma_t s_UartDma;
extern uint8_t m_ui8UartDmaTxBuffer[e_Prot_Invalid][DMA_BUFF_SIZE];
extern uint8_t m_ui8UartDmaRxBuffer[e_Prot_Invalid][DMA_BUFF_SIZE];
extern Protocol tagProtocol[e_Prot_Invalid];
/*dma接收*/

/*********************************************************HARDER_MOUDLE_PINCONFIG***********************************************************/
#define EN_5V_PIN				GPIO_Pins_7
#define EN_12V_PIN				GPIO_Pins_15
#define F1C100_EN_PIN	        GPIO_Pins_3


#define EN_5V_PORT				GPIOF
#define EN_12V_PORT				GPIOA
#define EN_F1C100_PORT			GPIOB

 
#define G1_COUNT_PIN		    GPIO_Pins_8
#define G2_COUNT_PIN		    GPIO_Pins_9
#define G1G2_COUNT_PORT		    GPIOB


#define A04E_DOOR_PIN		    GPIO_Pins_7
#define A04E_DOOR_PORT		    GPIOA


#define CHRG_CON_PIN	        GPIO_Pins_13
#define CHRG_CON_PORT	        GPIOB


#define CN3762_CHRG_PIN			GPIO_Pins_7
#define CN3762_CHRG_PORT   		GPIOA


#define AC_DET_PIN	            GPIO_Pins_15
#define AC_DET_PORT	            GPIOA
 
 
#define EN_5V_ON()				GPIO_SetBits(EN_5V_PORT, EN_5V_PIN)			
#define EN_5V_OFF()				GPIO_ResetBits(EN_5V_PORT, EN_5V_PIN)		

#define EN_12V_ON() 			GPIO_SetBits(EN_12V_PORT, EN_12V_PIN)	
#define EN_12V_OFF()			GPIO_ResetBits(EN_12V_PORT, EN_12V_PIN)	
 
 
#define EN_F1C100_ON()			GPIO_SetBits(EN_F1C100_PORT, F1C100_EN_PIN)
#define EN_F1C100_OFF()			GPIO_ResetBits(EN_F1C100_PORT, F1C100_EN_PIN)
 	

#define CHRG_CON_ON()			GPIO_SetBits(CHRG_CON_PORT, CHRG_CON_PIN)
#define CHRG_CON_OFF()			GPIO_ResetBits(CHRG_CON_PORT, CHRG_CON_PIN)


#define AC_DET					GPIO_ReadInputDataBit(AC_DET_PORT, AC_DET_PIN)
#define DOOR					GPIO_ReadInputDataBit(A04E_DOOR_PORT, A04E_DOOR_PIN)
#define CN3762_CHRG				GPIO_ReadInputDataBit(CN3762_CHRG_PORT, CN3762_CHRG_PIN)
 

#define G1_COUNT				GPIO_ReadInputDataBit(G1G2_COUNT_PORT, G1_COUNT_PIN)	
#define G2_COUNT				GPIO_ReadInputDataBit(G1G2_COUNT_PORT, G2_COUNT_PIN)

/*********************************************************HARDER_MOTOR***********************************************************/
#define Timerperiod (SystemCoreClock/15000 - 1)
#define SpeedArrDividend     (48000*125)

#define MOTOR_EN_PORT GPIOF
#define MOTOR_EN_PIN GPIO_Pins_6

#define DIR_PORT GPIOA
#define DIR_PIN GPIO_Pins_12

#define MOTOR_STEP_PORT GPIOA
#define MOTOR_STEP_PIN GPIO_Pins_11

#define MOTOR_CUR_PORT GPIOB
#define MOTOR_CUR_PIN GPIO_Pins_4


//步进电机信号输入设定	
#define MOTOR_STEP_ON()			GPIO_SetBits(MOTOR_STEP_PORT, MOTOR_STEP_PIN)
#define MOTOR_STEP_OFF()		GPIO_ResetBits(MOTOR_STEP_PORT, MOTOR_STEP_PIN)
//电机方向设定
#define MOTOR_DIR_FORWARD()		GPIO_SetBits(DIR_PORT, DIR_PIN)
#define	MOTOR_DIR_BACKWARD()	GPIO_ResetBits(DIR_PORT, DIR_PIN)
//电机使能位设定
#define MOTOR_EN_ON()			GPIO_SetBits(MOTOR_EN_PORT, MOTOR_EN_PIN)
#define MOTOR_EN_OFF()			GPIO_ResetBits(MOTOR_EN_PORT, MOTOR_EN_PIN)


/*********************************************************SYSTEM_delay***********************************************************/
extern u32 SystemCoreClock;
/*********************************************************SYSTEM_usart***********************************************************/

/*********************************************************SYSTEM_dma***********************************************************/

/*********************************************************SYSTEM_adc***********************************************************/
#define PRESSURE_PIN				GPIO_Pins_4
#define AIR1_LINE_PIN				GPIO_Pins_0
#define AIR2_LINE_PIN				GPIO_Pins_1
#define V_BAT_PIN  					GPIO_Pins_6
#define VBAT_AIRLINE_PRESS_PORT		GPIOA
/*********************************************************SYSTEM_adc***********************************************************/
#define TIM1_IRQ  0
#define TIM3_IRQ  0
#define TIM6_IRQ  1
#define TIM14_IRQ  1




//以下为汇编函数
void WFI_SET(void);		//执行WFI指令
void INTX_DISABLE(void);//关闭所有中断
void INTX_ENABLE(void);	//开启所有中断
void MSR_MSP(u32 addr);	//设置堆栈地址

void soft_reset(void);	//软件复位

#endif


/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/*-------------------------(C) COPYRIGHT 2019 MindMotion ----------------------*/
