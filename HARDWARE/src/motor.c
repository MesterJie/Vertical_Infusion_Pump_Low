#include "motor.h"

void MotorGpioInit(void)
{
	GPIO_InitType GPIO_InitStructure;			//定义结构体类型变量
  				
    TMR_TimerBaseInitType  TIM_TimeBaseInitStruct;
	
    TMR_OCInitType TIM_OCInitStruct;
    
	RCC_AHBPeriphClockCmd(RCC_AHBPERIPH_GPIOA|RCC_AHBPERIPH_GPIOB|RCC_AHBPERIPH_GPIOF, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_TMR3,ENABLE);
	
	GPIO_InitStructure.GPIO_Pins = MOTOR_EN_PIN;
	GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OutType = GPIO_OutType_PP;
	GPIO_InitStructure.GPIO_Pull = GPIO_Pull_NOPULL;
	GPIO_Init(MOTOR_EN_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pins = DIR_PIN;
	GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OutType = GPIO_OutType_PP;
	GPIO_InitStructure.GPIO_Pull = GPIO_Pull_NOPULL;
	GPIO_Init(DIR_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pins = MOTOR_STEP_PIN;
	GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OutType = GPIO_OutType_PP;
	GPIO_InitStructure.GPIO_Pull = GPIO_Pull_NOPULL;
	GPIO_Init(MOTOR_STEP_PORT,&GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pins = MOTOR_CUR_PIN;
	GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OutType = GPIO_OutType_PP;
	GPIO_InitStructure.GPIO_Pull = GPIO_Pull_NOPULL;
	GPIO_Init(MOTOR_CUR_PORT,&GPIO_InitStructure);	
 
	TIM_TimeBaseInitStruct.TMR_ClockDivision = TMR_CKD_DIV1;        //该定时器控制电流
	TIM_TimeBaseInitStruct.TMR_CounterMode =  TMR_CounterDIR_Up;
	TIM_TimeBaseInitStruct.TMR_DIV = 0;
	TIM_TimeBaseInitStruct.TMR_Period = Timerperiod;
	TIM_TimeBaseInitStruct.TMR_RepetitionCounter = 0;
	
    TMR_TimeBaseInit(TMR3, &TIM_TimeBaseInitStruct);
    
	TIM_OCInitStruct.TMR_OCMode = TMR_OCMode_PWM2;		//CNT < CCR 输出无效电平 
	TIM_OCInitStruct.TMR_OCPolarity = TMR_OCPolarity_Low;	//有效电平
	TIM_OCInitStruct.TMR_OutputState = TMR_OutputState_Enable;	
	TIM_OCInitStruct.TMR_Pulse = Timerperiod*45/100;		
	TIM_OCInitStruct.TMR_OCIdleState = TMR_OCIdleState_Set;
 
	TMR_OC1Init(TMR3, &TIM_OCInitStruct);
    TMR_Cmd(TMR3, ENABLE);

//    TIM1->CCR1 = 194*12;
//    MOTOR_STEP = 0;
//    MOTOR_DIR = 1;
//    MOTOR_EN = 0;
	  MOTOR_STEP_OFF();
//	  MOTOR_DIR_BACKWARD();
	  MOTOR_DIR_FORWARD();
	  MOTOR_EN_OFF();
//	  MOTOR_EN_ON();

	 EN_12V_OFF();
	 EN_5V_OFF();
}
