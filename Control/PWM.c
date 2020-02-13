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
 * 		-The timer Register is 16 bits, only 10 bits are used.
 * 		-The clock frequency is 16 MHz, with a prescale of 1024
 *
 * 	The Goal is:
 *
 * 		-To produce a 50-60 Hz square wave with duty cycle of choice to control ESC.
 *
 * 	The laws governing the resulting frequency is:
 *
 * 		F = 16000000/(prescale * (1 + TOP))	; (where TOP is 2^10 - 1) in this case (10 bits) and prescale is 1024, but
 * 												we will not use max number.
 * 		16000000/(1024*(1+TOP) = 55 Hz for example, solve for TOP = 283
 * 		since we need only 283 counts and the timer full count is 1024, therefore we should set default starting by
 * 		1024 - 1 - 283 = 740.
 * 		Now, the timer will count from 740 to 283 then overflow, which gives us 283 counts, and thus produces
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
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11) ;	//Clear output upon match. TOV on ICR TOP


	TCCR3A |= (1 << COM3A1) | (1 << COM3B1) | (1 << WGM31) | (1 << WGM30);	//Same as timer 1.

	TCNT1H = 0x8E;
	TCNT1L = 0x0B;											//Set default value as explained in description.


	TCNT3L = 0x8E;											//Set default value as explained in description.
	TCNT3H = 0x0B;

	u16 start = 0.2*0.055*36363 + 0.055*36363 + (65535 - 36363);		//(20% ARMING) CHANGE THIS IN CASE OF NOT GOOD ARMING
	/*	Translation: 283 -> range (1023 - 740).
	 * 	Where 740 is the default value placed to keep it at 55 Hz
	 *	The range is 18 ms, therefore, divide 283 by 18 to get 1 ms which is 15.7 counts.
	 *	The ESC ranges from zero throttle to 100% throttle corresponding to 1 ms (no throttle) to:
	 *	2 ms (full throttle), therefore, to arm the motors at 20% we need a pulse width of 1.2 ms,
	 *	which corresponds to 740 + 15 + 3 = 758.
	 */

	OCR1AH = (start >> 8);
	OCR1AL = start & 0xff;

	OCR1BH = (start >> 8);
	OCR1BL = start & 0xff;

	OCR3AH = (start >> 8);
	OCR3AL = start & 0xff;

	OCR3BH = (start >> 8);
	OCR3BL = start & 0xff;

	ICR1H = 0xff;
	ICR1L = 0xff;

	TIMSK |= (1 << TOIE1);// | (1 << OCIE1A) | (1 << OCIE1B);
	ETIMSK |= (1 << TOIE3);// | (1 << OCIE3A) | (1 << OCIE3B);

	TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS10) | (1 << CS12);		//Prescaler = 1024 and i deleted the shit out of wgm13
	TCCR3B |= (1 << CS31) | (1 << WGM32) | (1 << WGM33);					//Same as timer 1.
}
ISR(TIMER1_OVF_vect)
	{
		TCNT1H = 0x8E;
		TCNT1L = 0x0B;
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
	u16 temp = 36363 + (dutyCycle/100) * 2000 + 2000;			//First get the value needed then split to LOW and HIGH
	//u16 temp =  (dutyCycle/100.0) * (65535);

	switch(motorNumber)
	{
	case 1:

		OCR1AH = (temp >> 8);
		OCR1AL = temp & 0xff;
		break;
	case 2:

		OCR1BH = (temp >> 8);
		OCR1BL = temp & 0xff;
		break;
	case 3:
		OCR3AH = (temp >> 8);
		OCR3AL = temp & 0xff;
		break;
	case 4:

		OCR3BH = (temp >> 8);
		OCR3BL = temp & 0xff;
		break;
	default:
		temp = 36363 + (dutyCycle/100) * 2000 + 2000;
		OCR1AH = (temp >> 8);
		OCR1AL = temp & 0xff;

		OCR1BH = (temp >> 8);
		OCR1BL = temp & 0xff;

		OCR3AH = (temp >> 8);
		OCR3AL = temp & 0xff;

		OCR3BH = (temp >> 8);
		OCR3BL = temp & 0xff;


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
