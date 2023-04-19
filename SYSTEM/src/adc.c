#include "adc.h"
			
void MYADC_Init(uint8_t ADC_Channel_x1,uint8_t ADC_Channel_x2,uint8_t ADC_Channel_x3,uint8_t ADC_Channel_x4)
{
	ADC_InitType  ADC_InitStructure;
	GPIO_InitType GPIO_InitStructure;
	
	RCC_ADCCLKConfig(RCC_APB2CLK_Div16);
	
	RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_ADC1, ENABLE);
	
	GPIO_InitStructure.GPIO_Pins  = AIR1_LINE_PIN|AIR2_LINE_PIN|V_BAT_PIN|PRESSURE_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_Init(VBAT_AIRLINE_PRESS_PORT, &GPIO_InitStructure);
	
 
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;		
    ADC_InitStructure.ADC_ContinuousMode =  ENABLE;		//	ENABLE
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ExternalTrig = ADC_ExternalTrig_None;
	ADC_InitStructure.ADC_NumOfChannel = 4;
	ADC_InitStructure.ADC_ScanMode = ENABLE;
	
    ADC_Init(ADC1, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_x1, 1, ADC_SampleTime_239_5);	//Air1_Line
	ADC_RegularChannelConfig(ADC1, ADC_Channel_x2, 2, ADC_SampleTime_239_5);	//Air2_Line
	ADC_RegularChannelConfig(ADC1, ADC_Channel_x3, 3, ADC_SampleTime_239_5);	//V_Bat
	ADC_RegularChannelConfig(ADC1, ADC_Channel_x4, 4, ADC_SampleTime_239_5);	//Pressure
	
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_TempSensor, 0, ADC_SampleTime_239_5);
//	ADC_TempSensorVrefintCtrl(ENABLE); //开启内部温度传感器
	
	ADC_Ctrl(ADC1, ENABLE);
	
	/* Enable ADC1 reset calibration register */   
	ADC_RstCalibration(ADC1);
	/* Check the end of ADC1 reset calibration register */
	while(ADC_GetResetCalibrationStatus(ADC1));

	/* Start ADC1 calibration */
	ADC_StartCalibration(ADC1);
	/* Check the end of ADC1 calibration */
	while(ADC_GetCalibrationStatus(ADC1)){}
    
    ADC_SoftwareStartConvCtrl(ADC1, ENABLE);
}

