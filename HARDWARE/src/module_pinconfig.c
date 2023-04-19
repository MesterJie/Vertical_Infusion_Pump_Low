#include "module_pinconfig.h"

/****************************
函数功能：供电引脚初始化
硬件连接：5V_EN	  -> 	PF7
		  12V_EN  -> 	PA15
		  F1C100_EN ->	PB3
*****************************/
void PowerPin_Init(void)
{
	GPIO_InitType GPIO_InitStructure;			
 	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OutType = GPIO_OutType_PP;
	GPIO_InitStructure.GPIO_Pins = EN_5V_PIN;
	GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;  
	GPIO_Init(EN_5V_PORT,&GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OutType = GPIO_OutType_PP;
	GPIO_InitStructure.GPIO_Pins = EN_12V_PIN;
	GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;  
	GPIO_Init(EN_12V_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OutType = GPIO_OutType_PP;
	GPIO_InitStructure.GPIO_Pins = F1C100_EN_PIN;
	GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;  
	GPIO_Init(EN_F1C100_PORT,&GPIO_InitStructure);
	
//	EN_5V = 0;
//	EN_12V = 0;
//	EN_F1C100 = 0;
	EN_5V_OFF();
	EN_12V_OFF();
	EN_F1C100_OFF();
}



/**************************************
函数功能：电池充电管理芯片引脚初始化
硬件连接：CHRG  ->	PA7
***************************************/
void CN3762_Init(void)
{
	GPIO_InitType GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pull = GPIO_Pull_NOPULL;
	GPIO_InitStructure.GPIO_Pins = CN3762_CHRG_PIN;
	GPIO_Init(CN3762_CHRG_PORT,&GPIO_InitStructure);
	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStructure.GPIO_OutType = GPIO_OutType_PP;		//通用推挽输出
//    GPIO_InitStructure.GPIO_Pins = CHRG_EN_PIN;
//    GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
//    GPIO_Init(CHRG_EN_PORT, &GPIO_InitStructure);
	
//	CHRG_EN_ON();
}

/*************************************************
函数功能：霍尔元件A04E引脚初始化
当磁铁南极靠近有丝印时,霍尔元件导通(输出低电平);
当磁铁南极离开后,霍尔元件关闭(输出高电平)
**************************************************/
void A04E_Init(void)
{
	GPIO_InitType GPIO_InitStructure;
	
//	RCC_AHBPeriphClockCmd(RCC_AHBPERIPH_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pull = GPIO_Pull_NOPULL;
	GPIO_InitStructure.GPIO_Pins = A04E_DOOR_PIN;
	GPIO_Init(A04E_DOOR_PORT,&GPIO_InitStructure);
}

/********************************
函数功能：继电器引脚初始化
*********************************/
void HDF4_Init(void)
{
	GPIO_InitType GPIO_InitStructure;
 	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OutType = GPIO_OutType_PP;
	GPIO_InitStructure.GPIO_Pins = CHRG_CON_PIN;
	GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;  
	GPIO_Init(CHRG_CON_PORT,&GPIO_InitStructure);

//	CHRG_CON = 0;
	CHRG_CON_OFF();
}

/********************************
函数功能：交流电输入引脚初始化
*********************************/
void AC_PIN_Init(void)
{
	GPIO_InitType GPIO_InitStructure;
 	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pull = GPIO_Pull_NOPULL;
	GPIO_InitStructure.GPIO_Pins = AC_DET_PIN;
	GPIO_Init(AC_DET_PORT,&GPIO_InitStructure);
}

/**************************
函数功能：硬件初始化
说	  明：初始化外接设备
***************************/
void HardWare_Init(void)
{    
		LED_GPIO_INIT();  				//指示灯 
		MotorGpioInit();			//电机    
		CN3762_Init();				//充电芯片
		A04E_Init();				//霍尔传感器
		AC_PIN_Init();				//是否充电
		HDF4_Init();				//继电器
		PowerPin_Init();
}
