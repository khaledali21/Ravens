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

void ARM_Motors(void);
void PWM(u8 dutyCycle, u8 motorNumber);

#endif /* PWM_H_ */
