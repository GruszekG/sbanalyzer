
#ifndef _MEMS_SETTINGS_H
#define _MEMS_SETTINGS_H

//--------------------------------------------------------//
//-----------LIS3DH SETTINGS------------------------------//
//--------------------------------------------------------//

typedef enum
{
	LIS3DH_PDM 						=(unsigned char)0x00,//Power down mode(ODR = 0)
	LIS3DH_1Hz						=(unsigned char)0x10,
	LIS3DH_10Hz						=(unsigned char)0x20,
	LIS3DH_25Hz						=(unsigned char)0x30,
	LIS3DH_50Hz						=(unsigned char)0x40,
	LIS3DH_100Hz					=(unsigned char)0x50,
	LIS3DH_200Hz					=(unsigned char)0x60,
	LIS3DH_400Hz					=(unsigned char)0x70,
	LIS3DH_LP_1600Hz			=(unsigned char)0x88, //Low power mode
	LIS3DH_12500Hz				=(unsigned char)0x90, //Normal power mode
	LIS3DH_LP_5kHz				=(unsigned char)0x98 //Low power mode
}	LIS3DH_ODR;

typedef enum
{ 
	LIS3DH_2G						=(unsigned char)0x00,
	LIS3DH_4G						=(unsigned char)0x10,
	LIS3DH_8G						=(unsigned char)0x20,
	LIS3DH_16G					=(unsigned char)0x30
} LIS3DH_Range;


//--------------------------------------------------------//
//-----------L3G4200D SETTINGS----------------------------//
//--------------------------------------------------------//

typedef enum
{
	L3G4200D_100Hz  =(unsigned char)0x00,
	L3G4200D_200Hz  =(unsigned char)0x40,
	L3G4200D_400Hz	=(unsigned char)0x80,
	L3G4200D_800Hz	=(unsigned char)0xC0
}	L3G4200D_ODR;

typedef enum
{
	L3G4200D_250dps		=(unsigned char)0x00,
	L3G4200D_500dps		=(unsigned char)0x10,
	L3G4200D_2000dps	=(unsigned char)0x20 //(0x30)
}	L3G4200D_Range;

#endif
