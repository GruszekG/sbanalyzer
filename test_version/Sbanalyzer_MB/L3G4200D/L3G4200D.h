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

#ifndef _L3G4200D_H
#define _L3G4200D_H

/*Includes*/
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"

/*L3G4200D SPI port*/
#define L3G4200D_SPI  				SPI2
#define L3G4200D_SPI_GPIO 			GPIOB     //L3G4200D GPIO port for SPI
                                
#define L3G4200D_SS   				GPIO_Pin_12    //SPI SS
#define L3G4200D_SCK  				GPIO_Pin_13    //SPI SCK
#define L3G4200D_MISO 				GPIO_Pin_14    //SPI MISO
#define L3G4200D_MOSI 				GPIO_Pin_15    //SPI MOSI


#define L3G4200D_ID					0xD3

typedef unsigned          char uint8_t;

/*Commands*/
typedef enum
{
	L3G4200D_WRITE 	 		=(uint8_t)0x00,           //SPI
	L3G4200D_READ  	 		=(uint8_t)0x80,         //SPI
	L3G4200D_ADDR_NO_INC 	=(uint8_t)0x00,
	L3G4200D_ADDR_INC_SPI  	=(uint8_t)0x40  		//SPI
}	L3G4200D_Commands;

typedef enum
{
	L3G4200D_ERROR 			=(uint8_t)0x01,
	L3G4200D_OK    			=(uint8_t)0x00
}	L3G4200D_Status;



/*--------------Settings---------------------*/
//-------------CTRL_REG1(L3G4200D_CTRL_REG1)----------------//
//ODR
typedef enum 
{
	L3G4200D_100Hz  =(uint8_t)0x00,
	L3G4200D_200Hz  =(uint8_t)0x40,
	L3G4200D_400Hz	=(uint8_t)0x80,
	L3G4200D_800Hz	=(uint8_t)0xC0
}	L3G4200D_ODR;

typedef enum
{
	L3G4200D_CutOff_0	=(uint8_t)0x00,// CutOff value depends on ODR
	L3G4200D_CutOff_1	=(uint8_t)0x10,
	L3G4200D_CutOff_2	=(uint8_t)0x20,
	L3G4200D_CutOff_3	=(uint8_t)0x30
}	L3G4200D_CutOff;

typedef enum
{									
	L3G4200D_PowerDown			=(uint8_t)0x00,
	L3G4200D_NormalPowerMode	=(uint8_t)0x08
}	L3G4200D_PowerMode;

typedef enum 
{
	L3G4200D_XYZ_Enable	=(uint8_t)0x07,
	L3G4200D_XYZ_Disable=(uint8_t)0x00,
	L3G4200D_X_Enable	=(uint8_t)0x01,
	L3G4200D_Y_Enable	=(uint8_t)0x02,
	L3G4200D_Z_Enable	=(uint8_t)0x04
}	L3G4200D_XYZ_Status;

//---------CTRL_REG2(L3G4200D_CTRL_REG2)--------------------//


//---------CTRL_REG3(L3G4200D_CTRL_REG3)--------------------//
typedef enum
{
	L3G4200D_I1_Int1	=(uint8_t)0x80,
	L3G4200D_I1_Boot	=(uint8_t)0x40, 
	L3G4200D_H_Lactive	=(uint8_t)0x20,
	L3G4200D_PP_OD		=(uint8_t)0x10,
	L3G4200D_I2_DRDY	=(uint8_t)0x08,
	L3G4200D_I2_WTM		=(uint8_t)0x04,
	L3G4200D_I2_ORun	=(uint8_t)0x02,
	L3G4200D_I2_Empty	=(uint8_t)0x01
}	L3G4200D_REG3_Bits;

//---------CTRL_REG4(L3G4200D_CTRL_REG4)--------------------//
typedef enum
{
	L3G4200D_250dps		=(uint8_t)0x00,
	L3G4200D_500dps		=(uint8_t)0x10,
	L3G4200D_2000dps	=(uint8_t)0x20 //(0x30)
}	L3G4200D_Range;

typedef enum
{
	L3G4200D_BlockDataUpdate=(uint8_t)0x80, //(0: continous update, 1: output registers not update until MSB and LSB reading
	L3G4200D_BLE			=(uint8_t)0x40, //(0: Data LSB in lower address, 1: data MSB in lower address

	L3G4200D_ST_OFF			=(uint8_t)0x00,
	L3G4200D_ST_0			=(uint8_t)0x02,
	L3G4200D_ST_1			=(uint8_t)0x06,
									  
	L3G4200D_SPI_4_WIRE		=(uint8_t)0x00,
	L3G4200D_SPI_3_WIRE		=(uint8_t)0x01
}  L3G4200D_REG4_Bits;

//---------CTRL_REG5(L3G4200D_CTRL_REG5)--------------------//
//BOOT
typedef enum
{
	L3G4200D_BOOT_NM		=(uint8_t)0x00,
	L3G4200D_REBOOT			=(uint8_t)0x80,
	
	L3G4200D_FIFO_ENABLE	=(uint8_t)0x40,
						
	L3G4200D_HPF_ENABLE		=(uint8_t)0x10,
									  
	L3G4200D_INT1_Sel0		=(uint8_t)0x08,
	L3G4200D_INT1_Sel1		=(uint8_t)0x04,
	
	L3G4200D_Out_Sel0		=(uint8_t)0x02,
	L3G4200D_Out_Sel1		=(uint8_t)0x01
}	L3G4200D_REG5_Bits;

/*-----------Registers-----------------------*/
// L3G4200D Register Names, taken from datasheet
typedef enum
{
	L3G4200D_WHO_AM_I		=(uint8_t)0x0F,
						  
	L3G4200D_CTRL_REG1		=(uint8_t)0x20,
	L3G4200D_CTRL_REG2		=(uint8_t)0x21,	
	L3G4200D_CTRL_REG3		=(uint8_t)0x22,
	L3G4200D_CTRL_REG4		=(uint8_t)0x23,
	L3G4200D_CTRL_REG5		=(uint8_t)0x24,
	
	L3G4200D_REFERENCE		=(uint8_t)0x25,
	
	L3G4200D_OUT_TEMP		=(uint8_t)0x26,
	
	L3G4200D_STATUS_REG		=(uint8_t)0x27,
					  	
	L3G4200D_OUT_X_L		=(uint8_t)0x28,
	L3G4200D_OUT_X_H		=(uint8_t)0x29,
	L3G4200D_OUT_Y_L		=(uint8_t)0x2A,
	L3G4200D_OUT_Y_H		=(uint8_t)0x2B,
	L3G4200D_OUT_Z_L		=(uint8_t)0x2C,
	L3G4200D_OUT_Z_H		=(uint8_t)0x2D,
	
	L3G4200D_FIFO_CTRL_REG	=(uint8_t)0x2E,
	L3G4200D_FIFO_SRC_REG	=(uint8_t)0x2F,
	
	L3G4200D_INT1_CFG		=(uint8_t)0x30,
	L3G4200D_INT1_SOURCE	=(uint8_t)0x31,
	
	L3G4200D_INT1_TSH_XH	=(uint8_t)0x32,
	L3G4200D_INT1_TSH_XL	=(uint8_t)0x33,
	L3G4200D_INT1_TSH_YH	=(uint8_t)0x34,
	L3G4200D_INT1_TSH_YL	=(uint8_t)0x35,
	L3G4200D_INT1_TSH_ZH	=(uint8_t)0x36,
	L3G4200D_INT1_TSH_ZL	=(uint8_t)0x37,
	
	L3G4200D_INT1_DURATION	=(uint8_t)0x38
} 	L3G4200D_Reg ;
/*Speed vector*/
struct vector_w
{
	uint8_t X_MSB;
	uint8_t X_LSB;

	uint8_t Y_MSB;
	uint8_t Y_LSB;

	uint8_t Z_MSB;
	uint8_t Z_LSB;
};


/*------Fnctions-------------------------------*/
void L3G4200D_SPI_HwConfig(void);
void L3G4200D_RebootMemory(void);
L3G4200D_Status L3G4200D_Conf(L3G4200D_ODR ODR, L3G4200D_Range range);

L3G4200D_Status L3G4200D_Sleep(void);
L3G4200D_Status L3G4200D_Wake(void);

void L3G4200D_ReadRegister(L3G4200D_Reg addr, char *v);
void L3G4200D_WriteRegister(L3G4200D_Reg addr, char v);
															 
void L3G4200D_GetRot_8_bits(char * x, char * y, char * z);
void L3G4200D_GetRot_16_bits(uint8_t *vect, uint8_t* sum);
void L3G4200D_GetRotVect(struct vector_w * V);

void L3G4200D_SPI_CS_Enable(void);
void L3G4200D_SPI_CS_Disable(void);

#endif
