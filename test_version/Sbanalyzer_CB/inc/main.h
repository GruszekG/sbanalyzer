#ifndef _MAIN_H
#define _MAIN_H

#include "stm32f10x.h"

/*---------DEKLARACJE FUNKCJI------------------*/
bool Init_board(void);
void RCC_Conf(void);
void GPIO_Conf(void);
void NVIC_Setup(void);
void TIM2_Setup(void);
void TIM2_SingleShot(void);

unsigned long int SysTick_Config_Mod(unsigned long int SysTick_CLKSource, unsigned long int Ticks);

#endif
