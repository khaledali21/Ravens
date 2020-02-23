/*
 * test.c
 *
 *  Created on: Oct 4, 2019
 *      Author: mahmo
 */

#include "gps.h"

/* This module prvoides lat, lon, and alt in meters passd by referance
 * please note that alt is meaured from the sea level  not from ground
 */

void gps_init()
{
	// first init the uart at 9600

	u8 gps_init_9600[37]= {0xB5, 0x62, 0x06, 0x00, 0x14, 0x00, 0x01, 0x00, 0x00, 0x00, 0xD0, 0x08, 0x00, 0x00, 0x00, 0xC2, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB8, 0x42, 0xB5, 0x62, 0x06, 0x00, 0x01, 0x00, 0x01, 0x08, 0x22};
	u8 i =0;
	UART1_init(103);
	for (u8 i=0 ; i<37 ; i++){
		UART1_sendByte(gps_init_9600[i]);
	}
		UART1_init(8);


	// now init the uart to 115200
	u8 gps_init_115200 [79]= {0xB5 ,0x62, 0x06, 0x08, 0x06, 0x00, 0x64, 0x00, 0x01, 0x00, 0x01, 0x00, 0x7A, 0x12, 0xB5, 0x62, 0x06, 0x08, 0x00, 0x00, 0x0E, 0x30,
			0xB5, 0x62, 0x06, 0x01, 0x08 ,0x00 ,0x01 ,0x06 ,0x00 ,0x01 ,0x00 ,0x00 ,0x00 ,0x00 ,0x17 ,0xDA ,0xB5 ,0x62 ,0x06 ,0x01 ,0x02 ,0x00 ,0x01 ,0x06 ,0x10 ,0x39,
			0xB5, 0x62, 0x06, 0x09, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x31, 0xBF, 0xB5, 0x62, 0x05, 0x01, 0x02, 0x00, 0x06, 0x09, 0x17, 0x40};
	for (u8 i=0 ; i<79 ; i++){
		UART1_sendByte(gps_init_115200[i]);
	}

}

u8 GPS_Read(accel *position, accel *velocity)
{
//detecting the header of the line
	u8 char1,char2,char3;
	char1 = UART1_receiveByte();
	char2 = UART1_receiveByte();
	while (1)
	{

		char3 = UART1_receiveByte();

		if (char1==0xb5 && char2==0x62 && char3 == 0x01)		// the required info start with nav-sol header
			break;  								  			// break when we find the required info
		char1 = char2;
		char2 = char3;
	}

	UART1_receiveByte(); //id
	UART1_receiveByte(); // 2 byte length
	UART1_receiveByte();
	UART1_receiveByte();//4 time
	UART1_receiveByte();
	UART1_receiveByte();
	UART1_receiveByte();
	UART1_receiveByte();//4 idk
	UART1_receiveByte();
	UART1_receiveByte();
	UART1_receiveByte();
	UART1_receiveByte(); //2 week
	UART1_receiveByte();
	UART1_receiveByte(); //GPS fix (useless) +++++ U1-- 0=no fix -- 1=deadreckoning only -- 2=2D fix --3=3D fix -- 4=3D+DeadReckoning -- 5=Time fix only
	u8 flag = UART1_receiveByte(); //Gps fix (PASS IT ONE I GET THE VARIABLE)

	position->x= ((u32)(UART1_receiveByte()& 0xFF)| ((u32)(UART1_receiveByte()& 0xFF) <<8)|((u32)(UART1_receiveByte()& 0xFF)<<16) | (u32)(UART1_receiveByte()& 0xFF)<<24);
	position->y= ((u32)(UART1_receiveByte()& 0xFF)| ((u32)(UART1_receiveByte()& 0xFF) <<8)|((u32)(UART1_receiveByte()& 0xFF)<<16) | (u32)(UART1_receiveByte()& 0xFF)<<24);
	position->z= ((u32)(UART1_receiveByte()& 0xFF)| ((u32)(UART1_receiveByte()& 0xFF) <<8)|((u32)(UART1_receiveByte()& 0xFF)<<16) | (u32)(UART1_receiveByte()& 0xFF)<<24);
	UART1_receiveByte();// accuracy useless 4
	UART1_receiveByte();
	UART1_receiveByte();
	UART1_receiveByte();
	velocity->x= ((u32)(UART1_receiveByte()& 0xFF)| ((u32)(UART1_receiveByte()& 0xFF) <<8)|((u32)(UART1_receiveByte()& 0xFF)<<16) | (u32)(UART1_receiveByte()& 0xFF)<<24);
	velocity->y= ((u32)(UART1_receiveByte()& 0xFF)| ((u32)(UART1_receiveByte()& 0xFF) <<8)|((u32)(UART1_receiveByte()& 0xFF)<<16) | (u32)(UART1_receiveByte()& 0xFF)<<24);
	velocity->z= ((u32)(UART1_receiveByte()& 0xFF)| ((u32)(UART1_receiveByte()& 0xFF) <<8)|((u32)(UART1_receiveByte()& 0xFF)<<16) | (u32)(UART1_receiveByte()& 0xFF)<<24);
return flag;

}

