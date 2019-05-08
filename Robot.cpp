/*
 * Robot.cpp
 *
 *  Created on: 26 apr. 2019
 *      Author: Victor
 */

#include "Robot.h"

Robot::Robot() {
	// TODO Auto-generated constructor stub
	top.pinMode(12, INPUT); //Y
	top.pinMode(13, INPUT); //X

	stepperX.setMaxSpeed(2000);
	stepperX.setAcceleration(1500);
	stepperX.setMinPulseWidth(1);

	stepperY.setMaxSpeed(2000);
	stepperY.setAcceleration(1000);
	stepperY.setMinPulseWidth(1);
}

Robot::~Robot() {
	// TODO Auto-generated destructor stub
}

void Robot::home(){
	//stepperX.move(10);
	//stepperX.
	//stepperY.setSpeed(-100);
	while(top.digitalRead(12) || top.digitalRead(13)){
		if(!top.digitalRead(12)){
			stepperY.stop();
			stepperY.setSpeed(0);
		}else{
			stepperY.move(-50);
			stepperY.run();
		}
		if(!top.digitalRead(13)){
			stepperX.stop();
			stepperX.setSpeed(0);
		}else{
			stepperX.move(6000);
			stepperX.run();
		}
	}
	OSTimeDlyHMSM(0,0,0,50);
	while(!top.digitalRead(12) || !top.digitalRead(13)){
		if(top.digitalRead(12)){
			stepperY.stop();
			stepperY.setSpeed(0);
		}else{
			stepperY.move(10);
					stepperY.run();
		}
		if(top.digitalRead(13)){
			stepperX.stop();
			stepperX.setSpeed(0);
		}else{
			stepperX.move(-100);
			stepperX.run();
		}
	}
	stepperY.setCurrentPosition(0);
	stepperX.setCurrentPosition(0);



}

void Robot::moveTo(long x, long y){
	stepperX.moveTo(x);
	stepperY.moveTo(y);
	while(stepperX.isRunning()|| stepperY.isRunning()){
		stepperX.run();
		stepperY.run();
		}
}

void Robot::drawNumber(int value, long x, long y){
 switch(value){

 case 1:
	 break;
 case 2:
 	 break;
 case 3:
 	 break;
 case 4:
 	 break;
 case 5:
 	 break;
 case 6:
 	 break;
 case 7:
 	 break;
 case 8:
	 drawEight(x,y);
 	 break;
 case 9:
 	 break;


 }
}

//void Robot::DrawOne(){
//
//}

void Robot::drawEight(long x, long y){
	moveTo(x + numberXoffset, y +  numberYoffset);
	moveRelative(numberRight, 0);
	moveRelative(0,numberUp * 2);

	moveRelative(numberLeft,0);
	moveRelative(0,numberDown);
	moveRelative(numberRight,0);
	moveRelative(numberLeft,0);
	moveRelative(0,numberDown);




}

void Robot::moveRelative(long x, long y){
	stepperX.move(x);
	stepperY.move(y);
	while(stepperX.isRunning()|| stepperY.isRunning()){
		stepperX.run();
		stepperY.run();
		}
}

