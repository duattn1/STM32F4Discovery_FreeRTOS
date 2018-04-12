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


xSemaphoreHandle countingSemaphore;
xQueueHandle queue;

void producerTask(void *pvParameter);
void consumerTask(void *pvParameter);

int main(void)
{
	/* Create the counting semaphore with maximum
	count value of 10, and initial count value of 0 */
	countingSemaphore = xSemaphoreCreateCounting(10, 0);
	
	/* Create the queue that hold 10 elements (same value as counting semaphore) with each element size of 1 bytes */
	queue = xQueueCreate(10, 1);

	if(countingSemaphore != NULL && queue != NULL)
	{
		/* Create producer tasks */
		xTaskCreate(producerTask, "producerTask_1", 128, (void*)10, 1, NULL);
		xTaskCreate(producerTask, "producerTask_2", 128, (void*)20, 1, NULL);
		
		/* Create consumer task */
		xTaskCreate(consumerTask, "consumerTask", 128, NULL, 2, NULL);
		
		printf("Start scheduler.\n");
		vTaskStartScheduler();		
	} else {
		printf("Creating counting semaphore or queue failed\n");
	}
	
	while(1)
	{

	}  
}


void producerTask(void *pvParameter){
	uint8_t sentData = (uint8_t)pvParameter;
	portBASE_TYPE status;
	while(1)
	{		
		// Put data of producer to queue before give the semaphore
		status = xQueueSendToBack(queue, &sentData, 0);
		if(status != pdPASS)
		{
			printf("Adding to queue failed\n");
		} 
		
		xSemaphoreGive(countingSemaphore);		
		
		vTaskDelay(100);
		
		/* Allow the other producer task to run */
		taskYIELD();
	}
}

void consumerTask(void *pvParameter){	
	portBASE_TYPE status;
	uint8_t receivedData;
	while(1)
	{		
		xSemaphoreTake(countingSemaphore, 1000);		
		//printf("Taking semaphore\n");
		
		status = xQueueReceive(queue, &receivedData, 1000);
		if(status == pdPASS)
		{
			printf("Received: %d\n", receivedData);
		} else {
			printf("Getting item from queue fail\n");
		}
		
		/* Block this task for 200 ticks 
		to simulate multiple times giving the semaphore from producerTask().
		Each time giving the semaphore, the producer data is put into a queue.
		DO NOT DELAY LIKE THIS IN REAL APPLICATION.
		In real app, the interrupt causes multiple events, and we should use counting semaphore.
		*/
		vTaskDelay(200);
	}
}
