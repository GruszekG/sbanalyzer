#ifndef _USART_H
#define _USART_H

#include "stm32f10x.h"


#define USART1_TxPin GPIO_Pin_9
#define USART1_RxPin GPIO_Pin_10
#define USART1_GPIO_CLK RCC_APB2Periph_GPIOA
#define USART1_GPIO GPIOA



void USART1_Config(void);
void USART1_Send(uint8_t data);
void USART1_SendText(uint8_t * text);
void USART1_IRQHandler(void);
//uint8_t USART1_RecieveData(void);


#endif
