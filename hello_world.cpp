/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include "Main.h"
#include <HAL/inc/sys/alt_timestamp.h>
#include <io.h>
#include <stdio.h>
#include <unistd.h>
#include <altera_up_avalon_parallel_port.h>
#include "includes.h"

/* Definition of Task Stacks */
#define   TASK_STACKSIZE       2048
OS_STK	create_task_stk[10000];
OS_STK  image_task_stk[TASK_STACKSIZE];
OS_STK	io_task_stk[TASK_STACKSIZE];
OS_STK  robot_task_stk[TASK_STACKSIZE];


/* Definition of Task Priorities */
#define create_task_priority	7
#define image_task_priority    	9
#define io_task_priority		8
#define robot_task_priority		10

#define buf_size 16

#define camera	 		0x01	//white
#define waitingInput 	0x02	//green
#define stop 			0x03	//red
#define error 			0x04	//blinking red
#define busy			0x05	//blue
OS_FLAG_GRP *taskFlags;

//function prototypes
void create_task(void* pdata);
void image_task(void* pdata);
void io_task(void* pdata);
void robot_task(void* pdata);

OS_EVENT * coordinateQueue;

void * MyBuff[buf_size];

alt_up_parallel_port_dev* button = alt_up_parallel_port_open_dev("/dev/Pushbuttons");

void image_task(void* pdata)
{
  while (1)
  {
    printf("Hello from image_task\n");
    OSTimeDlyHMSM(0,0,3,0);
  }
}

void io_task(void* pdata)
{
	INT8U err;
	while(1){

		//OSFlagPend(taskFlags, camera + waitingInput + stop + error + busy, OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME, 0, &err);
		printf("Hello from io_task\n");

	}
}

void robot_task(void* pdata)
{
  while (1)
  {
    printf("Hello from robot_task\n");

    OSTimeDlyHMSM(0,0,0,100);
  }
}



void create_task(void* pdata){
	printf("create tasks\n");
	top.init();
	INT8U err;
	taskFlags = OSFlagCreate(0x00, &err);
//	OSTaskCreate(image_task,
//				  NULL,
//				  &image_task_stk[TASK_STACKSIZE-1],
//				  image_task_priority);
//	printf("created image task\n");
//	OSTaskCreate(io_task,
//				  NULL,
//				  &io_task_stk[TASK_STACKSIZE-1],
//				  io_task_priority);
//
//	printf("created io task\n");
//	OSTaskCreate(robot_task,
//				  NULL,
//				  &robot_task_stk[TASK_STACKSIZE-1],
//				  robot_task_priority);
//	printf("created robot task\n");
//
//	coordinateQueue = OSQCreate(&MyBuff[0], buf_size);
//
	OSTaskSuspend(create_task_priority);

}

/* The main function creates two task and starts multi-tasking */
int main(void)
{
	top.init();
	OSTaskCreate(create_task,
	                  NULL,
	                  &create_task_stk[TASK_STACKSIZE-1],
	                  create_task_priority);

  OSStart();
  return 0;
}
