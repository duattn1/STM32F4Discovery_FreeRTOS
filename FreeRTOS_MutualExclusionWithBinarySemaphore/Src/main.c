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

void printtingTask1(void *pvParameter);
void printtingTask2(void *pvParameter);

int main(void)
{
	/* Create the binary semaphore */
	vSemaphoreCreateBinary(binarySemaphore);

	if(binarySemaphore != NULL)
	{
		/* Create 2 printing tasks with same priority*/
		xTaskCreate(printtingTask1, "Task_1", 128, NULL, 1, NULL);
		xTaskCreate(printtingTask2, "Task_2", 128, NULL, 1, NULL);
		
		vTaskStartScheduler();		
	} else {
		printf("Creating binary semaphore failed\n");
	}
	
	while(1)
	{

	}  
}


void printtingTask1(void *pvParameter){
	while(1)
	{
		if(xSemaphoreTake(binarySemaphore, 0) == pdTRUE){					
			printf("Task 1 is running\n");				
			xSemaphoreGive(binarySemaphore);
		} else {
			/* Do nothing when taking the semaphore failed */
		}
		/* Allow the other task to run */
		taskYIELD();
	}
}

void printtingTask2(void *pvParameter){
	while(1)
	{
		if(xSemaphoreTake(binarySemaphore, 0) == pdTRUE){					
			printf("Task 2 is running\n");				
			xSemaphoreGive(binarySemaphore);
		} else {
			/* Do nothing when taking the semaphore failed */
		}	
		/* Allow the other task to run */
		taskYIELD();
	}
}

