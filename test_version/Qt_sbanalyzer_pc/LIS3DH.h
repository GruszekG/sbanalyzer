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


#ifndef _LIS3DH_H
#define _LIS3DH_H

//#include "stm32f10x_gpio.h"
//#include "stm32f10x_spi.h"
//#include "stm32f10x_exti.h"

/*LIS3DH SPI port*/

#define LIS3DH_SPI  				SPI1
#define LIS3DH_SPI_GPIO 			GPIOA     //LIS3DH GPIO port for SPI
                                
#define LIS3DH_SS   				GPIO_Pin_4    //SPI SS
#define LIS3DH_SCK  				GPIO_Pin_5    //SPI SCK
#define LIS3DH_MISO 				GPIO_Pin_6    //SPI MISO
#define LIS3DH_MOSI 				GPIO_Pin_7    //SPI MOSI

#define LIS3DH_RCC_SPI_Port			RCC_APB2Periph_GPIOA
#define LIS3DH_RCC_SPI				RCC_APB2Periph_SPI1

/*LIS3DH interrupt port*/

#define LIS3DH_INT_GPIO				GPIOB
#define LIS3DH_INT1_Pin				GPIO_Pin_7
#define LIS3DH_INT2_Pin				GPIO_Pin_6

#define LIS3DH_INT_PortSource		GPIO_PortSourceGPIOB

#define LIS3DH_INT1_S				GPIO_PinSource7
#define LIS3DH_INT2_S				GPIO_PinSource6

#define LIS3DH_EXTI1_Line			EXTI_Line7
#define LIS3DH_EXTI2_Line			EXTI_Line6

#define LIS3DH_IRQn					EXTI9_5_IRQn

#define LIS3DH_RCC_INT				RCC_APB2Periph_GPIOB

#define LIS3DH_INT1					0x01
#define LIS3DH_INT2					0x02

typedef unsigned          char uint8_t;

/*Commands*/
typedef enum
{
	LIS3DH_WRITE 	 		=(uint8_t)0x00,           //SPI
	LIS3DH_READ  	 		=(uint8_t)0x80,         //SPI
	LIS3DH_ADDR_NO_INC 	=(uint8_t)0x00,
	LIS3DH_ADDR_INC_SPI  	=(uint8_t)0x40  		//SPI
}	LIS3DH_Commands;

typedef enum
{
	LIS3DH_ERROR 			=(uint8_t)0x01,
	LIS3DH_OK    			=(uint8_t)0x00
}	LIS3DH_Status;

#define LIS3DH_ID					0x33

/*--------------Settings---------------------*/
//-------------CTRL_REG1(LIS3DH_CTRL_REG1)----------------//
//ODR
typedef enum
{
	LIS3DH_PDM 					=(uint8_t)0x00,//Power down mode(ODR = 0)
	LIS3DH_1Hz					=(uint8_t)0x10,
	LIS3DH_10Hz					=(uint8_t)0x20,
	LIS3DH_25Hz					=(uint8_t)0x30,
	LIS3DH_50Hz					=(uint8_t)0x40,
	LIS3DH_100Hz				=(uint8_t)0x50,
	LIS3DH_200Hz				=(uint8_t)0x60,
	LIS3DH_400Hz				=(uint8_t)0x70,
	LIS3DH_LP_1600Hz			=(uint8_t)0x88, //Low power mode
    LIS3DH_1250Hz				=(uint8_t)0x90, //Normal power mode
	LIS3DH_LP_5kHz				=(uint8_t)0x98 //Low power mode
}	LIS3DH_ODR;

typedef enum
{
	LIS3DH_LowPowerMode			=(uint8_t)0x08,
	LIS3DH_NormalPowerMode		=(uint8_t)0x00
}	LIS3DH_PowerMode;

typedef enum
{
	LIS3DH_XYZ_Enable			=(uint8_t)0x07,
	LIS3DH_XYZ_Disable			=(uint8_t)0x00,
	LIS3DH_X_Enable				=(uint8_t)0x01,
	LIS3DH_Y_Enable				=(uint8_t)0x02,
	LIS3DH_Z_Enable				=(uint8_t)0x04
}	LIS3DH_XYZ_Status;

//---------CTRL_REG2(LIS3DH_CTRL_REG2)--------------------//

typedef enum
{
	LIS3DH_HP_RESET_FILTER		=(uint8_t)0x00,
	LIS3DH_RSFF					=(uint8_t)0x40,
	LIS3DH_NM					=(uint8_t)0x80,
	LIS3DH_AUTO_RESET_INT		=(uint8_t)0xC0,
	//Hight pass filter cutt off freqency selection
	LIS3DH_HPF_COF_0			=(uint8_t)0x00,//Hight pass filter cutt off freqency selection
	LIS3DH_HPF_COF_1			=(uint8_t)0x10,
	LIS3DH_HPF_COF_2			=(uint8_t)0x20,
	LIS3DH_HPF_COF_3			=(uint8_t)0x30,
	
	LIS3DH_FDS					=(uint8_t)0x08,
	
	LIS3DH_HP_CLICK				=(uint8_t)0x04,
	LIS3DH_HP_IS2				=(uint8_t)0x02,
	LIS3DH_HP_IS1				=(uint8_t)0x01
}	LIS3DH_REG2_Bits;

//---------CTRL_REG3(LIS3DH_CTRL_REG3)--------------------//
typedef enum
{
	LIS3DH_I1_CLICK				=(uint8_t)0x80,  //single click on int 1
	
	LIS3DH_I1_AOI1				=(uint8_t)0x40,
	LIS3DH_I1_AOI2				=(uint8_t)0x20,
	LIS3DH_I1_DRDY1				=(uint8_t)0x10,
	LIS3DH_I1_DRDY2				=(uint8_t)0x08,
	LIS3DH_I1_WTM				=(uint8_t)0x04,
	LIS3DH_I1_OVERRUN			=(uint8_t)0x02
}	LIS3DH_REG3_Bits;

//---------CLICK_CFG(LIS3DH_CLICK_CFG)--------------------//
typedef enum
{
	LIS3DH_ZD					=(uint8_t)0x20,  //enable interrupt double tap-tap on Z axis
	LIS3DH_ZS					=(uint8_t)0x10,  //enable interrupt single tap-tap on Z axis
	
	LIS3DH_YD					=(uint8_t)0x08,  // double tap-tap on Y axis
	LIS3DH_YS					=(uint8_t)0x04,  // single tap-tap on Y axis
	
	LIS3DH_XD					=(uint8_t)0x02,  // double tap-tap on X axis
	LIS3DH_XS					=(uint8_t)0x01  // single tap-tap on X axis
}	LIS3DH_TapMode;
//---------CLICK_SRC(LIS3DH_CLICK_SRC)--------------------//
typedef enum
{
	LIS3DH_IA					=(uint8_t)0x40,  //enable interrupt
	
	LIS3DH_DT_Enable			=(uint8_t)0x20,  //enable interrupt double tap-tap
	
	LIS3DH_ST_Enable			=(uint8_t)0x10,  // enable interrupt single tap-tap
	
	LIS3DH_Sign					=(uint8_t)0x08,  // 0: positive detection, 1: negativ detection
	
	LIS3DH_Z_Tap				=(uint8_t)0x04,  // Z tap-tap detection
	LIS3DH_Y_Tap				=(uint8_t)0x02,  // Y tap-tap detection
	LIS3DH_X_Tap				=(uint8_t)0x01,  // X tap-tap detection
}	LIS3DH_ClickSRC_Bits;

//---------CLICK_THS(LIS3DH_CLICK_THS)--------------------//

//THS6-THS0 (0-127) Threshold value; 1LSB = full scale / 128

//---------TIME_LIMIT(LIS3DH_TIME_LIMIT)--------------------//

//TLI6-TLI0 (0-127) Time limit value; 1LSB = 1/ODR

//---------TIME_LIMIT(LIS3DH_TIME_LATENCY)--------------------//

//TLA7-TLA0 (0-255) Time latency value; 1LSB = 1/ODR

//---------TIME_WINDOW(LIS3DH_TIME_WINDOW)--------------------//
//TW7-TW0 (0-255) Time window value; 1LSB = 1/ODR

//---------CTRL_REG4(LIS3DH_CTRL_REG4)--------------------//
typedef enum
{ 
	LIS3DH_2G					=(uint8_t)0x00,
	LIS3DH_4G					=(uint8_t)0x10,
	LIS3DH_8G					=(uint8_t)0x20,
	LIS3DH_16G					=(uint8_t)0x30
} LIS3DH_Range;

typedef enum
{
	LIS3DH_HR_Enable			=(uint8_t)0x08, //HR- high resolution
	LIS3DH_HR_Disable			=(uint8_t)0x00,
	
	LIS3DH_ST_OFF				=(uint8_t)0x00,
	LIS3DH_ST_0					=(uint8_t)0x02,
	LIS3DH_ST_1					=(uint8_t)0x04,
	
	LIS3DH_SPI_4_WIRE			=(uint8_t)0x00,
	LIS3DH_SPI_3_WIRE			=(uint8_t)0x01,
	
	LIS3DH_BlockDataUpdate		=(uint8_t)0x80, //(0: continous update, 1: output registers not update until MSB and LSB reading
	LIS3DH_BLE					=(uint8_t)0x40 //(0: Data LSB in lower address, 1: data MSB in lower address
} LIS3DH_REG4_Bits;

//---------CTRL_REG5(LIS3DH_CTRL_REG5)--------------------//
//BOOT
typedef enum
{
	LIS3DH_BOOT_NM				=(uint8_t)0x00,
	LIS3DH_REBOOT				=(uint8_t)0x80,
	
	LIS3DH_FIFO_ENABLE			=(uint8_t)0x40,
	
	LIS3DH_LIR_INT1				=(uint8_t)0x08,
	LIS3DH_D4D_INT1				=(uint8_t)0x04
 } LIS3DH_REG5_Bits;

//---------CTRL_REG6(LIS3DH_CTRL_REG6)--------------------//
typedef enum
{
	LIS3DH_I2CLICK_Enable		=(uint8_t)0x80,
	LIS3DH_I2_INT1				=(uint8_t)0x40,
	
	LIS3DH_BOOT_I1				=(uint8_t)0x10,
	
	LIS3DH_H_LACTIVE			=(uint8_t)0x02,
} LIS3DH_REG6_Bits;


/*-----------Registers-----------------------*/
// LIS3DH Register Names, taken from datasheet
typedef enum
{
	LIS3DH_STATUS_REG_AUX 		=(uint8_t)0x07,
	
	LIS3DH_OUT_ADC1_L 			=(uint8_t)0x08,
	LIS3DH_OUT_ADC1_H			=(uint8_t)0x09,
	LIS3DH_OUT_ADC2_L			=(uint8_t)0x0A,
	LIS3DH_OUT_ADC2_H			=(uint8_t)0x0B,
	LIS3DH_OUT_ADC3_L			=(uint8_t)0x0C,
	LIS3DH_OUT_ADC3_H			=(uint8_t)0x0D,
	
	LIS3DH_INTCOUNTER_REG		=(uint8_t)0x0E,
	
	LIS3DH_WHO_AM_I				=(uint8_t)0x0F,
	
	LIS3DH_TEMP_CFG_REG			=(uint8_t)0x1F,
	
	LIS3DH_CTRL_REG1			=(uint8_t)0x20,
	LIS3DH_CTRL_REG2			=(uint8_t)0x21,	
	LIS3DH_CTRL_REG3			=(uint8_t)0x22,
	LIS3DH_CTRL_REG4			=(uint8_t)0x23,
	LIS3DH_CTRL_REG5			=(uint8_t)0x24,
	LIS3DH_CTRL_REG6			=(uint8_t)0x25,
	
	LIS3DH_REFERENCE			=(uint8_t)0x26,
	
	LIS3DH_STATUS_REG2			=(uint8_t)0x27,
	
	LIS3DH_OUT_X_L				=(uint8_t)0x28,
	LIS3DH_OUT_X_H				=(uint8_t)0x29,
	LIS3DH_OUT_Y_L				=(uint8_t)0x2A,
	LIS3DH_OUT_Y_H				=(uint8_t)0x2B, 
	LIS3DH_OUT_Z_L				=(uint8_t)0x2C,
	LIS3DH_OUT_Z_H				=(uint8_t)0x2D,
	
	LIS3DH_FIFO_CTRL_REG		=(uint8_t)0x2E,
	LIS3DH_FIFO_SRC_REG			=(uint8_t)0x2F,
	
	LIS3DH_INT1_CFG				=(uint8_t)0x30,
	LIS3DH_INT1_SOURCE			=(uint8_t)0x31,
	LIS3DH_INT1_THS				=(uint8_t)0x32,
	LIS3DH_INT1_DURATION		=(uint8_t)0x33,
	
	LIS3DH_CLICK_CFG			=(uint8_t)0x38,
	LIS3DH_CLICK_SRC			=(uint8_t)0x39,
	LIS3DH_CLICK_THS			=(uint8_t)0x3A,
	
	LIS3DH_TIME_LIMIT			=(uint8_t)0x3B,
	LIS3DH_TIME_LATENCY			=(uint8_t)0x3C,
	LIS3DH_TIME_WINDOW			=(uint8_t)0x38
} LIS3DH_Reg;

/*Acceleration vector*/
struct vector_a
{
	char X_MSB;
	char X_LSB;

	char Y_MSB;
	char Y_LSB;

	char Z_MSB;
	char Z_LSB;
};

/*Tap-tap Init structure definition*/
struct TapTapInitStruct
{
	unsigned char InteruptPin;   //1: interrupt pin 1; 2: interrupt pin 2;
	LIS3DH_TapMode TapMode;		 //(TapMode): LIS3DH_ZD, LIS3DH_ZS, LIS3DH_YD, LIS3DH_YS, LIS3DH_XD, LIS3DH_XS  
	unsigned char Threshold;	 //(Threshold value) =  Threshold * (full scale / 128);     0<=Threshold<128
	unsigned char TimeLimit;	 //(Time limit value) = TimeLimit * (1/ODR);				0<=TimeLimit<128
	unsigned char TimeLatency;	 //(Time latency value) = TimeLatency * (1/ODR);			0<=TimeLatency<256
	unsigned char TimeWindow;	 //(Time window value) = TimeWindow * (1/ODR);		  		0<=TimeWindow<256
};
//TapMode:
//		LIS3DH_ZD: enable interrupt double tap-tap on Z axis
//		LIS3DH_ZS: enable interrupt single tap-tap on Z axis
//		
//		LIS3DH_YD: double tap-tap on Y axis
//		LIS3DH_YS: single tap-tap on Y axis
//		
//		LIS3DH_XD: double tap-tap on X axis
//		LIS3DH_XS: single tap-tap on X axis

/*------Fnctions-------------------------------*/
//void LIS3DH_SPI_HwConfig(void);
//void LIS3DH_RebootMemory(void);
//LIS3DH_Status LIS3DH_Conf(LIS3DH_ODR ODR, LIS3DH_Range range, LIS3DH_PowerMode power_mode);
//void LIS3DH_EXTI_Enable(void);
//void LIS3DH_EXTI_Disable(void);

//LIS3DH_Status LIS3DH_Tap_Tap_Conf(struct TapTapInitStruct Init);

//void LIS3DH_SPI_CS_Enable(void);
//void LIS3DH_SPI_CS_Disable(void);

//void LIS3DH_ReadRegister(char addr, char *v);
//void LIS3DH_WriteRegister(char addr, char v);

//void LIS3DH_GetAcc_8_bits(char * x, char * y, char * z);
//void LIS3DH_GetAcc_16_bits(uint8_t *vect, uint8_t* sum);
//void LIS3DH_GetAccVect(struct vector_a * V);

//void EXTI9_5_IRQHandler(void);





#endif
