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

void task1(void *pvParameter);
void task2(void *pvParameter);

int main(void)
{
	/* Create 2 tasks with the same priority */
  xTaskCreate(task1, "task1", 128, NULL, 1, NULL);
  xTaskCreate(task2, "task2", 128, NULL, 1, NULL);
	
	/*
	/ After scheduler start, task1 will run first.
	/ Task1 will never leave the CPU unless vTaskDelay() or taskYIELD() is called in its function statements
	*/
  vTaskStartScheduler();
  while(1)
  {

  }
}

void task1(void *pvParameter){
	while(1){
		printf("Task 1 is running\n");
		
		//vTaskDelay(500);
		//taskYIELD();
	}
}

void task2(void *pvParameter){
	while(1){
		printf("Task 2 is running\n");
		
		//vTaskDelay(500);
		//taskYIELD();
	}
}
