/*
 * PWM.h
 *
 *  Created on: Feb 10, 2020
 *      Author: Yousef
 */

#ifndef PWM_H_
#define PWM_H_

#include <avr/io.h>
#include "STD_TYPES.h"
#include "UTILS.h"
#include "avr/interrupt.h"
#define MIN 500
#define MAX 1000


void ARM_Motors(void);
void PWM(u16 dutyCycle, u8 motorNumber);
void DISARM_Motors(void);

#endif /* PWM_H_ */
