#ifndef _MAIN_H
#define _MAIN_H

#include "stm32f10x.h"

/*---------DEKLARACJE FUNKCJI------------------*/
bool Init_board(void);

void RCC_Conf(void);
void NVIC_Conf(void);
void LED_Conf(void);
void TIM2_Conf(void);

void LED_OFF(void);
void LED_ON(void);
void LED_Change(void);

void RFM73_to_LIS3DH(void);
void LIS3DH_to_RFM73(void);

void TIM2_Enable(void);
void TIM2_Disable(void);

void TIM2_ChangePeriod(uint16_t _period);

unsigned long int SysTick_Config_Mod(unsigned long int SysTick_CLKSource, unsigned long int Ticks);

#endif
