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
#include "RFM73.h"

#include "LIS3DH.h"
#include "L3G4200D.h"
#include "LPY4150AL.h"

#include "commands.h"

#include "main.h"

#define switchTxToRxDelay 100

 uint8_t bufor[18];
 uint32_t measurementDownCounter;
 uint32_t measurementTime;
 uint32_t measurementFreq;

extern unsigned char buforRx[17];
extern unsigned char buforTx[17];



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




/*******************************************************************************
* Function Name  : TIM2_IRQHandler
* Description    : This function handles TIM2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_FLAG_Update) != RESET)
	{
		TIM_ClearFlag(TIM2, TIM_FLAG_Update);

		if(measurementDownCounter > 0)
		{
			
			RFM73_to_LIS3DH();
			
			bufor[0] = 0x53;
			bufor[17] = 0x00;
			
			L3G4200D_GetRot_16_bits(&bufor[1], &bufor[17]);
			LIS3DH_GetAcc_16_bits(&bufor[7], &bufor[17]);
			LPY4150AL_GetRot_16_bits(&bufor[13], &bufor[17]);
			
			LIS3DH_to_RFM73(); //change spi mode
		//	RFM73_SwitchToTxMode();
			
	//		if(!(measurementDownCounter%100))
	//		{
	//			LED_Change();
	//		}
			
			if(SPI_Read_Reg(STATUS)== 0)
			{
				LED_OFF();
				while(1);
			}
			
			Send_Packet(W_TX_PAYLOAD_NOACK_CMD, bufor, 18);

			measurementDownCounter--;

		}else
		{
			RFM73_SwitchToRxMode();
			TIM2_Disable();
			LED_OFF();
			TIM_ClearFlag(TIM2, TIM_FLAG_Update);
		}
	}
}

void EXTI2_IRQHandler(void)
{
	uint8_t rx_buf[MAX_PACKET_LEN];
	uint8_t len;
	LIS3DH_to_RFM73();
	if(EXTI_GetITStatus(RFM73_EXTI_Line) != RESET)
	{	
		if(GPIO_ReadOutputDataBit(RFM73_SPI_GPIO, RFM73_IRQ) == RESET)
		{
			RFM73_SwitchToTxMode();
			Receive_Packet(rx_buf, &len);
			
			if(len > 0  &&  rx_buf[0] < CmdCount)
			{
				switch (rx_buf[0])
				{
					case Measure_Cmd: //start
					{
							Delay(100);
							acceptedCmd();
							Delay(1000);
							TIM2_Conf();
							TIM2_Enable();
							measurementDownCounter = measurementTime*measurementFreq;
							LED_ON();
					}
					break;
					case Conf_Cmd: //conf
					{
						LED_ON();
					//	Delay(100);
						Delay(switchTxToRxDelay);
						if(confCommand(rx_buf) != Cmd_OK)
							noAcceptedCmd();
						else 
							acceptedCmd();
						Delay(1000);	
						RFM73_SwitchToRxMode();
						Delay(switchTxToRxDelay);
						LED_OFF();
						
					}
					break;
				}
			}else 
			{
				SPI_Command(FLUSH_RX);//flush Rx
				RFM73_SwitchToRxMode();
			}
				
		}
		/* Clear the  EXTI line pending bit */
		EXTI_ClearITPendingBit(RFM73_EXTI_Line);
	}	
}

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
