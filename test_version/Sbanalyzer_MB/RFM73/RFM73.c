
#include "RFM73.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
//#include "USART.h"
#include <stddef.h>



static uint32_t TimingDelay;
// ***********************************************
// 		sending to RFM73 MSB first
// **********************************************/

//Banks1 registers which must be writen
//0-8;	Byte(MSB->LSB), Bit(MSB->LSB)
const unsigned char Bank1_Reg00[]={0x40,0x4B,0x01,0xE2};
const unsigned char Bank1_Reg01[]={0xC0,0x4B,0x00,0x00};
const unsigned char Bank1_Reg02[]={0xD0,0xFC,0x8C,0x02};
const unsigned char Bank1_Reg03[]={0x99,0x00,0x39,0x41};
const unsigned char Bank1_Reg04[]={0xD9,0xB6,0x82,0x1B};	//{0xD9,0x9E,0x86,0x0B};
const unsigned char Bank1_Reg05[]={0x24,0x06,0x7F,0xA6};
//12-14;	Byte(LSB->MSB), Bit(MSB->LSB)
const unsigned char Bank1_Reg0C[]={0x00,0x12,0x73,0x05};
const unsigned char Bank1_Reg0D[]={0x36,0xB4,0x80,0x00};
const unsigned char Bank1_Reg0E[]={0x41,0x10,0x04,0x82,0x20,0x08,0x08,0xF2,0x7D,0xEF,0xFF};

//Initializing values of Bank0 registres
const unsigned char Bank0_Reg[][2]={
{0x00,0x3F},//	0CONFIG	//	reflect RX_DR\TX_DS\MAX_RT,Enable CRC ,2byte,POWER UP,PRX
{0x01,0x3F},//	1EN_AA		//	Enable auto acknowledgement data pipe5\4\3\2\1\0
{0x02,0x3F},//	2EX_RXADDR	//	Enable RX Addresses pipe5\4\3\2\1\0
{0x03,0x03},//	3SETUP_AW	//RX/TX address field width 5byte
{0x04,0x0f},//	4SETUP_RETR	//auto retransmission dalay (250us),auto retransmission count(15)
{0x05,0x17},//	5RF_CH	//	23 channel
{0x06,0x27},//	6RF_SETUP	//air data rate-250k,out power 5dbm,setup LNA gain
{0x07,0x07},//	7STATUS	//
{0x08,0x00},//	8OBSERVER_TX	//
{0x09,0x00},//	9CD	//
{0x0C,0xc3},//	10RX_ADDR_P2	//	only LSB Receive address data pipe 2, MSB bytes is equal to RX_ADDR_P1[39:8]
{0x0D,0xc4},//	11RX_ADDR_P3	//	only LSB Receive address data pipe 3, MSB bytes is equal to RX_ADDR_P1[39:8]
{0x0E,0xc5},//	12RX_ADDR_P4	//	only LSB Receive address data pipe 4, MSB bytes is equal to RX_ADDR_P1[39:8]
{0x0F,0xc6},//	13RX_ADDR_P5	//	only LSB Receive address data pipe 5, MSB bytes is equal to RX_ADDR_P1[39:8]
{0x11,0x20},//	14RX_PW_P0	//	Number of bytes in RX payload in data pipe0(32 byte) 
{0x12,0x20},//	15RX_PW_P1	//	Number of bytes in RX payload in data pipe1(32 byte)
{0x13,0x20},//	16RX_PW_P2	//	Number of bytes in RX payload in data pipe2(32 byte)
{0x14,0x20},//	17RX_PW_P3	//	Number of bytes in RX payload in data pipe3(32 byte)
{0x15,0x20},//	18RX_PW_P4	//	Number of bytes in RX payload in data pipe4(32 byte)
{0x16,0x20},//	19RX_PW_P5	//	Number of bytes in RX payload in data pipe5(32 byte)
{0x17,0x00},//	20FIFO_STATUS	//	fifo status
{0x1C,0x3F},//	21DYNPD	//	Enable dynamic payload length data pipe5\4\3\2\1\0
{0x1D,0x07}//	22FEATURE	//	Enables Dynamic Payload Length,Enables Payload with ACK,Enables the W_TX_PAYLOAD_NOACK command 
};
//Address = Bank1_Reg0A pipe 0 & Bank1_Reg0B pipe 1; in Bank 0
const unsigned char RX0_Address[]={0xE7,0xE7,0xE7,0xE7,0xE7};//Receive address data pipe 0	-> default value
const unsigned char RX1_Address[]={0xC2,0xC2,0xC2,0xC2,0xC2};//Receive address data pipe 1 -> default value

/*******************************************************************/
/*******************************************************************/

extern unsigned char rx_buf[MAX_PACKET_LEN];

//extern void delay_200ms(void);
//extern void delay_50ms(void);

unsigned char status;

// **************************************************
// Function: SPI_R/W(void);
// **************************************************/
unsigned char SPI_R(void)
{
//	while (SPI_GetFlagStatus(SPI_FLAG_TXE)== RESET) {}	// wait until TX buffer will be empty
	while (SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)== RESET) {}	// wait until TX buffer will be empty
	SPI_I2S_SendData(SPI1,0);																		// Send no data - to read the value from register
	while (SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_BSY) == SET) {}		// wait until SPI is ready
	while (SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE)== RESET) {}	// wait until Rx buffer will be ready to read
	
	return(SPI_I2S_ReceiveData(SPI1));
}
void SPI_W(unsigned char value)	// OK
{
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}		// wait until SPI is ready
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE)== RESET) {}	// wait until TX buffer will be empty
	status=0;
	
	SPI_I2S_SendData(SPI1, value);																// Write the read register command
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}		// wait until SPI is ready
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE)== RESET) {}	// wait until Rx buffer will be ready to read
	status=SPI_I2S_ReceiveData(SPI1);														// Read the status register
}

/**************************************************         
Function: RFM73_CSN_Low(); RFM73_CSN_High();                                  
**************************************************/
void RFM73_CSN_Low(void)
{
	GPIO_ResetBits(RFM73_SPI_GPIO, RFM73_SS);
}
void RFM73_CSN_High(void)
{
	GPIO_SetBits(RFM73_SPI_GPIO, RFM73_SS);
}

/**************************************************         
Function: RFM73_CE_Low(); RFM73_CE_High();                                  
**************************************************/
void RFM73_CE_Low(void){	GPIO_ResetBits(RFM73_PWR_Port, RFM73_CE);}
void RFM73_CE_High(void){	GPIO_SetBits(RFM73_PWR_Port, RFM73_CE);}

void SPI_Command(RFM73_Commands_TypeDef cmd)
{
	RFM73_CSN_Low();	// RFM73_CSN low, init SPI transaction
	SPI_W(cmd);	// Do cmd
	RFM73_CSN_High();	// RFM73_CSN high again, end SPI transaction
}
/**************************************************         
Function: SPI_Write_Reg();                                  
 
Description:                                                
	Writes value 'value' to register 'reg'              
**************************************************/
void SPI_Write_Reg(RFM73_RWReg_TypeDef write,RFM73_RegAddr_TypeDef addr, unsigned char value)
{
	RFM73_CSN_Low();	// RFM73_CSN low, init SPI transaction
	SPI_W(write|addr);	// select register
	SPI_W(value);	// ..and write value to it..
	RFM73_CSN_High();	// RFM73_CSN high again, end SPI transaction
}

/**************************************************         
Function: SPI_Read_Reg();                                   
 
Description:                                                
	Read one unsigned char from RFM73 register, 'reg'           
**************************************************/
unsigned char SPI_Read_Reg(RFM73_RegAddr_TypeDef addr)                               
{                                                           
	unsigned char value;
	
	RFM73_CSN_Low();	// RFM73_CSN low, initialize SPI transaction     
	SPI_W(addr);	// Select register to read from.   		
	value = SPI_R();	// ..then read register value 					 
	RFM73_CSN_High();	// RFM73_CSN high, terminate SPI communication

	return(value);	// return register value
}                                                           
/**************************************************/        

/**************************************************         
Function: SPI_Read_Buf();                                   
 
Description:                                                
	Reads 'length' #of length from register 'reg'         
**************************************************/
void SPI_Read_Buf(unsigned char reg, unsigned char *pBuf, unsigned char length)     
{                                                           
	unsigned char byte_ctr;

	RFM73_CSN_Low();	
	SPI_W(reg);	// Select register to write, and read status unsigned char
	for(byte_ctr=0;byte_ctr<length;byte_ctr++)              
		pBuf[byte_ctr] = SPI_R();	// Perform SPI_RW to read unsigned char from RFM73 
	RFM73_CSN_High();	// Set RFM73_CSN high again
}                                                           
/**************************************************/        

/**************************************************         
Function: SPI_Write_Buf();                                  

Description:                                                
	Writes contents of buffer '*pBuf' to RFM73         
**************************************************/
void SPI_Write_Buf(RFM73_RWReg_TypeDef RW,RFM73_RegAddr_TypeDef addr, unsigned char *pBuf, unsigned char length)    
{                                                           
	unsigned char byte_ctr;                                

	RFM73_CSN_Low();	// Set RFM73_CSN low, init SPI tranaction   
	SPI_W(RW|addr);	// Select register to write to and read status unsigned char
	for(byte_ctr=0; byte_ctr<length; byte_ctr++) // then write all unsigned char in buffer(*pBuf) 
		SPI_W(*pBuf++);                
	RFM73_CSN_High();	// Set RFM73_CSN high again
	     
}

/**************************************************
Function: SPI_Activate(RFM_CommandsW_Typedef activate);
Description:
	Change the bank0<->bank1
**************************************************/
void SPI_Activate(RFM73_CommandsW_Typedef activate, unsigned char cmd)
{
	RFM73_CSN_Low();
	SPI_W(activate);
	SPI_W(cmd);
	RFM73_CSN_High();
}
/***********INITIALIZE FUNCTIONS***************************

**************************************************
Function: SPI_Read_Buf();                                   
 
Description:                                                
	Reads 'length' #of length from register 'reg'         
**************************************************/
void SPI_Read_Ini_Buf(unsigned char reg, unsigned char *pBuf, unsigned char length)     
{                                                           
	unsigned char byte_ctr;

	RFM73_CSN_Low();	
	SPI_W(reg);	// Select register to write, and read status unsigned char
	for(byte_ctr=0;byte_ctr<length;byte_ctr++)              
		pBuf[byte_ctr] = SPI_R();	// Perform SPI_RW to read unsigned char from RFM73 
	RFM73_CSN_High();	// Set RFM73_CSN high again
}                                                           
/**************************************************/        

/**************************************************         
Function: SPI_Write_Ini_Buf();                                  

Description:                                                
	Writes contents of buffer '*pBuf' to RFM73         
*************************************************/
void SPI_Write_Ini_Buf(RFM73_RWReg_TypeDef RW,RFM73_RegAddr1_TypeDef addr, unsigned char *pBuf, unsigned char length)    
{                                                           
	unsigned char byte_ctr;                                

	RFM73_CSN_Low();	// Set RFM73_CSN low, init SPI tranaction   
	SPI_W(RW|addr);	// Select register to write to and read status unsigned char
	for(byte_ctr=0; byte_ctr<length; byte_ctr++) // then write all unsigned char in buffer(*pBuf) 
		SPI_W(*pBuf++);                
	RFM73_CSN_High();	// Set RFM73_CSN high again
	     
}

/**************************************************
Function: SwitchToRxMode();
Description:
	switch to Rx mode
**************************************************/
void RFM73_SwitchToRxMode()
{
	unsigned char value;

	SPI_Command(FLUSH_RX);//flush Rx
//	RFM73_CE_Low();
	value=SPI_Read_Reg(STATUS);	// read register STATUS's value
	SPI_Write_Reg(WRITE_REG,STATUS,value);// clear RX_DR or TX_DS or MAX_RT interrupt flag
	RFM73_CE_Low();
	value=SPI_Read_Reg(CONFIG);	// read register CONFIG's value
//PRX
	value=value|0x01;
  	SPI_Write_Reg(WRITE_REG, CONFIG, value); // Set PWR_UP bit, enable CRC(2 length) & Prim:RX. RX_DR enabled..
	RFM73_CE_High();
}

/**************************************************
Function: RFM73_SwitchToTxMode();
Description:
	switch to Tx mode
**************************************************/
void RFM73_SwitchToTxMode()
{
	unsigned char value;
	SPI_Command(FLUSH_TX);//flush Tx
	RFM73_CE_Low();
	value=SPI_Read_Reg(CONFIG);	// read register CONFIG's value
//PTX
		value=value&0xfe;	//	mask all bits without first / switch to PTX
  	SPI_Write_Reg(WRITE_REG, CONFIG, value); // Set PWR_UP bit, enable CRC(2 length) & Prim:RX. RX_DR enabled.
	Delay(2);
	RFM73_CE_High();
	Delay(2);
}

/**************************************************
Function: SwitchCFG();
                                                            
Description:
	 access switch between Bank1 and Bank0 

Parameter:
	_cfg      1:register bank1
	          0:register bank0
Return:
     None
**************************************************/
void SwitchCFG(char _cfg)//1:Bank1 0:Bank0
{
	unsigned char Tmp;

	Tmp=SPI_Read_Reg(STATUS);	//Read the STATUS register
	Tmp=Tmp&0x80;	//Mask only the RBANK bit
	if( ( (Tmp)&&(_cfg==0) )
	||( ((Tmp)==0)&&(_cfg) ) )	//If bank isn't the same that is required, change it
	{
		SPI_Activate(ACTIVATE_CMD, 0x53);	//sending the required command
	}
}

/**************************************************
Function: SetChannelNum();
Description:
	set channel number

**************************************************/
void SetChannelNum(unsigned char channel)
{
	SPI_Write_Reg(WRITE_REG,RF_CH,channel);	// Write the channel number which works on the RFM73
}

/**************************************************
Function: Send_Packet
Description:
	fill FIFO to send a packet
Parameter:
	type: WR_TX_PLOAD or  W_TX_PAYLOAD_NOACK_CMD
	pbuf: a buffer pointer
	len: packet length
Return:
	None
**************************************************/
void Send_Packet(RFM73_TRx_TypeDef type,unsigned char* pbuf,unsigned char len)
{
	unsigned char fifo_sta;
	
	fifo_sta=SPI_Read_Reg(FIFO_STATUS);	// read register FIFO_STATUS's value
	if((fifo_sta&FIFO_STATUS_TX_FULL)==0)//if not full, send data (write buff)
	{ 
		SPI_Write_Buf(WRITE_REG, type, pbuf, len); // Writes data to buffer
	}	  	 	
}

/**************************************************
Function: Receive_Packet
Description:
	read FIFO to read a packet
Parameter:
	None
Return:
	None
**************************************************/

void Receive_Packet(unsigned char *rx_buf, unsigned char *len)
{
	unsigned char i,sta,fifo_sta;
	//unsigned char rx_buf[MAX_PACKET_LEN];
	for(i = 0; i < MAX_PACKET_LEN ; i++)rx_buf[i] = 0;	// writing zeros to rx_buf
	sta=SPI_Read_Reg(STATUS);	// read register STATUS's value

	if((STATUS_RX_DR&sta) == 0x40)				// if receive data ready (RX_DR) interrupt
	{
		do
		{
			*len=SPI_Read_Reg((RFM73_RegAddr_TypeDef)R_RX_PL_WID_CMD);	// read length of recived packet

			if(*len<=MAX_PACKET_LEN)
			{
				SPI_Read_Buf(RD_RX_PLOAD, rx_buf, *len);// read receive payload from RX_FIFO buffer
			}
			else
			{
				SPI_Command(FLUSH_RX);	//	bad data reviced - flush Rx
			}

			fifo_sta=SPI_Read_Reg(FIFO_STATUS);	// read register FIFO_STATUS's value

		}while((fifo_sta&FIFO_STATUS_RX_EMPTY)==0); //while not empty
	}
	SPI_Write_Reg(WRITE_REG, STATUS, sta);// clear RX_DR or TX_DS or MAX_RT interrupt flag
}

void Ini_Bank0()
{
	unsigned char i, j;	// j-counter, i-variable
 	unsigned char WriteArr[12];
	//unsigned char rx_buf_test[MAX_PACKET_LEN];
	
	SwitchCFG(0);	//switch to bank0
	
	for(j=0;j<23;j++)	//initialize RFM73 - REGISTERS
	{
		SPI_Write_Reg(WRITE_REG, Bank0_Reg[j][0], Bank0_Reg[j][1]);
	}
	
	for(j=0;j<5;j++)	//initialize RFM73 - PIPES (RX0)
	{
		WriteArr[j]=RX0_Address[j];
	}
	SPI_Write_Buf(WRITE_REG, RX_ADDR_P0, &(WriteArr[0]), 5);
	
	for(j=0;j<5;j++)	//initialize RFM73 - PIPES (RX1)
	{
		WriteArr[j]=RX1_Address[j];
	}
	SPI_Write_Buf(WRITE_REG, RX_ADDR_P1, &(WriteArr[0]), 5);
	
	for(j=0;j<5;j++)	// initialize RFM73 - TX_ADDR
	{
		WriteArr[j]=RX0_Address[j];
	}
	SPI_Write_Buf(WRITE_REG, TX_ADDR, &(WriteArr[0]), 5);
	
	i=SPI_Read_Reg(FEATURE);
	if(i==0) // i!=0 showed that chip has been actived.so do not active again.
		SPI_Activate(ACTIVATE_CMD,0x73); // Activate
	for(j=22;j>=21;j--)
	{
		SPI_Write_Reg(WRITE_REG, Bank0_Reg[j][0], Bank0_Reg[j][1]); // Reinitialize the start value of DYNPD and FEATURE
	}
}
void Ini_Bank1()
{
	unsigned char j;
 	unsigned char WriteArr[12];
	
	SwitchCFG(1);
//	reg:00
	for(j=0; j<4; j++)
	{
		WriteArr[j]=Bank1_Reg00[j];
	}
	SPI_Write_Ini_Buf(WRITE_REG, A_00, &(WriteArr[0]),4);
//	reg:01
	for(j=0; j<4; j++)
	{
		WriteArr[j]=Bank1_Reg01[j];
	}
	SPI_Write_Ini_Buf(WRITE_REG, A_01, &(WriteArr[0]),4);
//	reg:02
	for(j=0; j<4; j++)
	{
		WriteArr[j]=Bank1_Reg02[j];
	}
	SPI_Write_Ini_Buf(WRITE_REG, A_02, &(WriteArr[0]),4);
//	reg:03
	for(j=0; j<4; j++)
	{
		WriteArr[j]=Bank1_Reg03[j];
	}
	SPI_Write_Ini_Buf(WRITE_REG, A_03, &(WriteArr[0]),4);
//	reg:04
	for(j=0; j<4; j++)
	{
		WriteArr[j]=Bank1_Reg04[j];
	}
	SPI_Write_Ini_Buf(WRITE_REG, A_04, &(WriteArr[0]),4);
//	reg:05
	for(j=0; j<4; j++)
	{
		WriteArr[j]=Bank1_Reg05[j];
	}
	SPI_Write_Ini_Buf(WRITE_REG, A_05, &(WriteArr[0]),4);
//	reg:0C
	for(j=0; j<4; j++)
	{
		WriteArr[j]=Bank1_Reg0C[j];
	}
	SPI_Write_Ini_Buf(WRITE_REG, A_0C, &(WriteArr[0]),4);
//	reg:0D
	for(j=0; j<4; j++)
	{
		WriteArr[j]=Bank1_Reg0D[j];
	}
	SPI_Write_Ini_Buf(WRITE_REG, A_0D, &(WriteArr[0]),4);
//	reg:0E
	for(j=0; j<11; j++)
	{
		WriteArr[j]=Bank1_Reg0E[j];
	}
	SPI_Write_Ini_Buf(WRITE_REG, A_0E, &(WriteArr[0]),11);
}
/**************************************************/   
char RFM73_Initialize()
{
	//delay_200ms();	//delay more than 50ms.
	Delay(200);
    Ini_Bank0();
	Ini_Bank1();	
	//delay_50ms();
	Delay(50);
	SwitchCFG(1);
	if(SPI_Read_Reg(RFM73_ID_Reg)!= RFM73_ID) return RFM73_ERROR;
	SwitchCFG(0);	//switch back to Bank0 register access
	return RFM73_OK;
}

/* **************************************************
// Function: SPI_HWConf;
// **************************************************/
void RFM73_SPI_Conf(void)
{ //GPIO and SPI configuration
  GPIO_InitTypeDef  GPIO_InitStructure; 
  SPI_InitTypeDef  SPI_InitStructure;

  //GPIO Config
  GPIO_InitStructure.GPIO_Pin =RFM73_MOSI | RFM73_MISO | RFM73_SCK;    //SPI - SCK, MISO & MOSI
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(RFM73_SPI_GPIO, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = RFM73_SS;      //SPI - SS, CE & PWR
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(RFM73_SPI_GPIO, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = RFM73_CE | RFM73_PWR;      //SPI - SS, CE & PWR
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(RFM73_PWR_Port, &GPIO_InitStructure);

  //SPI Config

  SPI_Cmd(RFM73_SPI, DISABLE);

  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 0;
  SPI_Init(RFM73_SPI, &SPI_InitStructure);
  SPI_CalculateCRC(RFM73_SPI, DISABLE);

  SPI_Cmd(RFM73_SPI, ENABLE);                                         // Wlacz SPI
}

/* **************************************************
// Function: Leds Config
// **************************************************/
//void RFM73_LEDS_Conf(void)
//{
//	GPIO_InitTypeDef GPIO_InitStruct;
//
//	GPIO_InitStruct.GPIO_Pin = RFM73_LED_1  |RFM73_LED_2;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
//	
//	GPIO_Init( RFM73_LEDS, &GPIO_InitStruct );	
//}


/**************************************************         
Function: PWR ON/OFF, Leds                                  
**************************************************/

void RFM73_PowerON(void)
{
	GPIO_SetBits(RFM73_PWR_Port, RFM73_PWR);
	//RFM73_SPI_GPIO->BSRR = RFM73_PWR;
}

void RFM73_PowerOFF(void)
{
	GPIO_ResetBits(RFM73_PWR_Port, RFM73_PWR);
	//RFM73_SPI_GPIO->BRR = RFM73_PWR;
}

//void LED_1_ON(void)
//{
//	RFM73_LEDS->BSRR = RFM73_LED_1;
//}
//
//void LED_1_OFF(void)
//{
//	RFM73_LEDS->BRR = RFM73_LED_1;
//}
//
//void LED_2_ON(void)
//{
//	RFM73_LEDS->BSRR = RFM73_LED_2;
//}
//
//void LED_2_OFF(void)
//{
//	RFM73_LEDS->BRR = RFM73_LED_2;
//}


/**************************************************         
Function: Delay();                                  

**************************************************/

void Delay(unsigned long int nTime)
{ 
  TimingDelay = nTime;
  //USART1_SendText("Delay\n\r");
  while(TimingDelay != 0);
}

void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

void RFM73_EXTI_Enable(void)
{
	/* Private variables */
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
//	NVIC_InitTypeDef   NVIC_InitStructure;

	/* Configure pin as input floating */
 	GPIO_InitStructure.GPIO_Pin = RFM73_IRQ;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(RFM73_IRQn_Port, &GPIO_InitStructure);

	/* Enable AFIO clock */
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	/* Connect EXTI Line to LIS3DH int. port */
 	GPIO_EXTILineConfig(RFM73_IRQn_PortSource, RFM73_IRQ_Src);

	/* Configure EXTI line */
  	EXTI_InitStructure.EXTI_Line = RFM73_EXTI_Line;
 	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);

//	/* Enable and set EXTI Interrupt to the lowest priority */
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
// 	NVIC_InitStructure.NVIC_IRQChannel = RFM73_IRQn;
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
// 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
// 	NVIC_Init(&NVIC_InitStructure);

}

void RFM73_EXTI_Disable(void)
{
	/* Private variables */
	EXTI_InitTypeDef   EXTI_InitStructure;
//	NVIC_InitTypeDef   NVIC_InitStructure;

	/* Configure EXTI line */
  	EXTI_InitStructure.EXTI_Line = RFM73_EXTI_Line;
 	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
  	EXTI_InitStructure.EXTI_LineCmd = DISABLE;
  	EXTI_Init(&EXTI_InitStructure);

//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//	/* Enable and set EXTI Interrupt to the lowest priority */
// 	NVIC_InitStructure.NVIC_IRQChannel = RFM73_IRQn;
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
// 	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
// 	NVIC_Init(&NVIC_InitStructure);

}
