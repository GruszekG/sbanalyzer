
#ifndef _COMMANDS_H
#define _COMMANDS_H

typedef enum
{
	Cmd_OK = 0,
	Cmd_ID_ERROR,
	Cmd_CHECK_SUM_ERROR,
	Cmd_ERROR

}	CheckCmd;

typedef enum
{
	Measure_Cmd = 0x01,

	Conf_Cmd,

	WriteReg_Cmd,
	ReadReg_Cmd,

	Info_Cmd,

	CmdCount

}	CommandID_t;

typedef enum
{
	SimpleCmd_Length = 0x03,
	WriteReadCmd_Length = 0x05,
	InfoCmd_Length = 0x08,
	ConfCmd_Length = 0x07
		
}	CommandLength_t;

typedef enum
{
	LIS3DH = 0x00,
	L3G4200D,

	DeviceCount

}	Devices_n;

typedef struct
{
	CommandID_t		CmdID;
	unsigned char 	CmdArgument;
	unsigned char	CmdCheckSum;

}	SimpleCommand_s;

typedef struct
{
	CommandID_t		CmdID;
	Devices_n		Device;
	unsigned char 	Register;
	unsigned char	Value;
	unsigned char	CmdCheckSum;

}	WriteRegCommand_s;

typedef struct
{
	CommandID_t		CmdID;
	Devices_n		Device;
	unsigned char 	Register;
	unsigned char	Value;
	unsigned char	CmdCheckSum;

}	ReadRegCommand_s;

typedef struct
{
	CommandID_t		CmdID;
	unsigned char	LIS3DHFreq;
	unsigned char	LIS3DHRange;
	unsigned char	L3G4200DFreq;
	unsigned char	L3g4200DRange;

	unsigned char	TimeMSB;
	unsigned char	TimeLSB;

	unsigned char	BatteryLevel;

	unsigned char	CmdCheckSum;
	unsigned char	EndByte;

}	GetInfoCommand_s;

typedef struct
{
	CommandID_t		CmdID;
	unsigned char	LIS3DHFreq;
	unsigned char	LIS3DHRange;
	unsigned char	L3G4200DFreq;
	unsigned char	L3g4200DRange;

	unsigned char	TimeMSB;
	unsigned char	TimeLSB;

	unsigned char	CmdCheckSum;
	unsigned char	EndByte;

}	ConfCommand_s;

CheckCmd infoCommand(void);

CheckCmd startCommand(void);

CheckCmd confCommand(void);

void acceptedCmd(void);
void noAcceptedCmd(void);

void writeInfoCmdToTxBuffor(GetInfoCommand_s _infoCmd);

#endif
