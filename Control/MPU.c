/*
 * IMU_REGS.c
 *
 *  Created on: Oct 3, 2019
 *      Author: Zayat
 */
#include <avr/io.h>
#include "IMU_REGS.h"
#include "i2c.h"
#include "stdlib.h"
#include "UTILS.h"
#include "MPU.h"

/********************************************************************************************************************************************************
 * **************************************************THIS CODE WAS WRITTEN BY TEAM RAVENS****************************************************************
 *
 * This section of code will demonstrate how to communicate with MPU6050.
 *
 * Process:
 * 			1- Initialize I2C protocol.
 * 			2- Initialize MPU by setting config, sample rate, power management and start location Start_Waiterss.
 * 			3- MPU slave Start_Waitress is = 0x68, thus while communicating with it we use it but shifted to the left once -> 0xD0,
 * 				and the LSB bit defines either Read_Ack or write (0xD0 for write, 0xD1 for Read_Ack)
 * 			4- Set INT enabled to mark end of config.
 * 			5- Read_Ack Register raw values (ACCEL_X -> ACCEL_Y -> ACCEL_Z -> TEMP - > GYRO_X -> GYRO_Y -> GYRO_Z) each is 2 parts: HIGH then LOW.
 * 			6- Divide each Read_Acking by its sensitivity for its actual values.
 *
 * *******************************************************************************************************************************************************
 */


void MPU_Init()
{
	I2C_Add(0xD0);								//Call slave Start_Waitress and wait for Ack
	I2C_Write(SMPRLT_DIV);						//Send SMPLRT reg Start_Waitress
	I2C_Write(0x00);							//Set to 1KHz / 1 = 1KHz sample rate, where 1 is SMPLRT_DIV value, and 1KHz is the gyro output rate when DLPF is activated
	I2C_Stop();

	I2C_Add(0xD0);
	I2C_Write(CONFIG_REG);						//Send CONFG REG Start_Waitress
	I2C_Write(0x00);							//Set Config reg to: FSYNC -> Disabled, DLPF_CONFG to 000 = Max bandwidth and least delay
	I2C_Stop();

	I2C_Add(0xD0);
	I2C_Write(GYRO_CONFIG);						//Send GYRO CONFG REG Start_Waitress
	I2C_Write(0x18);							//Set FSEL to 3 -> range = -2000 to 2000 degrees per sec.
	I2C_Stop();

	I2C_Add(0xD0);
	I2C_Write(ACCEL_CONFIG);					//Send ACCEL CONFIG REG Start_Waitress
	I2C_Write(0x18);							//Set AFS_SEL to 3 -> range = -16g to 16g
	I2C_Stop();

	I2C_Add(0xD0);
	I2C_Write(PWR_MGMT_1);						//Send PWR REG Start_Waiterss
	I2C_Write(0x01);							//Set to PLL with x-axis reference
	I2C_Stop();

	I2C_Add(0xD0);
	I2C_Write(INT_ENABLE);						//Send INT REG Start_Waiterss
	I2C_Write(0x01);							//Set DATA Read_AckY BIT to 1
	I2C_Stop();
}

void Read_IMU_Values(accel *acc, bodyrate *gyro)
{
	f32 temp;
	I2C_Add(0xD0);
	I2C_Write(ACCEL_XOUT_H);					//Set start Start_Waitress
	I2C_Add(0xD1);								//Send slave Start_Waitress + Read_Ack bit
	acc->x = ((u16)I2C_Read()<<8) | ((u16)I2C_Read());
	acc->y = ((u16)I2C_Read()<<8) | ((u16)I2C_Read());			//Read_Ack HIGH  then LOW
	acc->z = ((u16)I2C_Read()<<8) | ((u16)I2C_Read());			/////////////////////
	temp = ((u16)I2C_Read()<<8) | ((u16)I2C_Read());
	gyro->p = ((u16)I2C_Read()<<8) | ((u16)I2C_Read());
	gyro->q = ((u16)I2C_Read()<<8) | ((u16)I2C_Read());
	gyro->r = ((u16)I2C_Read()<<8) | ((u16)I2C_Read());
	I2C_Stop();
	acc->x /= 2048;								///////////////////////////////////////////
	acc->y /= 2048;								//normalizing the raw values to real values
	acc->z /= 2048;								///////////////////////////////////////////
	gyro->p /= 16.4;
	gyro->q /= 16.4;
	gyro->r /= 16.4;
}



