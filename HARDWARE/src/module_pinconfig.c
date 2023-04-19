#include "module_pinconfig.h"

/****************************
�������ܣ��������ų�ʼ��
Ӳ�����ӣ�5V_EN	  -> 	PF7
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
�������ܣ���س�����оƬ���ų�ʼ��
Ӳ�����ӣ�CHRG  ->	PA7
***************************************/
void CN3762_Init(void)
{
	GPIO_InitType GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pull = GPIO_Pull_NOPULL;
	GPIO_InitStructure.GPIO_Pins = CN3762_CHRG_PIN;
	GPIO_Init(CN3762_CHRG_PORT,&GPIO_InitStructure);
	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStructure.GPIO_OutType = GPIO_OutType_PP;		//ͨ���������
//    GPIO_InitStructure.GPIO_Pins = CHRG_EN_PIN;
//    GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
//    GPIO_Init(CHRG_EN_PORT, &GPIO_InitStructure);
	
//	CHRG_EN_ON();
}

/*************************************************
�������ܣ�����Ԫ��A04E���ų�ʼ��
�������ϼ�������˿ӡʱ,����Ԫ����ͨ(����͵�ƽ);
�������ϼ��뿪��,����Ԫ���ر�(����ߵ�ƽ)
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
�������ܣ��̵������ų�ʼ��
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
�������ܣ��������������ų�ʼ��
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
�������ܣ�Ӳ����ʼ��
˵	  ������ʼ������豸
***************************/
void HardWare_Init(void)
{    
		LED_GPIO_INIT();  				//ָʾ�� 
		MotorGpioInit();			//���    
		CN3762_Init();				//���оƬ
		A04E_Init();				//����������
		AC_PIN_Init();				//�Ƿ���
		HDF4_Init();				//�̵���
		PowerPin_Init();
}
