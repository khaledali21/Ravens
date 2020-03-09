<<<<<<< HEAD
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
=======
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
>>>>>>> dace0bb34349a62546d3f6c7f78d51a9c245c5a3
