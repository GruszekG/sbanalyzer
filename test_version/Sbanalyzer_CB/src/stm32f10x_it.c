/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "usart.h"
#include "RFM73.h"
#include "commands.h"

extern unsigned char buforRx[17];
extern unsigned char buforTx[17];

extern unsigned char rfm_buforRx[17];
extern unsigned char rfm_buforTx[17];

extern unsigned char bufTxIndex;
extern unsigned char bufRxIndex;
extern bool dataReceived;
bool sendData = FALSE;

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */


uint16_t licznik;



void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	TimingDelay_Decrement();
}

//void TIM2_IRQHandler(void)
//{
//	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
////	if(GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_0)==SET)
////	{
////		GPIO_SetBits(GPIOB, GPIO_Pin_1);
////		GPIO_ResetBits(GPIOB, GPIO_Pin_0);
////	}
////	else 
////	{
////		GPIO_SetBits(GPIOB, GPIO_Pin_0);
////		GPIO_ResetBits(GPIOB, GPIO_Pin_1);
////	}
////	USART1_SendText("Siemka");

//}

void TIM2_IRQHandler(void)//debug timer
{
	if(TIM_GetITStatus(TIM2, TIM_FLAG_Update) != RESET)
	{
		TIM_ClearFlag(TIM2, TIM_FLAG_Update);
		TIM_Cmd(TIM2, DISABLE);  
    TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
		noAcceptedCmd();
		RFM73_SwitchToTxMode();
	}
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		buforRx[bufRxIndex] = USART_ReceiveData(USART1);    //Odczyt danej automatycznie kasuje flage przerwania           
		if(buforRx[bufRxIndex] == 0x0D)                     //Wykrycie znaku \CR
		{
			dataReceived = TRUE;
			while (bufRxIndex<17)
			{                           //wyzerowanie znakow do konca bufora  (zabezpiecza przed wyswietlaniem "smieci" na LCD)
				buforRx[bufRxIndex]=0;      
				bufRxIndex++;
			}
			bufRxIndex = 0;                
		 } 
		 else 
		 {                                            //Obsluga pozostalych, "zwyklych" znakow
		  	bufRxIndex++;
		  	if (bufRxIndex>16)
		  	{                               //Zabezpieczenie przed przepelnieniem bufora jesli odbierany tekst jest dluzszy niz 16 znakow
		    	bufRxIndex=0;
		  	}
		}
	}

//	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
//	{  
//		USART_SendData(USART1, buforTx[bufTxIndex++]);      //Wyslij kolejny znak i zwieksz indeks bufora wyjsciowego
//		if(buforTx[bufTxIndex-1] == 0x0D)                   //Jesli wysylany zostal ostatni znak (CR)
//		{
//			USART_ClearFlag(USART1, TIM_FLAG_Update);
//			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);    //Wylacz przerwanie = koniec transmisji
//			bufTxIndex = 0;                                 
//		}    
//	}
}

void EXTI3_IRQHandler(void)
{
	uint8_t len;
	uint8_t rx_buf[MAX_PACKET_LEN]; 
	uint8_t i, chksum; 
	if(EXTI_GetITStatus(RFM73_EXTI_Line) != RESET)
	{
		
		if(GPIO_ReadOutputDataBit(RFM73_SPI_GPIO, RFM73_IRQ) == RESET)
		{
			Receive_Packet(rx_buf, &len);
			if(len>0)
				switch (rx_buf[0])
				{
					case 'A'://received ACK
					{
						TIM_ClearFlag(TIM2, TIM_FLAG_Update);
						TIM_Cmd(TIM2, DISABLE);  
						TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
							//RFM73_SwitchToTxMode();
							acceptedCmd();
					} break;
					case 'N':
					{
							acceptedCmd();
					} break;
					case 'S':
					{
							chksum = 0;
							for (i = 1; i < (len-1); i++)
						{
							chksum += rx_buf[i];
						}
						if((rx_buf[0] == TRANS_START)&&(chksum == rx_buf[len-1]))
						{
							for (i = 0; i < len; i++)
							USART1_Send(rx_buf[i]);
							licznik++;
						}else
						{
						//	USART1_SendText("TRANS ERROR\n\r");
						}
						if(licznik >= 100)
						{
							LED_1_Change();
							licznik = 0;
						}
					} break;
					default:
					{
						noAcceptedCmd();
					}
				}
			}
		}
		/* Clear the  EXTI line pending bit */
		EXTI_ClearITPendingBit(RFM73_EXTI_Line);	
}



/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
