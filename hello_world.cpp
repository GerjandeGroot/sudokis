#include "Main.h"
//#include <HAL/inc/sys/alt_timestamp.h>
#include <io.h>
//#include <stdio.h>
//#include <unistd.h>
//#include <altera_up_avalon_parallel_port.h>
//#include "includes.h"

/* Definition of Task Stacks */
#define   TASK_STACKSIZE       2048
OS_STK create_task_stk[10000];
OS_STK image_task_stk[TASK_STACKSIZE];
OS_STK io_task_stk[TASK_STACKSIZE];
OS_STK robot_task_stk[TASK_STACKSIZE];

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
#define start			0x01
//function prototypes
void create_task(void* pdata);
void image_task(void* pdata);
void io_task(void* pdata);
void robot_task(void* pdata);

OS_EVENT *coordinateQueue;

OS_FLAG_GRP *taskFlags;
OS_FLAG_GRP *taskStart;

void * MyBuff[buf_size];

alt_up_parallel_port_dev* button = alt_up_parallel_port_open_dev("/dev/Pushbuttons");

void image_task(void* pdata) {
	INT8U err;
	while (1) {
		OSFlagPend(taskStart, start, OS_FLAG_WAIT_SET_ANY + OS_FLAG_CLR, 0, &err);
		printf("PEND & START IMAGE TASK\n");
		//OSTimeDlyHMSM(0, 0, 3, 0);
	}
}

void io_task(void* pdata) {
	INT8U err;
	while (1) {
		printf("Hello from io_task\n");
		if(alt_up_parallel_port_read_data(top.keys) & 0b1){
			OSFlagPost(taskStart, start, OS_FLAG_SET, &err);
			printf("POST FLAG START\n");
		}
		if(alt_up_parallel_port_read_data(top.keys) & 0b10){

		}
		if(alt_up_parallel_port_read_data(top.keys) & 0b100){}
		OSFlagPend(taskFlags, camera + waitingInput + stop + error + busy, OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME, 0, &err);

		OSTimeDlyHMSM(0, 0, 0, 10);

	}
}

void robot_task(void* pdata) {
	while (1) {
		printf("Hello from robot_task\n");
		//OSTimeDlyHMSM(0, 0, 0, 100);
	}
}

void create_task(void* pdata) {
	printf("create tasks\n");
	top.init();
	INT8U err;
	taskFlags = OSFlagCreate(0x00, &err);
	taskStart = OSFlagCreate(0x00, &err);

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
int main(void) {
	top.init();
	OSTaskCreate(create_task,
	NULL, &create_task_stk[TASK_STACKSIZE - 1],
	create_task_priority);

	OSStart();
	return 0;
}
