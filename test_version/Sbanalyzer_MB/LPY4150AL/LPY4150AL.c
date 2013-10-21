/*
		LPY4150AL- MEMS motion sensor:
		dual-axis pitch and yaw ±1500/±6000 dps analog gyroscope
		Library for STM32F10*.
		
		This library is part of the "SkateboardAnalyzer" project.
		organization: Synergia <http://synergia.pwr.wroc.pl/>
		year: 2013
		author: Grzegorz Gruszka
		e-mail: grzegorz.gruszka1990@gmail.com
*/

#include "LPY4150AL.h"

#include "stm32f10x_gpio.h"	  
#include "stm32f10x_adc.h"	 

//  ADC configuration
void LPY4150AL_Conf(void)
{
  	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = LPY4150AL_GPIO_X_Axis|LPY4150AL_GPIO_Z_Axis;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	
	GPIO_Init(LPY4150AL_ADC_Port, &GPIO_InitStruct );

	GPIO_InitStruct.GPIO_Pin = LPY4150AL_PD_Pin;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;

	GPIO_Init(LPY4150AL_PWR_Port, &GPIO_InitStruct );

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;                  
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;                       
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;               
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Left;            	
	ADC_InitStructure.ADC_NbrOfChannel = 2; 	                          
	ADC_Init(LPY4150AL_ADC, &ADC_InitStructure);                               

	ADC_RegularChannelConfig(LPY4150AL_ADC, LPY4150AL_ADC_Channel_X_Axis, 1, ADC_SampleTime_1Cycles5);
	ADC_RegularChannelConfig(LPY4150AL_ADC, LPY4150AL_ADC_Channel_X_Axis, 2, ADC_SampleTime_1Cycles5);
	                                    
	ADC_Cmd(LPY4150AL_ADC, ENABLE);						                                 

	ADC_ResetCalibration(LPY4150AL_ADC);	                                        
	while(ADC_GetResetCalibrationStatus(LPY4150AL_ADC));                       
	ADC_StartCalibration(LPY4150AL_ADC);                                        
	while(ADC_GetCalibrationStatus(LPY4150AL_ADC));                            
}

void LPY4150AL_Enable(void)
{
	GPIO_ResetBits(LPY4150AL_PWR_Port, LPY4150AL_PD_Pin);
}
void LPY4150AL_Disable(void)
{
	GPIO_SetBits(LPY4150AL_PWR_Port, LPY4150AL_PD_Pin);
}

void LPY4150AL_GetRot(unsigned short int * X, unsigned short int * Z)
{
	ADC_SoftwareStartConvCmd(LPY4150AL_ADC, ENABLE);
	while (!ADC_GetFlagStatus(LPY4150AL_ADC,ADC_FLAG_EOC));
	*Z = ADC_GetConversionValue(LPY4150AL_ADC);
	
	ADC_SoftwareStartConvCmd(LPY4150AL_ADC, ENABLE);
	while (!ADC_GetFlagStatus(LPY4150AL_ADC,ADC_FLAG_EOC));
	*X = ADC_GetConversionValue(LPY4150AL_ADC); 	
}

void LPY4150AL_GetRot_16_bits(uint8_t* vect, uint8_t* sum)
{
	union Two_Bytes temp;	

	ADC_SoftwareStartConvCmd(LPY4150AL_ADC, ENABLE);
	while (!ADC_GetFlagStatus(LPY4150AL_ADC,ADC_FLAG_EOC));
	temp.as_word = ADC_GetConversionValue(LPY4150AL_ADC);
	vect[0] = temp.as_bytes.lo;
	vect[1] = temp.as_bytes.hi;
	*sum += temp.as_bytes.lo;
	*sum += temp.as_bytes.hi;
	
	ADC_SoftwareStartConvCmd(LPY4150AL_ADC, ENABLE);
	while (!ADC_GetFlagStatus(LPY4150AL_ADC,ADC_FLAG_EOC));
	temp.as_word = ADC_GetConversionValue(LPY4150AL_ADC);
	vect[2] = temp.as_bytes.lo;
	vect[3] = temp.as_bytes.hi;
	*sum += temp.as_bytes.lo;
	*sum += temp.as_bytes.hi;	 	
}
