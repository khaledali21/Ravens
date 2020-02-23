/*
 * imu6050.c
 *
 *  Created on: Oct 3, 2019
 *      Author: Khaled Ali
 */
/*
 * IMU_REGS.c
 *
 *  Created on: Oct 3, 2019
 *      Author: Zayat
 */
#include <avr/io.h>
#include "IMU_REGS.h"
#include "I2C_Master_H_file.h"
#include "stdlib.h"
#include "UTILS.h"
#include "STD_TYPES.h"
#include "imu6050.h"

/********************************************************************************************************************************************************
 * **************************************************THIS CODE WAS WRITTEN BY TEAM RAVENS****************************************************************
 *
 * This section of code will demonstrate how to communicate with MPU6050.
 *
 * Process:
 * 			1- Initialize I2C protocol.
 * 			2- Initialize MPU by setting config, sample rate, power management and start location adderss.
 * 			3- MPU slave address is = 0x68, thus while communicating with it we use it but shifted to the left once -> 0xD0,
 * 				and the last bit defines either read or write (0xD0 for write, 0xD1 for read)
 * 			4- Set INT enabled to mark end of config.
 * 			5- Read Register raw values (ACCEL_X -> ACCEL_Y -> ACCEL_Z -> TEMP - > GYRO_X -> GYRO_Y -> GYRO_Z) each is 2 parts: HIGH then LOW.
 * 			6- Divide each register by its sensitivity for its actual values.
 *
 * *******************************************************************************************************************************************************
 */



void MPU_Init()
{
	_delay_ms(150);
	I2C_Start_Wait(0xD0);						//Call slave address and wait for Ack
	I2C_Write(SMPRLT_DIV);					//Send SMPLRT reg address

	I2C_Write(0x01);						//Set to 1KHz / 1 = 1KHz sample rate, where 1 is SMPLRT_DIV value, and 1KHz is the gyro output rate when DLPF is activated
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(CONFIG_REG);					//Send CONFG REG address
	I2C_Write(0x00);						//Set Config reg to: FSYNC -> Disabled, DLPF_CONFG to 000
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(GYRO_CONFIG);				//Send GYRO CONFG REG address
	I2C_Write(0x18);							//Set FSEL to 3 -> range = -2000 to 2000 degrees per sec.
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(ACCEL_CONFIG);				//Send ACCEL CONFIG REG address
	I2C_Write(0x18);						//Set AFS_SEL to 3 -> range = -16g to 16g
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(INT_ENABLE);					//Send INT REG adderss
	I2C_Write(0x01);						//Set DATA READY BIT to 1
	I2C_Stop();
}

void Read_Accel_Values(accel *acc)
{
	I2C_Start_Wait(0xD0);

	I2C_Write(ACCEL_XOUT_H);				//Set start address

	I2C_Repeated_Start(0xD1);

	u16 temp;
	acc->x = ((s16)I2C_Read_Ack()<<8) | ((s16)I2C_Read_Ack());
	acc->y = ((s16)I2C_Read_Ack()<<8) | ((s16)I2C_Read_Ack());
	acc->z = ((s16)I2C_Read_Ack()<<8) | ((s16)I2C_Read_Ack());
	I2C_Stop();
	acc->x = (acc->x)/2048.0;
	acc->y = (acc->y)/2048.0;
	acc->z = (acc->z)/2048.0;

}

void Read_Gyro_Values(bodyrate *g)
{
	I2C_Start_Wait(0xD0);

	I2C_Write(GYRO_XOUT_H);				//Set start address
	I2C_Repeated_Start(0xD1);

	g->p = ((s16)I2C_Read_Ack()<<8) | ((s16)I2C_Read_Ack());

	g->q = ((s16)I2C_Read_Ack()<<8) | ((s16)I2C_Read_Ack());

	g->r = ((s16)I2C_Read_Ack()<<8) | ((s16)I2C_Read_Nack());

	I2C_Stop();
	g->p = (g->p)/16.4;
	g->q = (g->q)/16.4;
	g->r = (g->r)/16.4;

}



