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


xSemaphoreHandle mutex;

void printingTask(void *pvParameters);

int main(void)
{
	mutex = xSemaphoreCreateMutex();
	if(mutex != NULL){
		xTaskCreate(printingTask, "Task1", 128, "Task 1 is running", 1, NULL);
		xTaskCreate(printingTask, "Task2", 128, "Task 2 is running", 1, NULL);	
	
		vTaskStartScheduler();
	} else {
		printf("Creating mutex failed.\n");
	}
	
  while(1)
  {

  }
}

void printingTask(void *pvParameters){
	char *printedString;
	printedString = (char *) pvParameters;

	while(1){
		if(xSemaphoreTake(mutex, 0) == pdTRUE){
			printf("%s\n", printedString);
			xSemaphoreGive(mutex);				
		} else {
			/* Do nothing when taking the semaphore failed */
		}
		/* Allow the other task to run*/
		taskYIELD();
	}
}

