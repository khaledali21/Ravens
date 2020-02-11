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

void GPS_Read(f32 *lon ,f32 *lat ,f32 *alt)
{
	char temp_lat[10];
	char temp_lon[10];
	char temp_alt[10];
	// temporary variables,
	//if the reading is accepted we change the real variables
	u8 trash[10];

	u8 char1,char2,char3;
	char1 = UART1_receiveByte();
	char2 = UART1_receiveByte();
	while (1)
	{

		char3 = UART1_receiveByte();
		if (char1=='G' && char2=='G' && char3 == 'A')		// the required info start with GGA
			break;  										// break when we find the required info
		char1 = char2;
		char2 = char3;
	}

	UART1_receiveByte();
	UART1_receiveString (*trash);
	UART1_receiveString(temp_lat);

	UART1_receiveByte();
	UART1_receiveByte();
	UART1_receiveString(temp_lon);
	UART1_receiveByte();
	UART1_receiveByte();

	//if(UART1_receiveByte() == '0') return; 					// this byte says if the reading is acceptable or not
	UART1_receiveByte();
	UART1_receiveString (*trash);
	UART1_receiveString (*trash);
	UART1_receiveString(temp_alt);
	*lat=strTof(temp_lat);											// put the reading in the variables passed by reference
	*lon=strTof(temp_lon);
	*alt=strTof(temp_alt);
/*how to transform degree to meter .. temp_lat form is ddmm.mmmm .. where d is degree m is mnt
 *  first multi with 10 and get dd alone them multi with 100 to get mnts
 *   devide mnts by 60 to get degree
 *   now add to the old dgrees and multi with 111,139 to get it in meters
 */
	u8 lat_deg=temp_lat/100;
	f32 temp_mnts = (temp_lat-lat_deg) /60;
	f32 lat_deg_mnt=lat_deg + temp_mnts;
	temp_lat= lat_deg_mnt * 111139;

	u8 lon_deg=temp_lon/100;
	temp_mnts = (temp_lon-lon_deg) /60;
	f32 lon_deg_mnt=lon_deg + temp_mnts;
	temp_lon= lon_deg_mnt * 111139;





	*lat=strTof(temp_lat);				// put the reading in the variables passed by reference
	*lon=strTof(temp_lon);
	*alt=strTof(temp_alt);

	return;
}

