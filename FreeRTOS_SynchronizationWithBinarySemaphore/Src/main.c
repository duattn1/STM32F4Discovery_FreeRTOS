/** @file main.c
 *  @brief Application main function
 *
 *  This is the main place to control the application.
 *
 *  @author 	Tran Nhat Duat (duattn)
 *	@version 	V0.1
 */ 
 
#include "stm32f4xx.h"
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


xSemaphoreHandle binarySemaphore;

void sendingTask(void *pvParameter);
void receivingTask(void *pvParameter);

int main(void)
{
	/* Create the binary semaphore */
	vSemaphoreCreateBinary(binarySemaphore);

	if(binarySemaphore != NULL)
	{
		/* Create sending tasks */
		xTaskCreate(sendingTask, "sendingTask", 128, NULL, 1, NULL);
	
		/* Create receiving task */
		xTaskCreate(receivingTask, "receivingTask", 128, NULL, 2, NULL);
		vTaskStartScheduler();		
	} else {
		printf("Creating binary semaphore failed\n");
	}
	
	while(1)
	{

	}  
}


void sendingTask(void *pvParameter){
	while(1)
	{
		printf("Unlock semaphore\n");
		xSemaphoreGive(binarySemaphore);		
		vTaskDelay(500);
	}
}

void receivingTask(void *pvParameter){	
	while(1)
	{		
		/* Similar to Queue, the waiting time should NOT equal to 0
		/ It should be > the period between 2 giving semaphore
		*/
		if(xSemaphoreTake(binarySemaphore, 501) == pdTRUE){
			printf("Taking semaphore\n");	
		} else {
			printf("Taking semaphore failed.\n");	
		}		
				
	}
}
