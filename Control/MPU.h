/*
 * MPU.h
 *
 *  Created on: Oct 3, 2019
 *      Author: Zayat
 */

#ifndef MPU_H_
#define MPU_H_
#include"STD_TYPES.h"

void MPU_Init();
void Read_IMU_Values(accel *acc, bodyrate *g);

#endif /* MPU_H_ */
