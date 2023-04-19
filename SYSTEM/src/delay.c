#include "delay.h"


#if SYSTEM_SUPPORT_OS
#include "FreeRTOS.h"					//FreeRTOSʹ��		  
#include "task.h" 

static u8  fac_us = 0;							//us��ʱ������
static u16 fac_ms = 0;							//ms��ʱ������,��ucos��,����ÿ�����ĵ�ms��

extern void xPortSysTickHandler(void);

void SysTick_Handler(void)
{	
    if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)//ϵͳ�Ѿ�����
    {
        xPortSysTickHandler();	
    }
}

void delay_init()
{
	u32 reload;
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);//ѡ���ⲿʱ��  HCL96Mhz
	fac_us=SystemCoreClock/1000000;				    //�����Ƿ�ʹ��OS,fac_us����Ҫʹ��
	reload=SystemCoreClock/1000000;				    //ÿ���ӵļ������� ��λΪM  
	reload*=1000000/configTICK_RATE_HZ;			    //����configTICK_RATE_HZ�趨���ʱ��
                                                    //reloadΪ24λ�Ĵ���,���ֵ:16777216,��72M��,Լ��0.233s����	
	fac_ms=1000/configTICK_RATE_HZ;				    //����OS������ʱ�����ٵ�λ	   

	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;   	    //����SYSTICK�ж�
	SysTick->LOAD=reload; 						    //ÿ1/configTICK_RATE_HZ���ж�һ��	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	    //����SYSTICK    
}	

void delay_ms(u32 nms)
{	
	if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED) //ϵͳ�Ѿ�����
	{		
		if(nms>=fac_ms)						                //��ʱ��ʱ�����OS������ʱ������ 
		{ 
   			vTaskDelay(nms/fac_ms);	 		                //FreeRTOS��ʱ
		}
		nms%=fac_ms;						                //OS�Ѿ��޷��ṩ��ôС����ʱ��,������ͨ��ʽ��ʱ    
	}
	delay_us((u32)(nms*1000));				                //��ͨ��ʽ��ʱ
}

void delay_us(u32 nus)
{		
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;				//LOAD��ֵ	    	 
	ticks=nus*fac_us; 						//��Ҫ�Ľ����� 
	told=SysTick->VAL;        				//�ս���ʱ�ļ�����ֵ
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;	//����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����.
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;			//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
		}  
	};										    
}  

#else
void delay_init()
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8
    fac_us = SystemCoreClock / 8000000;				//Ϊϵͳʱ�ӵ�1/8
    fac_ms = (u16)fac_us * 1000;					//��OS��,����ÿ��ms��Ҫ��systickʱ����
}

void delay_us(u32 nus)
{
    u32 temp;
    SysTick->LOAD = nus * fac_us; 					//ʱ�����
    SysTick->VAL = 0x00;        					//��ռ�����
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;	    //��ʼ����
    do
    {
        temp = SysTick->CTRL;
    }
    while((temp & 0x01) && !(temp & (1 << 16)));    //�ȴ�ʱ�䵽��
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	    //�رռ�����
    SysTick->VAL = 0X00;      					    //��ռ�����
}



void delay_ms(u16 nms)
{
    u32 temp;
    SysTick->LOAD = (u32)nms * fac_ms;				//ʱ�����(SysTick->LOADΪ24bit)
    SysTick->VAL = 0x00;							//��ռ�����
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;	//��ʼ����
    do
    {
        temp = SysTick->CTRL;
    }
    while((temp & 0x01) && !(temp & (1 << 16)));		//�ȴ�ʱ�䵽��
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
    SysTick->VAL = 0X00;       					//��ռ�����
}

#endif
