#include "Main.h"
#include <io.h>

/* Definition of Task Stacks */
#define   TASK_STACKSIZE       2048

/* Definition of Task Priorities */
#define TaskIOPrio			5
#define TaskFlashPrio		6
#define TaskRobotPrio		7
#define TaskImagePrio   	8
#define TaskNoodstopPrio	9


#define buf_size 16

#define camera			0x01	//white
#define idle		 	0x02	//green
#define error 			0x03	//red
#define interupted		0x04	//blinking red
#define busy			0x05	//blue
#define start			0x01

OS_STK TaskIOStack[TASK_STACKSIZE];
OS_STK TaskRobotStack[TASK_STACKSIZE];
OS_STK TaskImageStack[TASK_STACKSIZE];
OS_STK TaskFlashStack[TASK_STACKSIZE];

//function prototypes
void taskIO(void* pdata);
void taskImage(void* pdata);
void taskRobot(void* pdata);
void taskFlash(void* pdata);

OS_EVENT *coordinateQueue;

OS_FLAG_GRP *statusFlags;
OS_FLAG_GRP *startFlag;

bool flash = false;
uint8_t status = idle;

void * MyBuff[buf_size];

alt_up_parallel_port_dev* button = alt_up_parallel_port_open_dev("/dev/Pushbuttons");

/* The main function creates two task and starts multi-tasking */
int main(void) {
	OSTaskCreate(taskIO, (void*)0, &TaskIOStack[TASK_STACKSIZE - 1], TaskIOPrio);
	OSStart();
	return 0;
}

void taskIO(void* pdata) {
	top.pinMode(8, OUTPUT);
	top.pinMode(9, OUTPUT);
	top.pinMode(10, OUTPUT);
	INT8U err;
	coordinateQueue = OSQCreate(&MyBuff[0], buf_size);

	statusFlags = OSFlagCreate(0x00, &err);
	startFlag = OSFlagCreate(0x00, &err);
	printf("create tasks\n");
	OSTaskCreate(taskImage, (void *)0, &TaskImageStack[TASK_STACKSIZE-1], TaskImagePrio);
	OSTaskCreate(taskRobot, (void *)0, &TaskRobotStack[TASK_STACKSIZE-1], TaskRobotPrio);
	OSTaskCreate(taskFlash, (void *)0, &TaskFlashStack[TASK_STACKSIZE-1], TaskFlashPrio);
	printf("created robot task\n");



	while(1){
		printf("In while, waiting...\n");
		//alt_up_parallel_port_write_data(top.redLeds, alt_up_parallel_port_read_data(top.keys) & 0b10);
		if(alt_up_parallel_port_read_data(top.keys) & 0b10){ //START
			OSFlagPost(startFlag, start, OS_FLAG_SET, &err);
			if(status == idle){
				status = camera;
			}else if(status == camera){
				status = busy;
			}else if(status == interupted){
				OSTaskResume(TaskImagePrio);
				OSTaskResume(TaskRobotPrio);
				status = busy;
			}
		}
		if(alt_up_parallel_port_read_data(top.keys) & 0b100){ // RESEST
			status = idle;
			OSTaskDel(TaskImagePrio);
			OSTaskDel(TaskRobotPrio);
			OSTaskCreate(taskImage, (void *)0, &TaskImageStack[TASK_STACKSIZE-1], TaskImagePrio);
			OSTaskCreate(taskRobot, (void *)0, &TaskRobotStack[TASK_STACKSIZE-1], TaskRobotPrio);

		}
		if(alt_up_parallel_port_read_data(top.keys) & 0b1000){ //NOODSTOP
			printf("NOODSTOP!\n");

			OSTaskSuspend(TaskImagePrio);

			OSTaskSuspend(TaskRobotPrio);
			status = interupted;
			printf("Taken gestopt\n");

		}
		//RGB CONTROL
		if(status == idle){
			top.setRGB(false, true, false);
		}else if(status == camera){
			top.setRGB(true, true, true);
		}else if(status == error){
			top.setRGB(true,false,false);
		}else if(status == interupted){
			if(flash){
				top.setRGB(true, false, false);
			}
			else{
				top.setRGB(false, false, false);
			}
		}else if(status == busy){
			top.setRGB(false, false, true);
		}
		OSTimeDlyHMSM(0,0,0,125);
	}
}

void taskImage(void* pdata) {
	INT8U err;
	while (1) {
		if(OSFlagPend(startFlag, start, OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME, 0, &err)){
			alt_up_parallel_port_write_data(top.redLeds, 1);
			printf("FLAG GEZIEN\n");
		}
		alt_up_parallel_port_write_data(top.redLeds, 0);
		OSTimeDlyHMSM(0, 0, 0, 10);
	}
}

void taskRobot(void* pdata) {
	while (1) {
		printf("Hello from robot_task\n");
		//OSTimeDlyHMSM(0, 0, 0, 100);
	}
}

void taskFlash(void* pdata){
	INT8U err;
	while(1){
		flash = !flash;
		OSTimeDlyHMSM(0,0,0,125);

	}
}
