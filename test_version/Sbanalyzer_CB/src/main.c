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

unsigned char buforRxRFM73[17];
unsigned char buforTxRFM73[17];

unsigned char bufRxIndex;
unsigned char bufTxIndex;
bool dataReceived;

//unsigned char tempBuf[]={0x2,96,0,64,0,0,5,0xef}; TX rfm test

/*---------------------------------------------*/
/*---------------MAIN--------------------------*/
/*---------------------------------------------*/
int main(void)
{
	//tests
//	unsigned char buf[20];
//	unsigned char len;
	/*------BOARD INITIALIZATION-------------*/
   	while(Init_board()!=TRUE);
	LED_2_ON();
	Delay(500);
	LED_2_OFF();
	Delay(500);


	//RFM73_SwitchToRxMode();

	dataReceived = FALSE;

	while (1)
	{
		unsigned char len;
		unsigned char buf[20];
		//testts
		//Delay(100);
		//Receive_Packet(buf, &len);
		//test
		if (dataReceived)
		{
			SPI_Command(FLUSH_RX);//flush Rx
			Receive_Packet(buf, &len);
			RFM73_SwitchToTxMode();
			
			dataReceived = FALSE;
			switch (buforRx[0])
			{
				case Measure_Cmd:
				{
					
					Delay(100);
					
					TIM2_SingleShot();
					SPI_Command(FLUSH_RX);//flush Rx
					Receive_Packet(buf, &len);
					
					if(Cmd_OK != startCommand())
						noAcceptedCmd();
					else 
					{
						Delay(50);
						RFM73_SwitchToRxMode();
					}
					//	Delay(50);
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
					{
						SPI_Command(FLUSH_RX);//flush Rx
						SPI_Command(FLUSH_TX);//flush Rx
						TIM2_SingleShot();
						Send_Packet(W_TX_PAYLOAD_NOACK_CMD, buforRx, ConfCmd_Length + 1);
						Delay(100);
						RFM73_SwitchToRxMode();
						flushTXbuffer();
						flushRXbuffer();
					}			
				}	break;
				case Hello_Cmd:
				{
						TIM2_SingleShot();
						Send_Packet(W_TX_PAYLOAD_NOACK_CMD, buforRx, 2);

						Delay(100);
						RFM73_SwitchToRxMode();
						flushTXbuffer();
						flushRXbuffer();
				}	break;
				default:
				{
					noAcceptedCmd();		
				}
			}
		//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);	
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
	TIM2_Setup();
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
	NVIC_InitTypeDef NVIC_InitStruct_TIM2,NVIC_InitStructure,NVIC_InitStruct_USART1 ;


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
	
	NVIC_InitStruct_TIM2.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct_TIM2.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct_TIM2.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct_TIM2.NVIC_IRQChannelSubPriority = 3;

	NVIC_Init(&NVIC_InitStruct_TIM2);								
	
}

void TIM2_Setup(void){

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 4000-1;           //0,5ms * 4000 = 4s
	TIM_TimeBaseInitStruct.TIM_Prescaler = 36000;				//72MHz / 36000 = 2kHz => T=0,5ms
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	//TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	TIM_SetCounter(TIM2, 0);
	//TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	//TIM_Cmd(TIM2, ENABLE);
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

void TIM2_SingleShot(void)
{
		TIM_SetCounter(TIM2, 0);
    TIM_Cmd(TIM2, ENABLE);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
}

void flushTXbuffer(void)
{
	unsigned int i = 0;
	for(i = 0; i <17; i++)
		buforTx[i] = 0;
}

void flushRXbuffer(void)
{
	unsigned int i = 0;
	for(i = 0; i <17; i++)
		buforRx[i] = 0;
}
