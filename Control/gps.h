/*
 * gps.h
 *
 *  Created on: Oct 4, 2019
 *      Author: mahmo
 */

#ifndef GPS_H_
#define GPS_H_
#include"STD_TYPES.h"
#include"UTILS.h"
#include "strTof.h"
#include "USART_128.h"
void GPS_Read(f32 *lat,f32 *lon , f32 *alt);




#endif /* GPS_H_ */
