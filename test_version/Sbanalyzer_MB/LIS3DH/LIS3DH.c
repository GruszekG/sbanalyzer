/*
		LIS3DH- MEMS digital output motion sensor ultra low-power high performance 3-axes “nano” accelerometer
		Library for STM32F10*.
		Communication interface: SPI
		
		This library is part of the "SkateboardAnalyzer" project.
		project	website: <http://sbanalyzer.pl/>
		organization: Synergia <http://synergia.pwr.wroc.pl/>
		year: 2013
		author: Grzegorz Gruszka
		e-mail: grzegorz.gruszka1990@gmail.com
*/

#include "LIS3DH.h"


void LIS3DH_SPI_HwConfig(void) //Hardware configuration
{ //GPIO and SPI configuration
	GPIO_InitTypeDef  GPIO_InitStructure; 
	SPI_InitTypeDef  SPI_InitStructure;
	
	//GPIO Config
	GPIO_InitStructure.GPIO_Pin =LIS3DH_MOSI | LIS3DH_MISO | LIS3DH_SCK;    //SPI - SCK, MISO & MOSI
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LIS3DH_SPI_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = LIS3DH_SS;                             //SPI - SS
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(LIS3DH_SPI_GPIO, &GPIO_InitStructure);
	
	//SPI Config
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(LIS3DH_SPI, &SPI_InitStructure);
	
	SPI_Cmd(LIS3DH_SPI, ENABLE);                    
}


char  LIS3DH_SPI_Transmit(char Data)
{ 
	SPI_I2S_SendData(LIS3DH_SPI, Data);
	while (SPI_I2S_GetFlagStatus(LIS3DH_SPI, SPI_I2S_FLAG_RXNE) == RESET);
	return (char) SPI_I2S_ReceiveData(LIS3DH_SPI);
}

    
void LIS3DH_SPI_CS_Enable(void)
{
	GPIO_ResetBits(LIS3DH_SPI_GPIO, LIS3DH_SS);
}


void LIS3DH_SPI_CS_Disable(void)
{
  GPIO_SetBits(LIS3DH_SPI_GPIO, LIS3DH_SS);
}


void LIS3DH_RebootMemory(void)
{
	LIS3DH_SPI_CS_Enable();
	LIS3DH_SPI_Transmit(LIS3DH_WRITE|LIS3DH_ADDR_NO_INC|LIS3DH_CTRL_REG5);
	LIS3DH_SPI_Transmit(LIS3DH_REBOOT);
	LIS3DH_SPI_CS_Disable();
}
//LIS3DH configuration. 
//ODR- output data rate:
//			 LIS3DH_10Hz					
//			 LIS3DH_25Hz				
//			 LIS3DH_50Hz					
//			 LIS3DH_100Hz				
//			 LIS3DH_200Hz			
//			 LIS3DH_400Hz			
//			 LIS3DH_LP_1600Hz		//Low power mode
//			 LIS3DH_12500Hz			//Normal power mode
//			 LIS3DH_LP_5kHz			//Low power mode
//Range:
//			 LIS3DH_2G					
//			 LIS3DH_4G					
//			 LIS3DH_8G				
//			 LIS3DH_16G
//Power mode:
//			 LIS3DH_LowPowerMode			
//			 LIS3DH_NormalPowerMode	
					
LIS3DH_Status LIS3DH_Conf(LIS3DH_ODR ODR, LIS3DH_Range range, LIS3DH_PowerMode power_mode)
{
	char RegVal1, LIS3DHSettings1 ,RegVal2, LIS3DHSettings2;
	
	//Reset LIS3DH configuration
	LIS3DH_RebootMemory();
	LIS3DH_ReadRegister(LIS3DH_WHO_AM_I, &RegVal1);
	if(RegVal1!=LIS3DH_ID) return LIS3DH_ERROR; //LIS3DH ID verification
	
	//CTRL_REG1 configuration
	LIS3DH_ReadRegister(LIS3DH_CTRL_REG1, &RegVal1);	
	LIS3DHSettings1 = ODR | power_mode | LIS3DH_XYZ_Enable;
	LIS3DH_WriteRegister(LIS3DH_CTRL_REG1, LIS3DHSettings1);
	LIS3DH_ReadRegister(LIS3DH_CTRL_REG1, &RegVal1);

	//CTRL_REG4 configuration
	LIS3DH_ReadRegister(LIS3DH_CTRL_REG4, &RegVal2);	
	LIS3DHSettings2 = range | LIS3DH_HR_Enable | LIS3DH_ST_OFF | LIS3DH_SPI_4_WIRE | LIS3DH_BlockDataUpdate;;//LIS3DH_HR_Enable- set high resolution output mode
	LIS3DH_WriteRegister(LIS3DH_CTRL_REG4, LIS3DHSettings2);
	LIS3DH_ReadRegister(LIS3DH_CTRL_REG4, &RegVal2);
	
	
	
	if ((RegVal1 == LIS3DHSettings1)&(RegVal2 == LIS3DHSettings2)) return LIS3DH_OK;
	return LIS3DH_ERROR;
}


void LIS3DH_ReadRegister(char addr,char * v)
{
	LIS3DH_SPI_CS_Enable();
	LIS3DH_SPI_Transmit(LIS3DH_READ|LIS3DH_ADDR_NO_INC|addr);
	*v=LIS3DH_SPI_Transmit(0xFF);
	LIS3DH_SPI_CS_Disable();
}


void LIS3DH_WriteRegister(char addr, char v)
{
	LIS3DH_SPI_CS_Enable();
	LIS3DH_SPI_Transmit(LIS3DH_WRITE|LIS3DH_ADDR_NO_INC|addr);
	LIS3DH_SPI_Transmit(v);
	LIS3DH_SPI_CS_Disable();
}


void LIS3DH_GetAcc_8_bits(char * x, char * y, char * z)
{
	LIS3DH_SPI_CS_Enable();

	LIS3DH_SPI_Transmit(LIS3DH_READ|LIS3DH_ADDR_INC_SPI|LIS3DH_OUT_X_H);
	
	*x=LIS3DH_SPI_Transmit(0xFF);
	LIS3DH_SPI_Transmit(0xFF);
	*y=LIS3DH_SPI_Transmit(0xFF);
	LIS3DH_SPI_Transmit(0xFF);
	*z=LIS3DH_SPI_Transmit(0xFF);
	LIS3DH_SPI_CS_Disable();
}

void LIS3DH_GetAccVect(struct vector_a * V)
{
	unsigned char status = 0x80;

	LIS3DH_SPI_CS_Enable();

	do{
		LIS3DH_SPI_Transmit(LIS3DH_READ|LIS3DH_ADDR_NO_INC|LIS3DH_STATUS_REG_AUX);
	}while(status!=(LIS3DH_SPI_Transmit(0xFF)&0x80));

	LIS3DH_SPI_Transmit(LIS3DH_READ|LIS3DH_ADDR_INC_SPI|LIS3DH_OUT_X_L);
	
	V->X_LSB=LIS3DH_SPI_Transmit(0xFF);
	V->X_MSB=LIS3DH_SPI_Transmit(0xFF);
	
	V->Y_LSB=LIS3DH_SPI_Transmit(0xFF);
	V->Y_MSB=LIS3DH_SPI_Transmit(0xFF);
	
	V->Z_LSB=LIS3DH_SPI_Transmit(0xFF);
	V->Z_MSB=LIS3DH_SPI_Transmit(0xFF);
	
	LIS3DH_SPI_CS_Disable();
}

void LIS3DH_GetAcc_16_bits(uint8_t *vect, uint8_t* sum)
{
	LIS3DH_SPI_CS_Enable();
	do{
		LIS3DH_SPI_Transmit(LIS3DH_READ|LIS3DH_ADDR_NO_INC|LIS3DH_STATUS_REG_AUX);
	}while(0x08!=(LIS3DH_SPI_Transmit(0xFF)&0x08));
	LIS3DH_SPI_CS_Disable();

	LIS3DH_SPI_CS_Enable();
	LIS3DH_SPI_Transmit(LIS3DH_READ|LIS3DH_ADDR_INC_SPI|LIS3DH_OUT_X_L);
	
	*(vect) = LIS3DH_SPI_Transmit(0xFF);	//X_LSB
	*(vect+1)=LIS3DH_SPI_Transmit(0xFF);  //X_MSB

	*sum += *(vect);
	*sum += *(vect+1);
	
	*(vect+2)=LIS3DH_SPI_Transmit(0xFF);	//Y_LSB
	*(vect+3)=LIS3DH_SPI_Transmit(0xFF);	//Y_MSB

	*sum += *(vect+2);
	*sum += *(vect+3);
	
	*(vect+4)=LIS3DH_SPI_Transmit(0xFF);	//Z_LSB
	*(vect+5)=LIS3DH_SPI_Transmit(0xFF);	//Z_MSB

	*sum += *(vect+4);
	*sum += *(vect+5);
	
	LIS3DH_SPI_CS_Disable();
}
/*---------Single tap-tap configuration--------------------//

InteruptPin: 1: interrupt pin 1; 2: interrupt pin 2;
TapMode: 1: single click; 2: double click;
TapAxis: LIS3DH_Z_Tap, LIS3DH_Y_Tap, LIS3DH_X_Tap
(Threshold value) =  Threshold * (full scale / 128);         0<=Threshold<128
(Time limit value) = TimeLimit * (1/ODR);					 0<=TimeLimit<128
(Time latency value) = TimeLatency * (1/ODR);				 0<=TimeLatency<256
(Time window value) = TimeWindow * (1/ODR);		  			 0<=TimeWindow<256    */

LIS3DH_Status LIS3DH_Tap_Tap_Conf(struct TapTapInitStruct Init)
{
	char reg = 0;
	char test = 0;
	
	LIS3DH_SPI_CS_Enable();

	LIS3DH_WriteRegister(LIS3DH_TIME_WINDOW, Init.TimeWindow);
	
	if(Init.InteruptPin == 1)
	{
		LIS3DH_ReadRegister(LIS3DH_CTRL_REG3, &reg);
		reg |= 0x80;
		LIS3DH_WriteRegister(LIS3DH_CTRL_REG3, reg);
		LIS3DH_ReadRegister(LIS3DH_CTRL_REG3, &test);

		if(test!=reg) return LIS3DH_ERROR;
	}
	else if(Init.InteruptPin == 2)
	{
		LIS3DH_ReadRegister(LIS3DH_CTRL_REG6, &reg);
		reg |= 0x80;
		LIS3DH_WriteRegister(LIS3DH_CTRL_REG6, reg);
		LIS3DH_ReadRegister(LIS3DH_CTRL_REG6, &test);

		if(test!=reg) return LIS3DH_ERROR;
	}

	LIS3DH_WriteRegister(LIS3DH_CLICK_THS, Init.Threshold);
	LIS3DH_WriteRegister(LIS3DH_TIME_LIMIT, Init.TimeLimit);
	LIS3DH_WriteRegister(LIS3DH_TIME_LATENCY, Init.TimeLatency);

	LIS3DH_WriteRegister(LIS3DH_CLICK_CFG, Init.TapMode);	

	return LIS3DH_OK;
}

void LIS3DH_EXTI_Enable(void)
{
	/* Private variables */
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;

	/* Enable GPIO clock */
  	RCC_APB2PeriphClockCmd(LIS3DH_RCC_INT, ENABLE);
	//RCC_APB1PeriphClockCmd(LIS3DH_RCC_INT, ENABLE);

	/* Configure pin as input floating */
 	GPIO_InitStructure.GPIO_Pin = LIS3DH_INT1_Pin|LIS3DH_INT2_Pin;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(LIS3DH_INT_GPIO, &GPIO_InitStructure);

	/* Enable AFIO clock */
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	/* Connect EXTI Line to LIS3DH int. port */
 	GPIO_EXTILineConfig(LIS3DH_INT_PortSource, LIS3DH_INT1_S|LIS3DH_INT2_S);

	/* Configure EXTI line */
  	EXTI_InitStructure.EXTI_Line = LIS3DH_EXTI1_Line|LIS3DH_EXTI2_Line;
 	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI Interrupt to the lowest priority */
 	NVIC_InitStructure.NVIC_IRQChannel = LIS3DH_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 	NVIC_Init(&NVIC_InitStructure);

}

void LIS3DH_EXTI_Disable(void)
{
	/* Private variables */
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;

	/* Configure EXTI line */
  	EXTI_InitStructure.EXTI_Line = LIS3DH_EXTI1_Line|LIS3DH_EXTI2_Line;
 	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
  	EXTI_InitStructure.EXTI_LineCmd = DISABLE;
  	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI Interrupt to the lowest priority */
 	NVIC_InitStructure.NVIC_IRQChannel = LIS3DH_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
 	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
 	NVIC_Init(&NVIC_InitStructure);

}

void EXTI9_5_IRQHandler(void)
{
	//LIS3DH pin INT1 interupt
	if(EXTI_GetITStatus(LIS3DH_EXTI1_Line) != RESET)
	{		
		/* Clear the  EXTI line pending bit */
		EXTI_ClearITPendingBit(LIS3DH_EXTI1_Line);
	}

	//LIS3DH pin INT2  interupt
	if(EXTI_GetITStatus(LIS3DH_EXTI2_Line) != RESET)
	{		
		/* Clear the  EXTI line pending bit */
		EXTI_ClearITPendingBit(LIS3DH_EXTI2_Line);
	}
	
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0)==SET) GPIO_ResetBits(GPIOA, GPIO_Pin_0);
		else GPIO_SetBits(GPIOA, GPIO_Pin_0);
}
