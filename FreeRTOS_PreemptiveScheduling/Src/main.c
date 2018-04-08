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
	/	After scheduler start, task1 and task2 run alternately.
	/ Tasks are switched every Tick interrupt.
	/ Tick interrupt may switch the context to the other task while the task is printing use the stdout, 
	/ then the output may be displayed like: "Task 1Task 2 is running is running...."
	*/
  vTaskStartScheduler();
  while(1)
  {

  }
}

void task1(void *pvParameter){
	while(1){
		printf("Task 1 is running\n");		
	}
}

void task2(void *pvParameter){
	while(1){
		printf("Task 2 is running\n");
	}
}
