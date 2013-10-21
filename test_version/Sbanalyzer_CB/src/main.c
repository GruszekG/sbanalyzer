#include "main.h"

/*-------------includes--------------*/
#include "stm32f10x.h"
#include "usart.h"
#include "RFM73.h"
#include <stddef.h>
#include "commands.h"

/*--------global variables-----------*/
unsigned char buforRx[17];
unsigned char buforTx[17];
unsigned char bufRxIndex;
unsigned char bufTxIndex;
bool dataReceived;

/*---------------------------------------------*/
/*---------------MAIN--------------------------*/
/*---------------------------------------------*/
int main(void)
{
	/*------BOARD INITIALIZATION-------------*/
   	while(Init_board()!=TRUE);
	LED_2_ON();
	Delay(500);
	LED_2_OFF();
	Delay(500);

	RFM73_SwitchToRxMode();

	dataReceived = FALSE;

	while (1)
	{
		if (dataReceived)
		{
			RFM73_SwitchToTxMode();
			
			dataReceived = FALSE;
			switch (buforRx[0])
			{
				case Measure_Cmd:
				{
					Delay(100);
					if(Cmd_OK == startCommand())
						acceptedCmd();
					else
						noAcceptedCmd();

				}	break;
				case Info_Cmd:
				{
					if(Cmd_OK != infoCommand())
						noAcceptedCmd();
				}	break;
				case Conf_Cmd:
				{
					if(Cmd_OK != confCommand())
						noAcceptedCmd();
					else
						acceptedCmd();
							
				}	break;
				default:
				{
					noAcceptedCmd();		
				}
			}
			USART_ITConfig(USART1, USART_IT_TXE, ENABLE);	
		}	
	};
}

/*---------------------------------------------*/
/*---------------FUNCTIONS---------------------*/
/*---------------------------------------------*/

bool Init_board(void)
{
	RCC_Conf();
	NVIC_Setup();
	//TIM2_Setup();
	USART1_Config();
	RFM73_EXTI_Enable();
	SysTick_Config_Mod(SysTick_CLKSource_HCLK_Div8, 9000);

	RFM73_SPI_Conf();
	RFM73_LEDS_Conf();

	RFM73_PowerON();
	Delay(100);	
	if(RFM73_Initialize() == RFM73_ERROR)	return FALSE;

	return TRUE;
}

void RCC_Conf(void)
{

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(USART1_GPIO_CLK | RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}											  

void GPIO_Conf(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_Init( GPIOB, &GPIO_InitStruct );	
}

// NVIC configuration
void NVIC_Setup(void){
//
	NVIC_InitTypeDef /*NVIC_InitStruct_TIM2,*/NVIC_InitStructure,NVIC_InitStruct_USART1 ;


	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	/* Enable and set EXTI Interrupt to the lowest priority */
 	NVIC_InitStructure.NVIC_IRQChannel = RFM73_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStruct_USART1.NVIC_IRQChannel =  USART1_IRQn;
	NVIC_InitStruct_USART1.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct_USART1.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct_USART1.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct_USART1);
	
//	NVIC_InitStruct_TIM2.NVIC_IRQChannel = TIM2_IRQn;
//	NVIC_InitStruct_TIM2.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_InitStruct_TIM2.NVIC_IRQChannelPreemptionPriority = 1;
//	NVIC_InitStruct_TIM2.NVIC_IRQChannelSubPriority = 3;
//
//	NVIC_Init(&NVIC_InitStruct_TIM2);								
	
}

void TIM2_Setup(void){

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 300;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 36000;				//72MHz / 36000 = 2kHz => T=0,5ms
//	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
}

unsigned long int SysTick_Config_Mod(unsigned long int SysTick_CLKSource, unsigned long int Ticks)
{ 
	unsigned long int Settings;

	assert_param(IS_SYSTICK_CLK_SOURCE(SysTick_CLKSource));
 	if (Ticks > SysTick_LOAD_RELOAD_Msk)  return (1);            /* Reload value impossible */

	SysTick->LOAD = (Ticks & SysTick_LOAD_RELOAD_Msk) - 1;

	NVIC_SetPriority(SysTick_IRQn, 0);

	SysTick->VAL = 0;

	Settings = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;

	if(SysTick_CLKSource == SysTick_CLKSource_HCLK)
	{
		Settings |= SysTick_CLKSource_HCLK;
	}
	else
	{
		Settings &= SysTick_CLKSource_HCLK_Div8;
	}
  
	SysTick->CTRL = Settings;
                                                               
 	return (0);     
}
