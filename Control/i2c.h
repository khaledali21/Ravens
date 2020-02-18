/*
 * i2c.h
 *
 *  Created on: Oct 3, 2019
 *      Author: Yousef
 */

#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>
#include "STD_TYPES.h"

/*#define TWBR (* (volatile u8 *) ( 0x20) )
#define TWCR (* (volatile u8 *) ( 0x56) )
#define TWSR (* (volatile u8 *) ( 0x21) )
#define TWDR (* (volatile u8 *) ( 0x23) )
#define TWAR (* (volatile u8 *) ( 0x22) )*/
#define TWBR (* (volatile u8 *) ( 0x70) )
#define TWCR (* (volatile u8 *) ( 0x74) )
#define TWSR (* (volatile u8 *) ( 0x71) )
#define TWDR (* (volatile u8 *) ( 0x73) )
#define TWAR (* (volatile u8 *) ( 0x72) )
void I2C_Init(u8 bit_rate);
void I2C_Start(void);
void I2C_Add(u8 Add);
void I2C_Write(u8 data);
u8 I2C_Read(void);
void I2C_Stop(void);







#endif /* I2C_H_ */
