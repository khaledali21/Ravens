/*
 * PWM.c
 *
 *  Created on: Feb 10, 2020
 *      Author: Yousef
 */
/* In this file:
 *
 * 		Making a function that generates a Pulse wave with duty cycle of choice.
 *
 * 		-The timer Register is 16 bits, only 9 bits are used.
 * 		-The clock frequency is 16 MHz, with a prescale of 1024
 *
 * 	The Goal is:
 *
 * 		-To produce a 50-60 Hz square wave with duty cycle of choice to control ESC.
 *
 * 	The laws governing the resulting frequency is:
 *
 * 		F = 16000000/(prescale * (1 + TOP))	; (where TOP is 2^16 - 1) in this case (16 bits) and prescale is 1024, but
 * 												we will not use max number.
 * 		16000000/(8*(1+TOP) = 55 Hz for example, solve for TOP = 36363
 * 		since we need only 36363 counts and the timer full count is 65535, therefore we should set default starting by
 * 		65535 - 36363 = 29173.
 * 		Now, the timer will count from 29173 to 65535 then overflow, which gives us 36363 counts, and thus produces
 * 		 55 Hz.
 *
 * 		To set duty cycle:
 *
 * 			-Place compare value in
 */

#include "PWM.h"
#include <avr/io.h>

void ARM_Motors(void)
{
	TCCR1A |= (1 << COM1A1) | (1 << WGM11) | (1 << WGM10) | (1 << COM1B1);	//Clear output upon match. 16 bit Fast PWM raise TOV upon TOP
	TCCR1B |= (1 << CS11) | (1 << WGM12) | (1 << WGM13);		//Prescaler = 8

	TCCR3A |= (1 << COM3A1) | (1 << COM3B1) | (1 << WGM31) | (1 << WGM30);	//Same as timer 1.
	TCCR3B |= (1 << CS31) | (1 << WGM32) | (1 << WGM33);		//Same as timer 1.

	TCNT1L = 0xF5;											//Set default value as explained in description.
	TCNT1H = 0x71;

	TCNT3L = 0xF5;											//Set default value as explained in description.
	TCNT3H = 0x71;

	u16 start = 0.2*0.055*36363 + 0.055*36363 + 29173;		//(20% ARMING) CHANGE THIS IN CASE OF NOT GOOD ARMING
	/*	Translation: 36363 -> range (65563 - 29173).
	 * 	Where 29173 is the default value placed to keep it at 55 Hz
	 *	The range is 18 ms, therefore, divide 36363 by 18 to get 1 ms which is 2020.
	 *	The ESC ranges from zero throttle to 100% throttle corresponding to 1 ms (no throttle) to:
	 *	2 ms (full throttle), therefore, to arm the motors at 20% we need a pulse width of 1.2 ms,
	 *	which corresponds to 29173 + 2000 + 2000/5 = whatever b2a.
	 */

	OCR1AL = start & 0xff;
	OCR1AH = (start >> 8);

	OCR1BL = start & 0xff;
	OCR1BH = (start >> 8);

	OCR3AL = start & 0xff;
	OCR3AH = (start >> 8);

	OCR3BL = start & 0xff;
	OCR3BH = (start >> 8);

	TIMSK |= (1 << TOIE1) | (1 << OCIE1A) | (1 << OCIE1B);
	ETIMSK |= (1 << TOIE3) | (1 << OCIE3A) | (1 << OCIE3B);
}
	/*The Following function takes in duty cycle and produces PWM signal accordingly (Might be changed later to take
	 * force and output the PWM signal directly), along with Motor number to determine which OC reg.
	 *
	 * 		-Motor 1 = OCR1A						1    2
	 * 		-Motor 2 = OCR1B						 \  /
	 * 		-Motor 3 = OCR3A						  []		Revisit course for recheck.
	 * 		-Motor 4 = OCR3B						 /  \
	 * 												3    4
	 *
	 */

void PWM(u8 dutyCycle, u8 motorNumber)					//dutyCycle is a percentage of how much force is needed of max
{
	u16 temp = 29173 + (dutyCycle/100) * 2000 + 2000;			//First get the value needed then split to LOW and HIGH

	switch(motorNumber)
	{
	case 1:
		OCR1AL = temp & 0xff;
		OCR1AH = (temp >> 8);
		break;
	case 2:
		OCR1BL = temp & 0xff;
		OCR1BH = (temp >> 8);
		break;
	case 3:
		OCR3AL = temp & 0xff;
		OCR3AH = (temp >> 8);
		break;
	case 4:
		OCR3BL = temp & 0xff;
		OCR3BH = (temp >> 8);
		break;
	default:
		temp = 29173 + 0.2 * 2000 + 2000;			
		OCR1AL = temp & 0xff;
		OCR1AH = (temp >> 8);
		OCR1BL = temp & 0xff;
		OCR1BH = (temp >> 8);
		OCR3AL = temp & 0xff;
		OCR3AH = (temp >> 8);
		OCR3BL = temp & 0xff;
		OCR3BH = (temp >> 8);
	}
}

/* Disabling all timers*/
void DISARM_Motors(void)
{
	TCCR1A = 0;
	TCCR1B = 0;
	TCCR3A = 0;
	TCCR3B = 0;
	TCNT1 = 0;
	TCNT3 = 0;
	OCR1A = 0;
	OCR1B = 0;
	OCR3A = 0;
	OCR3B = 0;
	TIMSK = 0;
	ETIMSK = 0;
}
