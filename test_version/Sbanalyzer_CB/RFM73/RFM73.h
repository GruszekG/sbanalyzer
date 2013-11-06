

#ifndef _RFM73_H
#define _RFM73_H

#include <stdio.h>
#include <stdarg.h>
#include <string.h>


#define TRANS_OK		  				0xFF
#define TRANS_ERROR						0xF0
#define TRANS_START						0x53	   //'S'
//definicje pinów do komunikacji z RFM73
#define RFM73_SPI  SPI1
#define RFM73_SPI_GPIO GPIOA     //RFM73 GPIO port for SPI
                                
#define RFM73_CE  GPIO_Pin_2    //SPI CE
#define RFM73_IRQ  GPIO_Pin_3    //SPI IRQ
#define RFM73_SS   GPIO_Pin_4    //SPI SS
#define RFM73_SCK  GPIO_Pin_5    //SPI SCK
#define RFM73_MISO GPIO_Pin_6    //SPI MISO
#define RFM73_MOSI GPIO_Pin_7    //SPI MOSI

#define RFM73_PWR   GPIO_Pin_1    //SPI power PWR

#define RFM73_LEDS GPIOB     //RFM73 GPIO port for LEDS
#define RFM73_LED_1 GPIO_Pin_0
#define RFM73_LED_2 GPIO_Pin_1

//definicje do IRQ
#define RFM73_IRQ_Src  GPIO_PinSource3
#define RFM73_EXTI_Line  EXTI_Line3
#define RFM73_IRQn	EXTI3_IRQn

#define RFM73_IRQn_Port	GPIOA
#define RFM73_IRQn_PortSource	GPIO_PortSourceGPIOA


#define MAX_PACKET_LEN  32// max value is 32

#define RFM73_ID 0x63
#define RFM73_ID_Reg 0x08

#define RFM73_ERROR 0x01
#define RFM73_OK	0x00
//************************FSK COMMAND and REGISTER****************************************//


// SPI(RFM73) commands
typedef enum {
	RD_RX_PLOAD							=	(unsigned char)0x61,  // Define RX payload register address
	WR_TX_PLOAD							=	(unsigned char)0xA0,  // Define TX payload register address
	FLUSH_TX								=	(unsigned char)0xE1,  // Define flush TX register command
	FLUSH_RX								=	(unsigned char)0xE2,  // Define flush RX register command
	REUSE_TX_PL							=	(unsigned char)0xE3,  // Define reuse TX payload register command
	NOP_NOP									=	(unsigned char)0xFF  // Define No Operation, might be used to read status register
}	RFM73_Commands_TypeDef;

typedef enum {
	W_TX_PAYLOAD_NOACK_CMD	=	(unsigned char)0xb0,
	W_ACK_PAYLOAD_CMD				=	(unsigned char)0xa8,
	R_RX_PL_WID_CMD					=	(unsigned char)0x60
}	RFM73_TRx_TypeDef;

typedef enum {
	ACTIVATE_CMD						=	(unsigned char)0x50
}	RFM73_CommandsW_Typedef;
typedef enum {
	READ_REG								= (unsigned char)0x00,  // Define read command to register
	WRITE_REG								=	(unsigned char)0x20  // Define write command to register
} RFM73_RWReg_TypeDef;

// SPI(RFM73) registers(addresses)
typedef enum {
 CONFIG				=	(unsigned char)0x00,  // 'Config' register address
 EN_AA				=	(unsigned char)0x01,  // 'Enable Auto Acknowledgment' register address
 EN_RXADDR		=	(unsigned char)0x02,  // 'Enabled RX addresses' register address
 SETUP_AW			=	(unsigned char)0x03,  // 'Setup address width' register address
 SETUP_RETR		=	(unsigned char)0x04,  // 'Setup Auto. Retrans' register address
 RF_CH				=	(unsigned char)0x05,  // 'RF channel' register address
 RF_SETUP			=	(unsigned char)0x06,  // 'RF setup' register address
 STATUS				=	(unsigned char)0x07,  // 'Status' register address
 OBSERVE_TX		=	(unsigned char)0x08,  // 'Observe TX' register address
 CD						=	(unsigned char)0x09,  // 'Carrier Detect' register address
 RX_ADDR_P0		=	(unsigned char)0x0A,  // 'RX address pipe0' register address
 RX_ADDR_P1		=	(unsigned char)0x0B,  // 'RX address pipe1' register address
 RX_ADDR_P2		=	(unsigned char)0x0C,  // 'RX address pipe2' register address
 RX_ADDR_P3		=	(unsigned char)0x0D,  // 'RX address pipe3' register address
 RX_ADDR_P4		=	(unsigned char)0x0E,  // 'RX address pipe4' register address
 RX_ADDR_P5		=	(unsigned char)0x0F,  // 'RX address pipe5' register address
 TX_ADDR			=	(unsigned char)0x10,  // 'TX address' register address
 RX_PW_P0			=	(unsigned char)0x11,  // 'RX payload width, pipe0' register address
 RX_PW_P1			=	(unsigned char)0x12,  // 'RX payload width, pipe1' register address
 RX_PW_P2			=	(unsigned char)0x13,  // 'RX payload width, pipe2' register address
 RX_PW_P3			=	(unsigned char)0x14,  // 'RX payload width, pipe3' register address
 RX_PW_P4			=	(unsigned char)0x15,  // 'RX payload width, pipe4' register address
 RX_PW_P5			=	(unsigned char)0x16,  // 'RX payload width, pipe5' register address
 FIFO_STATUS	=	(unsigned char)0x17,  // 'FIFO Status Register' register address
 FEATURE			=	(unsigned char)0x1D,	 // 'FEATURE register address
 PAYLOAD_WIDTH=	(unsigned char)0x1f  // 'payload length of 256 bytes modes register address
}	RFM73_RegAddr_TypeDef;

typedef enum {
	A_00	=	(unsigned char)0x00,
	A_01	=	(unsigned char)0x01,
	A_02	=	(unsigned char)0x02,
	A_03	=	(unsigned char)0x03,
	A_04	=	(unsigned char)0x04,
	A_05	=	(unsigned char)0x05,
	A_0C	=	(unsigned char)0x0C,
	A_0D	=	(unsigned char)0x0D,
	A_0E	=	(unsigned char)0x0E
} RFM73_RegAddr1_TypeDef;	

//interrupt status
typedef enum {
	STATUS_RX_DR 	= 	(unsigned char)0x40,
	STATUS_TX_DS 	=		(unsigned char)0x20,
	STATUS_MAX_RT =		(unsigned char)0x10,
	STATUS_TX_FULL =	(unsigned char)0x01
} RFM73_IrqStat_TypeDef;

//FIFO_STATUS
typedef enum {
FIFO_STATUS_TX_REUSE = 	(unsigned char)0x40,
FIFO_STATUS_TX_FULL = 	(unsigned char)0x20,
FIFO_STATUS_TX_EMPTY = 	(unsigned char)0x10,

FIFO_STATUS_RX_FULL = 	(unsigned char)0x02,
FIFO_STATUS_RX_EMPTY = 	(unsigned char)0x01
}	RFM73_FifoStat_Typedef;

/*****************************

	 FUNCTION DECLARATION

****************************/

void SPI_Read_Buf(unsigned char reg, unsigned char *pBuf, unsigned char bytes);
void SPI_Write_Buf(RFM73_RWReg_TypeDef RW,RFM73_RegAddr_TypeDef addr, unsigned char *pBuf, unsigned char length);

unsigned char SPI_Read_Reg(RFM73_RegAddr_TypeDef addr);
void SPI_Write_Reg(RFM73_RWReg_TypeDef RW,RFM73_RegAddr_TypeDef addr, unsigned char value);

void SPI_Command(RFM73_Commands_TypeDef cmd);

void RFM73_SwitchToTxMode(void);
void RFM73_SwitchToRxMode(void);

void SPI_Bank1_Read_Reg(unsigned char reg, unsigned char *pBuf);
void SPI_Bank1_Write_Reg(unsigned char reg, unsigned char *pBuf);
void SwitchCFG(char _cfg);

void CSN_Low(void);
void CSN_High(void);
void CE_Low(void);
void CE_High(void);

char RFM73_Initialize(void);

unsigned char Send_Packet(RFM73_TRx_TypeDef type,unsigned char* pbuf,unsigned char len);
void Receive_Packet(unsigned char *rx_buf, unsigned char *len);


// Banks initialize
void Ini_Bank0(void);
void Ini_Bank1(void);

void RFM73_SPI_Conf(void);
void RFM73_LEDS_Conf(void);

//void RFM73_CSN_Low(void);//
//void RFM73_CSN_High(void);//
//void RFM73_CE_Low(void);//
//void RFM73_CE_High(void);//
void RFM73_PowerON(void);//
void RFM73_PowerOFF(void);//
void LED_1_ON(void);//
void LED_1_OFF(void);//
void LED_2_ON(void);//
void LED_2_OFF(void);//
void LED_1_Change(void);
void LED_2_Change(void);

void RFM73_EXTI_Enable(void);
void RFM73_EXTI_Disable(void);

void Delay(unsigned long int nTime);//
void TimingDelay_Decrement(void);//

#endif
