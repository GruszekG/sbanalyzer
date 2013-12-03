#include "main.h"

/*-------------includes--------------*/
#include "LIS3DH.h"
#include "L3G4200D.h"
#include "LPY4150AL.h"
#include "RFM73.h"
#include "commands.h"

#include "stm32f10x_it.h"

extern uint32_t measurementTime;
extern uint32_t measurementFreq;
//sdf

/*---------------------------------------------*/
/*---------------MAIN--------------------------*/
/*---------------------------------------------*/
int main(void)
{			  
/*------BOARD INITIALIZATION-------------*/
   	while(Init_board()!=TRUE);
	LED_ON();
	Delay(1000);
	LED_OFF();
/*-------------------------------------------*/

//	NVIC_Conf();
//	RFM73_EXTI_Enable();
//	TIM2_Conf();
//	LIS3DH_to_RFM73(); //change spi mode
	while(1)
	{
	//	Delay(100);
	//	acceptedCmd();
	};
}


/*---------------------------------------------*/
/*---------------FUNCTIONS---------------------*/
/*---------------------------------------------*/

bool Init_board(void)
{
	RCC_Conf();
	NVIC_Conf();
	SysTick_Config_Mod(SysTick_CLKSource_HCLK_Div8, 9000);
	RFM73_EXTI_Enable();
	LED_Conf();

	RFM73_SPI_Conf();
	L3G4200D_SPI_HwConfig();
   	LIS3DH_SPI_HwConfig();

	RFM73_PowerOFF();
	RFM73_CSN_High();
	RFM73_to_LIS3DH();

	if(L3G4200D_Conf(L3G4200D_800Hz, L3G4200D_2000dps) == L3G4200D_ERROR) return FALSE;
	Delay(50);
	if(LIS3DH_Conf(LIS3DH_1250Hz, LIS3DH_2G, LIS3DH_NormalPowerMode) == LIS3DH_ERROR) return FALSE;
	LIS3DH_SPI_CS_Disable();  

	LPY4150AL_Conf();	 
	LPY4150AL_Enable();    

	LIS3DH_to_RFM73();

	RFM73_PowerON();   
	Delay(500);
	if(RFM73_Initialize() == RFM73_ERROR)	return FALSE;	 
//	RFM73_SwitchToTxMode();
	SPI_Command(FLUSH_TX);//flush Rx
	RFM73_SwitchToRxMode();
	SPI_Command(FLUSH_RX);//flush Rx
	Delay(200);


	RFM73_CSN_High();

//	RFM73_to_LIS3DH();
	
	measurementTime = 5;
	measurementFreq = 800;

	return TRUE;
}

void RFM73_to_LIS3DH(void)
{
  	SPI_Cmd(LIS3DH_SPI, DISABLE);
	SPI_CalculateCRC(RFM73_SPI, ENABLE);
	SPI1->CR1 |= (SPI_CPOL_High|SPI_CPHA_2Edge);
	SPI1->CRCPR = 7;
	SPI_Cmd(LIS3DH_SPI, ENABLE);                    

}
void LIS3DH_to_RFM73(void)
{
	SPI_Cmd(RFM73_SPI, DISABLE);
	SPI_CalculateCRC(RFM73_SPI, DISABLE);
	SPI1->CR1 &= ~(SPI_CPOL_High|SPI_CPHA_2Edge);
	SPI1->CRCPR = 0;
	SPI_Cmd(RFM73_SPI, ENABLE);                                         // Wlacz SPI

}

void LED_Conf(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_Init( GPIOA, &GPIO_InitStruct );	
}
void LED_OFF(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);	
}
void LED_ON(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_0);	
}

void LED_Change(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0)) GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	else GPIO_SetBits(GPIOA, GPIO_Pin_0);	
}

void RCC_Conf(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_SPI1|RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2|RCC_APB1Periph_TIM2, ENABLE);
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

void TIM2_Conf(void){

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
//	TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
//	TIM_Cmd(TIM2, DISABLE);

	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; 
	//TIM_TimeBaseInitStruct.TIM_Period = 49;					 // 1000 tacts => 0,1s
	//TIM_TimeBaseInitStruct.TIM_Period = 125;					 //125 tacts => 1,25 ms => 800 Hz
	TIM_TimeBaseInitStruct.TIM_Period = 100000/measurementFreq;					 //125 tacts => 1,25 ms => 800 Hz
	TIM_TimeBaseInitStruct.TIM_Prescaler = 720-1;				//72MHz / 720 = 10kHz => T=0,01ms
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
//	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
//	TIM_Cmd(TIM2, ENABLE);
}
void NVIC_Conf(void)
{
	NVIC_InitTypeDef NVIC_InitStruct_TIM2, NVIC_InitStructure;

	//	/* Enable and set EXTI Interrupt to the lowest priority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
 	NVIC_InitStructure.NVIC_IRQChannel = RFM73_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStruct_TIM2.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct_TIM2.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct_TIM2.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct_TIM2.NVIC_IRQChannelSubPriority = 1;

	NVIC_Init(&NVIC_InitStruct_TIM2);
}
void TIM2_Enable(void)
{
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
}
void TIM2_Disable(void)
{
	TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
	TIM_Cmd(TIM2, DISABLE);
}

void TIM2_ChangePeriod(uint16_t _period)
{
	TIM2->ARR = _period;
}
