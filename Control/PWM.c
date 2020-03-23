/*
 * PWM.c
 *
 *  Created on: Feb 10, 2020
 *      Author: Zayat
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
#define frequency 50
#define prescaler 8
#define TOP  (16000000/(prescaler*frequency)) 	//40000 total counts
#define MAX 0xffff

void ARM_Motors(void)
{
	ICR1 = TOP;
	ICR3 = TOP;
	TIMSK |= (1 << TOIE1);
	ETIMSK |= (1 << TOIE3);

	TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11) ;	//Clear output upon match. TOV on ICR TOP
	TCCR3A |= (1 << COM3A1) | (1 << COM3B1) | (1 << WGM31) ;	//Same as timer 1.

	TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS11) ;		//Prescaler = 8 and i deleted the shit out of wgm13
	TCCR3B |= (1 << WGM32) | (1 << WGM33) | (1 << CS31);		//Same as timer 1.
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
void PWM(u16 dutyCycle, u8 motorNumber)
{
	u16 temp = TOP * dutyCycle/10000.0;

	switch(motorNumber)
	{
	case 1:
		OCR1A = temp;
		break;
	case 2:
		OCR1B = temp;
		break;
	case 3:
		OCR3A = temp;
		break;
	case 4:
		OCR3B = temp;
		break;
	default:
		temp =  TOP * dutyCycle/10000.0;
		OCR1A = temp;
		OCR1B = temp;
		OCR3A = temp;
		OCR3B = temp;
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
