#include "commands.h"
#include "stdio.h"
#include "rfm73.h"
#include "L3G4200D.h"
#include "LIS3DH.h"
#include "main.h"
#include "stm32f10x_it.h"


//extern unsigned char buforRx[17];
//extern unsigned char buforTx[17];

extern uint32_t measurementTime;
extern uint32_t measurementFreq;

void writeInfoCmdToTxBuffor(GetInfoCommand_s _infoCmd)
{
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
}

CheckCmd infoCommand()
{
//	GetInfoCommand_s cmd;
//	unsigned char _buf[2]= { Info_Cmd, 0x0d };
//	Send_Packet(W_TX_PAYLOAD_NOACK_CMD, _buf, 0x02);
//	
//	cmd.CmdID = Info_Cmd;
//	cmd.LIS3DHFreq = LIS3DH_12500Hz;
//	cmd.LIS3DHRange = LIS3DH_8G;
//	cmd.L3G4200DFreq = L3G4200D_800Hz;
//	cmd.L3g4200DRange = L3G4200D_2000dps;
//	cmd.TimeMSB = 0x03;
//	cmd.TimeLSB = 0x0c;
//	cmd.BatteryLevel = 0x50;
//	cmd.CmdCheckSum = 0x00;

//	if(buforRx[0] == Info_Cmd)
//	{
//		writeInfoCmdToTxBuffor(cmd);
//		return Cmd_OK;
//	}
//	else
//	{
	return Cmd_ERROR;
//	}  
}

CheckCmd confCommand(unsigned char* _buf)
{
	unsigned char _cks = 0;
	unsigned char i = 0;
	ConfCommand_s* _confStruct;
	_confStruct = (ConfCommand_s*) _buf;
	
	for(i = 0; i<ConfCmd_Length; i++)
	{
		_cks += _buf[i];
	}
	if(_cks != _buf[ConfCmd_Length])
		return Cmd_CHECK_SUM_ERROR;
		
 RFM73_to_LIS3DH();
 Delay(200);
 if(LIS3DH_Conf(_confStruct->LIS3DHFreq, _confStruct->LIS3DHRange,LIS3DH_NormalPowerMode) == LIS3DH_ERROR) 
 {
	 LIS3DH_to_RFM73();
	 return Cmd_ERROR;
 }else	LIS3DH_to_RFM73();
 Delay(200);
		
 if(L3G4200D_Conf(_confStruct->L3G4200DFreq, _confStruct->L3G4200DRange) == L3G4200D_ERROR) return Cmd_ERROR;

	measurementTime = _confStruct->TimeMSB;
	measurementTime = measurementTime << 8;
	measurementTime |= _confStruct->TimeLSB;
	
	switch(_confStruct->L3G4200DFreq)
	{
		case L3G4200D_100Hz: //start
		{
				measurementFreq = 100;
		}
		break;
		case L3G4200D_200Hz: //start
		{
				measurementFreq = 200;
		}
		break;
		case L3G4200D_400Hz: //start
		{
				measurementFreq = 400;
		}
		break;
		case L3G4200D_800Hz: //start
		{
				measurementFreq = 800;
		}
		break;	
	}
	
	return Cmd_OK; 
}

void acceptedCmd(void)
{
	unsigned char _buf[4];
	_buf[0] = 'A';
	_buf[1] = 'C';
	_buf[2] = 'K';
	_buf[3] = 0x0d;
	Send_Packet(W_TX_PAYLOAD_NOACK_CMD, _buf, 0x04);
}

void noAcceptedCmd(void)
{
	unsigned char _buf[5];
	
	_buf[0] = 'N';
	_buf[1] = 'A';
	_buf[2] = 'C';
	_buf[3] = 'K';
	_buf[4] = 0x0d;
	Send_Packet(W_TX_PAYLOAD_NOACK_CMD, _buf, 0x05);
}
