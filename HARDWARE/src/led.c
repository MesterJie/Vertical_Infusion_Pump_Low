#include "led.h"

void LED_GPIO_INIT(void)
{
    GPIO_InitType GPIO_InitStructure;			//定义结构体类型变量
    
    RCC_AHBPeriphClockCmd(RCC_AHBPERIPH_GPIOB, ENABLE);
    
	GPIO_InitStructure.GPIO_Pins = SYS_LED_PIN;
	GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OutType = GPIO_OutType_PP;
	GPIO_InitStructure.GPIO_Pull = GPIO_Pull_NOPULL;
	GPIO_Init(SYS_LED_PORT,&GPIO_InitStructure); 
 
	GPIO_InitStructure.GPIO_Pins = AC_LED_PIN;
	GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OutType = GPIO_OutType_PP;
	GPIO_InitStructure.GPIO_Pull = GPIO_Pull_NOPULL;
	GPIO_Init(AC_LED_PORT,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pins = BAT_LED_PIN;
	GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OutType = GPIO_OutType_PP;
	GPIO_InitStructure.GPIO_Pull = GPIO_Pull_NOPULL;
	GPIO_Init(BAT_LED_PORT,&GPIO_InitStructure);
    
	BAT_LED_ON();
	AC_LED_ON();
	SYS_LED_ON();
}
void Sys_Led(void)
{
	static bool flag = false;
	static uint16_t cnt1=0,cnt2=0;
	if(flag)
	{
		flag = !flag;
		for(cnt1=0;cnt1<6000;cnt1++)
			for(cnt2=0;cnt2<600;cnt2++)
		SYS_LED_ON();
	}
	else
	{
		flag = !flag;
		for(cnt1=0;cnt1<6000;cnt1++)
			for(cnt2=0;cnt2<600;cnt2++)
		SYS_LED_OFF();
	}
}
