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
#include "USART_128.h"
void gps_init(void);
u8 GPS_Read(accel *position, accel *velocity);



#endif /* GPS_H_ */

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
