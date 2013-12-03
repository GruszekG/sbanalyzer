#include "commands.h"
#include "memsSettings.h"
#include "stdio.h"
#include "rfm73.h"
#include "usart.h"


extern unsigned char buforRx[17];
extern unsigned char buforTx[17];

extern unsigned char buforRxRFM73[17];
extern unsigned char buforTxRFM73[17];




//void writeInfoCmdToTxBuffor(GetInfoCommand_s _infoCmd)
//{
//	unsigned int i = 0;
//	buforTx[0] = _infoCmd.CmdID;
//	buforTx[1] = _infoCmd.LIS3DHFreq;
//	buforTx[2] = _infoCmd.LIS3DHRange;
//	buforTx[3] = _infoCmd.L3G4200DFreq;
//	buforTx[4] = _infoCmd.L3g4200DRange;
//	buforTx[5] = _infoCmd.TimeMSB;
//	buforTx[6] = _infoCmd.TimeLSB;
//	buforTx[7] = _infoCmd.BatteryLevel;

//	buforTx[8] = 0;

//	for(i = 0; i<InfoCmd_Length; i++)
//	{
//		buforTx[8] += buforTx[i]; 
//	}
//	buforTx[9] = 0x0d; //'stop' byte	
//}

CheckCmd infoCommand(unsigned char *_buf)
{
	unsigned int i;
	unsigned char checkSum =  0;
	
	for( i = 0; i < 8; i++)
	{
				checkSum += _buf[i];
	}
	if(checkSum != _buf[8])
		return Cmd_ERROR;
		
	if(0x0d != _buf[9])
		return Cmd_ERROR;
		
	USART1_SendBuf(_buf, 10);
	
	return Cmd_OK;
}

CheckCmd startCommand()
{
	unsigned char _buf[2]= { Measure_Cmd, 0x0d };

	if(buforRx[0] != Measure_Cmd) return Cmd_ID_ERROR;
	else if(buforRx[2] != (buforRx[0]+buforRx[1])) return Cmd_CHECK_SUM_ERROR;
	else
	{
		Send_Packet(W_TX_PAYLOAD_NOACK_CMD, _buf, 0x02);				
	}
	return Cmd_OK;
}

CheckCmd confCommand()
{
	unsigned char _cks = 0;
	unsigned char i = 0;
	
	_cks += buforRx[0];
	for(i = 1; i<ConfCmd_Length; i++)
	{
	//	buforRx[i] = buforRx[i];
		//buforRx[i] = ~buforRx[i];
		_cks += buforRx[i];
	}
	//if(_cks != buforRx[ConfCmd_Length])
	//	return Cmd_CHECK_SUM_ERROR;
		
	Send_Packet(W_TX_PAYLOAD_NOACK_CMD, buforRx, ConfCmd_Length + 1);

	return Cmd_OK; 
}

void acceptedCmd(void)
{

	buforTx[0] = 'A';
	buforTx[1] = 'C';
	buforTx[2] = 'K';
	buforTx[3] = 0x0d;
	buforTx[4] = 0;
	
	USART1_SendText(buforTx);
}

void noAcceptedCmd(void)
{
	buforTx[0] = 'N';
	buforTx[1] = 'A';
	buforTx[2] = 'C';
	buforTx[3] = 'K';
	buforTx[4] = 0x0d;
	
	USART1_SendText(buforTx);
}
