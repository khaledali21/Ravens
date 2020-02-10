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
 * 		F = 16000000/(prescale * (1 + TOP))	; where TOP is 2^10 in this case (9 bits) and prescale is 1024, but
 * 												we will not use max number.
 * 		16000000/(1024*(1+TOP) = 55 Hz for example, solve for TOP = 283
 * 		since we need only 283 counts and the timer full count is 512, therefore we should set default starting by
 * 		512 - 283 = 228.
 * 		Now, the timer will count from 228 to 511 then overflow, which gives us 283 counts, and thus produces 55 Hz.
 *
 * 		To set duty cycle:
 *
 * 			-Place compare value in
 */
#include "PWM.h"


TCCR1A = (1 << COM1A1) | (1 << WGM11) | (1 << COM1B1);	//Clear output upon match. 9 bit Fast PWM raise TOV upon TOP
TCCR1B |= (1 << CS10) | (1 << CS12) | (1 << WGM12);		//Prescaler = 1024

TCCR3A |= (1 << COM3A1) | (1 << COM3B1) | (1 << WGM11);	//Same as timer 1.
TCCR3B |= (1 << CS10) | (1 << CS12) | (1 << WGM12);		//Same as timer 1.

TCNT1L = 228;											//Set default value as explained in description.
TCNT1H = 0;

TCNT3L = 228;											//Set default value as explained in description.
TCNT3H = 0;

OCR1AL = 0xcd;
OCR1AH = 0x0c;

OCR1BL = 0xcd;
OCR1BH = 0x0c;

OCR3AL = 0xcd;
OCR3AH = 0x0c;

OCR3BL = 0xcd;
OCR3BH = 0x0c;

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
	u16 temp = 3277 + ( dutyCycle/100) * 3277;			//First get the value needed then split to LOW and HIGH

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
		OCR3BL = temp & 0xff;
		OCR3BH = (temp >> 8);
	}
}
