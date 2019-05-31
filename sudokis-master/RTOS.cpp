#include "Main.h"
#include "standard_functions.h"
#include <io.h>
/* Definition of Task Stacks */
#define		TASK_STACKSIZE		2048
#define		TASK_IMAGE_STACK	20000

/* Definition of Task Priorities */
#define TaskIOPrio				5
#define TaskFlashPrio			6
#define MutexPrio				7
#define TaskRobotPrio			8
#define TaskImagePrio   		9
#define TaskWelcomeFlashPrio	12

#define camera			0x01	//white
#define idle		 	0x02	//green
#define error 			0x03	//red
#define interrupted		0x04	//blinking red
#define busy			0x05	//blue
#define drawing			0x06	//yellow

#define buffer	81
void * MyBuff[buffer];

OS_STK TaskIOStack[10000];
OS_STK TaskRobotStack[TASK_STACKSIZE];
OS_STK TaskImageStack[TASK_IMAGE_STACK];
OS_STK TaskFlashStack[TASK_STACKSIZE];
OS_STK TaskWelcomeFlashStack[TASK_STACKSIZE];

//function prototypes
void taskIO(void* pdata);
void taskImage(void* pdata);
void taskRobot(void* pdata);
void taskFlash(void* pdata);
void taskWelcomeFlash(void* pdata);

Sudoku sudoku;
Robot robot;

OS_FLAG_GRP *startFlag;

bool flash = false;
uint8_t status = idle;
uint8_t prev_status;
alt_up_parallel_port_dev* button = alt_up_parallel_port_open_dev("/dev/Pushbuttons");

/* The main function creates one task and starts multi-tasking */
int main(void) {
	INT8U err;
	OSTaskCreate(taskIO, (void*)0, &TaskIOStack[10000 - 1], TaskIOPrio);
	OSStart();
	return 0;
}

void taskIO(void* pdata) {
	INT8U err;

	top.coQueue = OSQCreate(&MyBuff[0], buffer);
	if(top.coQueue == 0){
		printf("Pas op, Queue is leeg...");
	}

	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(10, OUTPUT);

	status = idle;
	robot.home();
	OSTaskCreate(taskFlash, (void *)0, &TaskFlashStack[TASK_STACKSIZE-1], TaskFlashPrio);
	OSTaskCreate(taskWelcomeFlash, (void *)0, &TaskWelcomeFlashStack[TASK_STACKSIZE-1], TaskWelcomeFlashPrio);
	clearScreen();
	top.displayStartScreen();
	while(1){
		if(keysRead(1)){ //START
			if(status == idle){
				OSTaskCreate(taskImage, (void *)0, &TaskImageStack[TASK_IMAGE_STACK-1], TaskImagePrio);
			}else if(status == camera){
				status = busy;
			}else if(status == interrupted){
				OSTaskResume(TaskImagePrio);
				OSTaskResume(TaskRobotPrio);
				status = prev_status;
			}
		}
		if(keysRead(2)){ // RESET
			printf("RESET ingedrukt\n");
			status = idle;
			Robot robot;
			robot.home();
			OSTaskDel(TaskImagePrio);
			OSTaskDel(TaskRobotPrio);
			OSTaskCreate(taskImage, (void *)0, &TaskImageStack[TASK_IMAGE_STACK-1], TaskImagePrio);
		}
		if(keysRead(3)){ //NOODSTOP
			if(status != interrupted){
				prev_status = status;
				printf("NOODSTOP!\n");
				OSTaskSuspend(TaskImagePrio);
				OSTaskSuspend(TaskRobotPrio);
				status = interrupted;
				printf("Taken zijn gestopt\n");

			}

		}

		//RGB CONTROL
		if(status == idle){
			top.setRGB(false, true, false); //GREEN
		}else if(status == camera){
			top.setRGB(true, true, true);	//WHITE
		}else if(status == error){
			top.setRGB(true,false,false);	//RED
		}else if(status == interrupted){
			if(flash){
				top.setRGB(true, false, false); //BLINKING RED
			}
			else{
				top.setRGB(false, false, false); //OFF
			}
		}else if(status == busy){
			top.setRGB(false, false, true); //BLUE
		}else if(status == drawing){
			top.setRGB(true, false, true); //PURPLE
		}
		OSTimeDlyHMSM(0,0,0,125);
	}
}

void taskImage(void* pdata) {
	INT8U err;
	status = camera;
	printf("taskImage wordt uitgevoerd\n");
	clearScreen();
	IOWR(0x10003060,3,0b100);
	OSTimeDlyHMSM(0,0,3,0);
	IOWR(0x10003060,3,0b000);
	status = busy;

	if(top.testOCR(&sudoku) < 0){
		status = error;
	}else{
		status = idle;
		bool up = false;
		for (int x = 0; x < 9; ++x) {
			for(int y = 0; y < 9; y++){
				Message *m = (Message *) malloc(sizeof(Message));
				if(m == 0){
					printf("malloc error: message");
					exit(203);
				}
				if(up) {
					m->x = x;
					m->y = y;
					m->solution = sudoku.grid[x][y];
					if(sudoku.mainNumbers[x][y] > 0) continue;
				} else {
					m->x = x;
					m->y = 8-y;
					m->solution = sudoku.grid[x][8-y];
					if(sudoku.mainNumbers[x][8-y] > 0) continue;
				}

				err = OSQPost(top.coQueue, (void *) m);
				printf("error: %d\n", err);

			}
			up = !up;
		}
		printf("taskRobot wordt gestart\n");
		OSTaskCreate(taskRobot, (void *)0, &TaskRobotStack[TASK_STACKSIZE-1], TaskRobotPrio);
	}
}

void taskRobot(void* pdata) {
	INT8U err;
	Message *message;
	status = drawing;
	printf("In taskRobot\n");
	while(1){
		message = (Message *) OSQPend(top.coQueue, 1, &err);
		if(message == NULL){
			break;
		}
		sudoku.drawBusy(message->x,message->y);
		robot.drawNumberToGrid(message->solution,  message->x,  message->y);
		sudoku.drawIdle(message->x,message->y);
		free(message);
	}
	printf("Ik ben er helemaal klaar mee");
	status = idle;
	robot.home();
	OSTaskDel(TaskRobotPrio);
}

void taskFlash(void* pdata){
	while(1){
		flash = !flash;
		OSTimeDlyHMSM(0,0,0,125);
	}
}
void taskWelcomeFlash(void* pdata){
	while(1){
		flash = !flash;
		OSTimeDlyHMSM(0,0,0,125);
		top.welcomeSudokis();
	}
}
