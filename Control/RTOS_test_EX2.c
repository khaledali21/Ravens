/*
 * RTOS_test_EX3.c
 *
 * In this exercise, We have two tasks the communicate with each other using a binary semaphore
 *    First task: Scans a push button every 200msec and gives the semaphore when it's pressed.
 *    Second Task: Waits for that semaphore and toggle a LED once when getting it.
 * 
 *  Author: Nael
 */ 

#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"                   // in order to use semaphore

//==================[ Global  ] ===============
xSemaphoreHandle Push_sem;

//================= [Tasks] ===============
void PB_scan_task( void *pvParameters)
{
	DDRB = 0X00;      ;                                 // PB.0 is input (Push Button)
	PORTB = 0X01;										// Internal pull up

	/* take the semaphore once to make the initial count zero */
	xSemaphoreTake(Push_sem, portMAX_DELAY);

	while(1)
	{
		if ((PINB & (1<<0)) == 0)                               // If push button is pressed
		{
			xSemaphoreGive(Push_sem);			//give semaphore
		}
		vTaskDelay(200);  // repeat scan every 200 msec
	}
}
//-----------------------------------------------
void Blink__task( void *pvParameters)
{
    unsigned char ret;
	
	DDRA |= (1<<0); 								//PA.0 is output (LED)
	
	while(1)
	{
		// Task is blocked waiting for the semaphore or time out
		ret = xSemaphoreTake(Push_sem, portMAX_DELAY);

		if (ret == 1) // if semaphore is released (not time out)
		 {
				PORTA ^=  (1<<0); // toggle LED
		 }
	}
}

//================= [Main] =====================

int main(void)
{
	DDRA |= (1<<0); 								//PA.0 is output (LED)
	// Create  Semaphore 
	vSemaphoreCreateBinary(Push_sem);
	
	// Create Tasks
	xTaskCreate( PB_scan_task,NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL );
	xTaskCreate( Blink__task,NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	
	//Start FreeRTOS
	vTaskStartScheduler();
}
