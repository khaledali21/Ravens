/*
 * main.c
 *
 *  Created on: Dec 8, 2019
 *      Author: Khaled Ali
 */
#include "avr/io.h"
#include "UTILS.h"
#include "STD_TYPES.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Blocks.h"
#include "PWM.h"
#include"avr/delay.h"


void main(void)
{
	parameters parameter;

	xTaskCreate(lateral_controller,"lateral", configMINIMAL_STACK_SIZE, &parameter, 1, NULL);
	xTaskCreate(altitude_controller,"altitude", configMINIMAL_STACK_SIZE, &parameter, 2, NULL);
	xTaskCreate(yaw_controller,"yaw", configMINIMAL_STACK_SIZE, &parameter, 3, NULL);
	xTaskCreate(roll_pitch,"roll&pitch", configMINIMAL_STACK_SIZE, &parameter, 4, NULL);
	xTaskCreate(body_rates,"body_rates", configMINIMAL_STACK_SIZE, &parameter, 5, NULL);


	ARM_Motors();
	int i;
	while (1)
	{

	}

}
