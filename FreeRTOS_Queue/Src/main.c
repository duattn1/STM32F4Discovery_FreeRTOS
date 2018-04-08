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
#include "queue.h"


xQueueHandle mainQueue;

void sendingTask(void *pvParameter);
void receivingTask(void *pvParameter);

int main(void)
{
	/* Create the queue */
	mainQueue = xQueueCreate(5, 1);

	if(mainQueue != NULL)
	{
		/* Create sending tasks */
		xTaskCreate(sendingTask, "sendingTask1", 128, (void*)100, 1, NULL);
		xTaskCreate(sendingTask, "sendingTask1", 128, (void*)200, 1, NULL);
	
		/* Create receiving task */
		xTaskCreate(receivingTask, "receivingTask", 128, NULL, 2, NULL);
		
		vTaskStartScheduler();		
	} else {
		printf("Creating queue failed\n");
	}
	
	while(1)
	{

	}  
}


void sendingTask(void *pvParameter){
	uint8_t sentData;
	portBASE_TYPE status;

	sentData = *((uint8_t*)pvParameter);

	while(1)
	{
		printf("- Sending: %d\n", sentData);
		status = xQueueSendToBack(mainQueue, &sentData, 0);

		if(status != pdPASS)
		{
			printf("  Sending failed\n");
		} 
		
		/* Delay for each sending time */
		vTaskDelay(1000);

		/* Allow other sender task to execute */
		taskYIELD();
	}
}

void receivingTask(void *pvParameter){
	uint8_t receivedData;
	portBASE_TYPE status;

	while(1)
	{
		/* Note that the last parameter of xQueueReceive() is the maximum wait time 
		* that the task remains in Blocked state.
		*	It must be greater than the data sending speed. In this case it must greater than 1000ms */
		status = xQueueReceive(mainQueue, &receivedData, 1001);

		if(status == pdPASS)
		{
			printf("  Received: %d\n", (uint8_t)receivedData);
		}
		else
		{
			printf("  Receiving failed\n");
		}
	}
}
