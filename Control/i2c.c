/*
 * i2c.c
 *
 *  Created on: Oct 4, 2019
 *      Author: Yousef
 */

#include <avr/io.h>
#include "UTILS.h"
#include "STD_TYPES.h"
#include "DDIO_128.h"
#include "i2c.h"


void I2C_Init(u8 bit_rate)
{
	TWCR = 0x00;
	TWBR = bit_rate;

}

void I2C_Start(void)
{
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);

	while(GET_BIT(TWCR, TWINT) == 0);

	while((TWSR & (0xF8)) != 0x08  && (TWSR & (0xF8)) != 0x10); //start status ok
}

void I2C_Add(u8 Add)
{
	TWDR = Add;
	CLEAR_BIT(TWCR,TWSTA);
	TWCR = (1<<TWEN)|(1<<TWINT);

	while (!(TWCR & (1<<TWINT)));
	while((TWSR & (0xF8)) != 0x18 &(TWSR & (0xF8)) != 0x40);
}
void I2C_Write(u8 data)
{
	u8 status;
	TWDR = data;
	TWCR = (1<<TWEN)|(1<<TWINT);
	while(GET_BIT(TWCR, TWINT) == 0);
	status=TWSR& 0xF8;
	while(status!= 0x28);

}
void I2C_Stop(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

u8 I2C_Read(void)
{
	TWCR = (1<<TWEA)|(1<<TWEN)|(1<<TWINT);


	while(GET_BIT(TWCR, TWINT) == 0);
	return TWDR;
}
