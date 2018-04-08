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
	printf("Init semaphore\n");
	xSemaphoreGive(binarySemaphore);

	while(1)
	{
		printf("Unlock semaphore\n");
		xSemaphoreGive(binarySemaphore);		
		vTaskDelay(1000);
	}
}

void receivingTask(void *pvParameter){	
	xSemaphoreTake(binarySemaphore, 2000);
	printf("Taking init semaphore\n");
	while(1)
	{		
		xSemaphoreTake(binarySemaphore, 2000);
		printf("Taking semaphore\n");
	}
}
