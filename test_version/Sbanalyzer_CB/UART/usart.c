/* Includes ------------------------------------------------------------------*/
#include "usart.h"


/* USARTy and USARTz configuration -------------------------------------------*/
  /* USARTy and USARTz configured as follow:
        - BaudRate = 9600 baud
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled

  */


extern unsigned char buforTx[17];
extern bool odebranoDane;

void USART1_Config(void)
{
	USART_InitTypeDef USART_InitStructure;

	GPIO_InitTypeDef GPIO_InitStructure;

//	NVIC_InitTypeDef NVIC_InitStruct_USART1;

		/* Enable clocks */
//	RCC_APB2PeriphClockCmd(USART1_GPIO_CLK | RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO, ENABLE);

//	NVIC_InitStruct_USART1.NVIC_IRQChannel =  USART1_IRQn;
//	NVIC_InitStruct_USART1.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_InitStruct_USART1.NVIC_IRQChannelPreemptionPriority = 0xf0;
//	NVIC_InitStruct_USART1.NVIC_IRQChannelSubPriority = 0xf0;
//
//	NVIC_Init(&NVIC_InitStruct_USART1);


	

	/* Configure USART1 Tx as alternate function open-drain */
	GPIO_InitStructure.GPIO_Pin = USART1_TxPin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(USART1_GPIO, &GPIO_InitStructure);

	/* Configure USART1 RX as input floating */
	GPIO_InitStructure.GPIO_Pin = USART1_RxPin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART1_GPIO, &GPIO_InitStructure);

	//USART_InitStructure.USART_BaudRate = 9600;
//	USART_InitStructure.USART_BaudRate = 19200;
//	USART_InitStructure.USART_BaudRate = 256000;
	USART_InitStructure.USART_BaudRate = 921600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* W³¹czenie przerwania USART */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	/* Configure USART1 */
	USART_Init(USART1, &USART_InitStructure);



	/* Enable the USART1 */

	USART_Cmd(USART1, ENABLE);
}


void USART1_Send(uint8_t data)
{
  USART_SendData(USART1, data);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}
}

void USART1_SendText(uint8_t * text)
{
	while(*text)
	{
		uint8_t temp;
		temp = *text;
		
		USART1_Send(temp);
		text++;
	}
}

uint8_t USART1_RecieveData(void)
{
	uint8_t RxData=0;
	while(USART_GetFlagStatus(USART1, USART_IT_RXNE) == RESET);
    RxData = USART_ReceiveData(USART1);
	
	return RxData; 
}
