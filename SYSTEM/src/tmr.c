#include "tmr.h"

#if SYSTEM_SUPPORT_OS
#include "FreeRTOS.h"	//FreeRTOS使用		  
#include "task.h"
#endif



void TIMx_Init(TMR_Type* TIMx,u16 psc,u16 arr)
{
    TMR_TimerBaseInitType TIM_StructInit;
    NVIC_InitType NVIC_StructInit;

    if(TIMx == TMR1)
        RCC_APB1PeriphClockCmd(RCC_APB2PERIPH_TMR1, ENABLE);
    else if(TIMx == TMR3)
        RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_TMR3,ENABLE); 
    else if(TIMx == TMR6)
        RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_TMR6,ENABLE);
	else if(TIMx == TMR14)
		RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_TMR14,ENABLE);

    TIM_StructInit.TMR_Period = arr-1;                                  //ARR寄存器值
    TIM_StructInit.TMR_DIV = psc-1;                               		//预分频值
    TIM_StructInit.TMR_ClockDivision = TMR_CKD_DIV1;                    //采样分频值
    TIM_StructInit.TMR_CounterMode = TMR_CounterDIR_Up;                	//计数模式
    TMR_TimeBaseInit(TIMx, &TIM_StructInit);
    
	
	
#if  TIM1_IRQ   
    TMR_INTConfig(TIMx, TMR_INT_Overflow, ENABLE);
    NVIC_StructInit.NVIC_IRQChannel = ;
    NVIC_StructInit.NVIC_IRQChannelCmd = ENABLE;
    NVIC_StructInit.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_StructInit.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_StructInit);
#endif
   
	
#if  TIM3_IRQ
    TMR_INTConfig(TIMx, TMR_INT_Overflow, ENABLE);
    NVIC_StructInit.NVIC_IRQChannel = TMR3_GLOBAL_IRQn;
    NVIC_StructInit.NVIC_IRQChannelCmd = ENABLE;
    NVIC_StructInit.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_StructInit.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_StructInit);
#endif		

#if  TIM6_IRQ
    TMR_INTConfig(TIMx, TMR_INT_Overflow, ENABLE);
    NVIC_StructInit.NVIC_IRQChannel = TMR6_GLOBAL_IRQn;
    NVIC_StructInit.NVIC_IRQChannelCmd = ENABLE;
    NVIC_StructInit.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_StructInit.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_StructInit);
#endif

#if  TIM14_IRQ
    TMR_INTConfig(TIMx, TMR_INT_Overflow, ENABLE);
    NVIC_StructInit.NVIC_IRQChannel = TMR14_GLOBAL_IRQn;
    NVIC_StructInit.NVIC_IRQChannelCmd = ENABLE;
    NVIC_StructInit.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_StructInit.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_StructInit);
#endif


    TMR_Cmd(TIMx, DISABLE); 
}

