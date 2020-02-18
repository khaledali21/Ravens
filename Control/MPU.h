/*
 * MPU.h
 *
 *  Created on: Oct 3, 2019
 *      Author: Zayat
 */

#ifndef MPU_H_
#define MPU_H_
#include"STD_TYPES.h"
typedef struct accel{
	f32 x;
	f32 y;
	f32 z;
}accel;
typedef struct bodyrate{
	f32 p;
	f32 q;
	f32 r;
}bodyrate;

void MPU_Init();
void Read_IMU_Values(accel *acc, bodyrate *g);

#endif /* MPU_H_ */
