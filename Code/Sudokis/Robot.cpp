/*
 * Robot.cpp
 *
 *  Created on: 26 apr. 2019
 *      Author: Victor
 */

#include "Robot.h"

Robot::Robot() {
	// TODO Auto-generated constructor stub
	top.pinMode(11, INPUT);
	top.pinMode(12, INPUT);
	stepperX.setMaxSpeed(1000);
	stepperX.setAcceleration(500);
	stepperX.setMinPulseWidth(1);

	stepperY.setMaxSpeed(2000);
	stepperY.setAcceleration(1000);
	stepperY.setMinPulseWidth(1);
}

Robot::~Robot() {
	// TODO Auto-generated destructor stub
}

void Robot::home(){
	stepperX.setSpeed(-100);
	//stepperY.setSpeed(-100);
	while(1){
		stepperX.run();
	}
}
