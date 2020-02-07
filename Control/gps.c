/*
 * test.c
 *
 *  Created on: Oct 4, 2019
 *      Author: mahmo
 */


#include "gps.h"


void GPS_Read(f32 *lat,f32 *lon ,f32 *alt)
{
	char temp_lat[10];
	char temp_lon[10];
	char temp_alt[10];
	// temporary variables,
	//if the reading is accepted we change the real variables
	u8 trash[10];

	u8 char1,char2,char3;
	char1 = UART0_receiveByte();
	char2 = UART0_receiveByte();
	while (1)
	{
		char3 = UART0_receiveByte();
		if (char1=='G' && char2=='G' && char3 == 'A')		// the required info start with GGA
			break;  										// break when we find the required info
		char1 = char2;
		char2 = char3;
	}
	UART2_receiveByte();
	UART2_receiveString (*trash);
	UART2_receiveString(temp_lat);
	UART2_receiveByte();
	UART2_receiveByte();
	UART2_receiveString(temp_lon);
	UART2_receiveByte();
	UART2_receiveByte();
	if(UART2_receiveByte() == '0') return; 					// this byte says if the reading is acceptable or not
	UART2_receiveByte();
	UART2_receiveString (*trash);
	UART2_receiveString (*trash);
	UART2_receiveString(temp_alt);
	*lat=strTof(temp_lat);											// put the reading in the variables passed by reference
	*lon=strTof(temp_lon);
	*alt=strTof(temp_alt);
	return;
}

