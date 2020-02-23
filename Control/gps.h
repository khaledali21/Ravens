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
u8 GPS_Read(accel *position, accel *velocity);
void gps_init();




#endif /* GPS_H_ */
