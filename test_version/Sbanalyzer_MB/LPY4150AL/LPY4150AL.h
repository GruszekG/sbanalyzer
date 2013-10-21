/*
		LPY4150AL- MEMS motion sensor:
		dual-axis pitch and yaw ±1500/±6000 dps analog gyroscope
		Library for STM32F10*.
		
		This library is part of the "SkateboardAnalyzer" project.
		project	website: <http://sbanalyzer.pl/>
		organization: Synergia <http://synergia.pwr.wroc.pl/>
		year: 2013
		author: Grzegorz Gruszka
		e-mail: grzegorz.gruszka1990@gmail.com
*/

#ifndef _LPY4150AL_H
#define _LPY4150AL_H

#define LPY4150AL_ADC 						ADC1     //LPY4150AL ADC
#define LPY4150AL_ADC_Port					GPIOB     //LPY4150AL GPIO port for ADC
                                
#define LPY4150AL_GPIO_X_Axis   			GPIO_Pin_1    //ADC for X-axis
#define LPY4150AL_GPIO_Z_Axis  				GPIO_Pin_0    //ADC for Z-axis

#define LPY4150AL_ADC_Channel_X_Axis   		ADC_Channel_9    //ADC for X-axis
#define LPY4150AL_ADC_Channel_Z_Axis  		ADC_Channel_8    //ADC for Z-axis

#define LPY4150AL_PWR_Port 					GPIOB     //LPY4150AL GPIO port for ADC
#define LPY4150AL_PD_Pin					GPIO_Pin_5

typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;

union Two_Bytes
{
  struct {
    uint8_t lo;
    uint8_t hi;
  } as_bytes;
  uint16_t as_word;
};

/*------Fnctions-------------------------------*/
void LPY4150AL_Conf(void);
void LPY4150AL_Enable(void);
void LPY4150AL_Disable(void);
void LPY4150AL_GetRot(unsigned short int * X, unsigned short int * Z);
void LPY4150AL_GetRot_16_bits(uint8_t* vect, uint8_t* sum);

#endif
