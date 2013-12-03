/*
		L3G4200D- MEMS motion sensor:
		ultra-stable three-axis digital output gyroscope
		Library for STM32F10*.
		Communication interface: SPI
		
		This library is part of the "SkateboardAnalyzer" project.
		project	website: <http://sbanalyzer.pl/>
		organization: Synergia <http://synergia.pwr.wroc.pl/>
		year: 2013
		author: Grzegorz Gruszka
		e-mail: grzegorz.gruszka1990@gmail.com
*/

#include "L3G4200D.h"


void L3G4200D_SPI_HwConfig(void)
{ //GPIO and SPI configuration
	GPIO_InitTypeDef  GPIO_InitStructure; 
	SPI_InitTypeDef  SPI_InitStructure;

	
	//GPIO Config
	GPIO_InitStructure.GPIO_Pin =L3G4200D_MOSI | L3G4200D_MISO | L3G4200D_SCK;    //SPI - SCK, MISO & MOSI
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(L3G4200D_SPI_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = L3G4200D_SS;                             //SPI - SS
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(L3G4200D_SPI_GPIO, &GPIO_InitStructure);
	
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
	SPI_Init(L3G4200D_SPI, &SPI_InitStructure);
	
	SPI_Cmd(L3G4200D_SPI, ENABLE);                                         // Wlacz SPI
}


char  L3G4200D_SPI_Transmit(char Data)
{ 
	SPI_I2S_SendData(L3G4200D_SPI, Data);
	while (SPI_I2S_GetFlagStatus(L3G4200D_SPI, SPI_I2S_FLAG_RXNE) == RESET);
	return (char) SPI_I2S_ReceiveData(L3G4200D_SPI);
}

    
void L3G4200D_SPI_CS_Enable(void)
{
	GPIO_ResetBits(L3G4200D_SPI_GPIO, L3G4200D_SS);
}


void L3G4200D_SPI_CS_Disable(void)
{
  GPIO_SetBits(L3G4200D_SPI_GPIO, L3G4200D_SS);
}


void L3G4200D_RebootMemory(void)
{
	L3G4200D_SPI_CS_Enable();
	L3G4200D_SPI_Transmit(L3G4200D_WRITE|L3G4200D_ADDR_NO_INC|L3G4200D_CTRL_REG5);
	L3G4200D_SPI_Transmit(L3G4200D_REBOOT);
	L3G4200D_SPI_CS_Disable();
}

//L3G4200D configuration. 
//ODR- output data rate:
//			L3G4200D_100Hz				
// 			L3G4200D_200Hz			
//			L3G4200D_400Hz			
//			L3G4200D_800Hz			
//Range:
//			L3G4200D_250dps				
//			L3G4200D_500dps				
//			L3G4200D_2000dps			
L3G4200D_Status L3G4200D_Conf(L3G4200D_ODR ODR, L3G4200D_Range range)
{
	char RegVal1, L3G4200DSettings1 ,RegVal2, L3G4200DSettings2;
	
	//Reset L3G4200D configuration
	L3G4200D_RebootMemory();
	L3G4200D_ReadRegister(L3G4200D_WHO_AM_I, &RegVal1);
	if(RegVal1!=L3G4200D_ID) return L3G4200D_ERROR; //L3G4200D ID verification
	
	//CTRL_REG1 configuration
	L3G4200D_ReadRegister(L3G4200D_CTRL_REG1, &RegVal1);	
	L3G4200DSettings1 = ODR | L3G4200D_NormalPowerMode | L3G4200D_XYZ_Enable | L3G4200D_CutOff_0;
	L3G4200D_WriteRegister(L3G4200D_CTRL_REG1, L3G4200DSettings1);
	L3G4200D_ReadRegister(L3G4200D_CTRL_REG1, &RegVal1);

	//CTRL_REG4 configuration 
	L3G4200D_ReadRegister(L3G4200D_CTRL_REG4, &RegVal2);	
	L3G4200DSettings2 = range | L3G4200D_ST_OFF | L3G4200D_SPI_4_WIRE|L3G4200D_BlockDataUpdate;
	L3G4200D_WriteRegister(L3G4200D_CTRL_REG4, L3G4200DSettings2);
	L3G4200D_ReadRegister(L3G4200D_CTRL_REG4, &RegVal2);
	
	
	
	if ((RegVal1 == L3G4200DSettings1)&(RegVal2 == L3G4200DSettings2)) return L3G4200D_OK;
	return L3G4200D_ERROR;
}


void L3G4200D_ReadRegister(L3G4200D_Reg addr,char * v)
{
	L3G4200D_SPI_CS_Enable();
	L3G4200D_SPI_Transmit(L3G4200D_READ|L3G4200D_ADDR_NO_INC|addr);
	*v=L3G4200D_SPI_Transmit(0xFF);
	L3G4200D_SPI_CS_Disable();
}


void L3G4200D_WriteRegister(L3G4200D_Reg addr, char v)
{
	L3G4200D_SPI_CS_Enable();
	L3G4200D_SPI_Transmit(L3G4200D_WRITE|L3G4200D_ADDR_NO_INC|addr);
	L3G4200D_SPI_Transmit(v);
	L3G4200D_SPI_CS_Disable();
}

L3G4200D_Range L3G4200D_Get_Range(void)
{
	char _range;
	L3G4200D_ReadRegister(L3G4200D_CTRL_REG4,&_range);
	return _range&0x30;	
}
L3G4200D_ODR L3G4200D_Get_ODR(void)
{
	char _ODR;
	L3G4200D_ReadRegister(L3G4200D_CTRL_REG1,&_ODR);
	return _ODR&0xC0;
}


void L3G4200D_GetRot_8_bits(char * x, char * y, char * z)
{
	L3G4200D_SPI_CS_Enable();
	L3G4200D_SPI_Transmit(L3G4200D_READ|L3G4200D_ADDR_INC_SPI|L3G4200D_OUT_X_H);
	
	*x=L3G4200D_SPI_Transmit(0xFF);
	L3G4200D_SPI_Transmit(0xFF);
	*y=L3G4200D_SPI_Transmit(0xFF);
	L3G4200D_SPI_Transmit(0xFF);
	*z=L3G4200D_SPI_Transmit(0xFF);
	L3G4200D_SPI_CS_Disable();
}

void L3G4200D_GetRotVect(struct vector_w * V)
{
	unsigned char status = 0x80;

	L3G4200D_SPI_CS_Enable();

	do{
		L3G4200D_SPI_Transmit(L3G4200D_READ|L3G4200D_ADDR_NO_INC|L3G4200D_STATUS_REG);
	}while(status!=(L3G4200D_SPI_Transmit(0xFF)&0x80));


	L3G4200D_SPI_Transmit(L3G4200D_READ|L3G4200D_ADDR_INC_SPI|L3G4200D_OUT_X_L);
	
	V->X_LSB=L3G4200D_SPI_Transmit(0xFF);
	V->X_MSB=L3G4200D_SPI_Transmit(0xFF);
	
	V->Y_LSB=L3G4200D_SPI_Transmit(0xFF);
	V->Y_MSB=L3G4200D_SPI_Transmit(0xFF);
	
	V->Z_LSB=L3G4200D_SPI_Transmit(0xFF);
	V->Z_MSB=L3G4200D_SPI_Transmit(0xFF);
	
	L3G4200D_SPI_CS_Disable();
}

void L3G4200D_GetRot_16_bits(uint8_t *vect, uint8_t* sum)
{

L3G4200D_SPI_CS_Enable();

	do{
		L3G4200D_SPI_Transmit(L3G4200D_READ|L3G4200D_ADDR_NO_INC|L3G4200D_STATUS_REG);
	}while(0x08!=(L3G4200D_SPI_Transmit(0xFF)&0x08));

	L3G4200D_SPI_CS_Disable();
	L3G4200D_SPI_CS_Enable();


	L3G4200D_SPI_Transmit(L3G4200D_READ|L3G4200D_ADDR_INC_SPI|L3G4200D_OUT_X_L);
	
	*(vect) = L3G4200D_SPI_Transmit(0xFF);	//X_LSB
	*(vect+1)=L3G4200D_SPI_Transmit(0xFF);  //X_MSB

	*sum += *(vect);
	*sum += *(vect+1);
	
	*(vect+2)=L3G4200D_SPI_Transmit(0xFF);	//Y_LSB
	*(vect+3)=L3G4200D_SPI_Transmit(0xFF);	//Y_MSB

	*sum += *(vect+2);
	*sum += *(vect+3);
	
	*(vect+4)=L3G4200D_SPI_Transmit(0xFF);	//Z_LSB
	*(vect+5)=L3G4200D_SPI_Transmit(0xFF);	//Z_MSB

	*sum += *(vect+4);
	*sum += *(vect+5);
	
	L3G4200D_SPI_CS_Disable();
}
L3G4200D_Status L3G4200D_Sleep(void)
{
	char RegVal, L3G4200DSettings;
	//CTRL_REG1 configuration
	L3G4200D_ReadRegister(L3G4200D_CTRL_REG1, &RegVal);	
	L3G4200DSettings &= ~L3G4200D_NormalPowerMode;
	L3G4200D_WriteRegister(L3G4200D_CTRL_REG1, L3G4200DSettings);
	L3G4200D_ReadRegister(L3G4200D_CTRL_REG1, &RegVal);
	if(L3G4200DSettings == RegVal) return L3G4200D_OK;
	else return L3G4200D_ERROR;	
}
L3G4200D_Status L3G4200D_Wake(void)
{
	char RegVal, L3G4200DSettings;
	//CTRL_REG1 configuration
	L3G4200D_ReadRegister(L3G4200D_CTRL_REG1, &RegVal);	
	L3G4200DSettings |= L3G4200D_NormalPowerMode;
	L3G4200D_WriteRegister(L3G4200D_CTRL_REG1, L3G4200DSettings);
	L3G4200D_ReadRegister(L3G4200D_CTRL_REG1, &RegVal);
	if(L3G4200DSettings == RegVal) return L3G4200D_OK;
	else return L3G4200D_ERROR;
}
