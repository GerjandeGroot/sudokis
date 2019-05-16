/*
 * Robot.cpp
 *
 *  Created on: 26 apr. 2019
 *      Author: Victor
 */

#include "Robot.h"

Robot::Robot() {
	top.pinMode(12, INPUT); //Y
	top.pinMode(13, INPUT); //X

	stepperX.setMaxSpeed(1500);
	stepperX.setAcceleration(2500);
	stepperX.setMinPulseWidth(1);

	stepperY.setMaxSpeed(2000);
	stepperY.setAcceleration(1000);
	stepperY.setMinPulseWidth(1);

	pen(false);
}

Robot::~Robot() {
	// TODO Auto-generated destructor stub
}

void Robot::home() {
	//stepperX.move(10);
	//stepperX.
	//stepperY.setSpeed(-100);
	while (top.digitalRead(12) || top.digitalRead(13)) {
		if (!top.digitalRead(12)) {
			stepperY.stop();
			stepperY.setSpeed(0);
		} else {
			stepperY.move(-50);
			stepperY.run();
		}
		if (!top.digitalRead(13)) {
			stepperX.stop();
			stepperX.setSpeed(0);
		} else {
			stepperX.move(6000);
			stepperX.run();
		}
	}
	OSTimeDlyHMSM(0, 0, 0, 50);
	while (!top.digitalRead(12) || !top.digitalRead(13)) {
		if (top.digitalRead(12)) {
			stepperY.stop();
			stepperY.setSpeed(0);
		} else {
			stepperY.move(10);
			stepperY.run();
		}
		if (top.digitalRead(13)) {
			stepperX.stop();
			stepperX.setSpeed(0);
		} else {
			stepperX.move(-100);
			stepperX.run();
		}
	}
	stepperY.setCurrentPosition(0);
	stepperX.setCurrentPosition(0);

}

void Robot::moveTo(long x, long y) {
	stepperX.moveTo(x);
	stepperY.moveTo(y);
	while (stepperX.isRunning() || stepperY.isRunning()) {
		stepperX.run();
		stepperY.run();
	}
}

void Robot::drawNumber(int value, long x, long y) {
	switch (value) {

	case 1:
		drawOne(x, y);
		break;
	case 2:
		drawTwo(x, y);
		break;
	case 3:
		drawThree(x, y);
		break;
	case 4:
		drawFour(x, y);
		break;
	case 5:
		drawFive(x, y);
		break;
	case 6:
		drawSix(x, y);
		break;
	case 7:
		drawSeven(x, y);
		break;
	case 8:
		drawEight(x, y);
		break;
	case 9:
		drawNine(x, y);
		break;

	}
}

void Robot::drawOne(long x, long y) {
	moveTo(x + numberXoffset + numberRight, y + numberYoffset);
	pen(true);
	moveRelative(0, numberUp * 2);
	pen(false);
}

void Robot::drawTwo(long x, long y) {
	moveTo(x + numberXoffset + numberRight, y + numberYoffset);
	pen(true);
	moveRelative(numberLeft, 0);
	moveRelative(0, numberUp);
	moveRelative(numberRight, 0);
	moveRelative(0, numberUp);
	moveRelative(numberLeft, 0);
	pen(false);
}

void Robot::drawThree(long x, long y) {
	moveTo(x + numberXoffset, y + numberYoffset);
	pen(true);
	moveRelative(numberRight, 0);
	moveRelative(0, numberUp);
	moveRelative(numberLeft, 0);
	moveRelative(numberRight, 0);
	moveRelative(0, numberUp);
	moveRelative(numberLeft, 0);
	pen(false);
}

void Robot::drawFour(long x, long y) {
	moveTo(x + numberXoffset + numberRight, y + numberYoffset);
	pen(true);
	moveRelative(0, numberUp * 2);
	moveRelative(0, numberDown);
	moveRelative(numberLeft, 0);
	moveRelative(0, numberUp);
	pen(false);
}

void Robot::drawFive(long x, long y) {
	moveTo(x + numberXoffset, y + numberYoffset);
	pen(true);
	moveRelative(numberRight, 0);
	moveRelative(0, numberUp);
	moveRelative(numberLeft, 0);
	moveRelative(0, numberUp);
	moveRelative(numberRight, 0);
	pen(false);
}

void Robot::drawSix(long x, long y) {
	moveTo(x + numberXoffset + numberRight, y + numberYoffset + numberUp * 2);
	pen(true);
	moveRelative(numberLeft, 0);
	moveRelative(0, numberDown * 2);
	moveRelative(numberRight, 0);
	moveRelative(0, numberUp);
	moveRelative(numberLeft, 0);
	pen(false);
}

void Robot::drawSeven(long x, long y) {
	moveTo(x + numberXoffset + numberRight, y + numberYoffset);
	pen(true);
	moveRelative(0, numberUp * 2);
	moveRelative(numberLeft, 0);
	pen(false);
}

void Robot::drawEight(long x, long y) {
	moveTo(x + numberXoffset, y + numberYoffset);
	pen(true);
	moveRelative(numberRight, 0);
	moveRelative(0, numberUp * 2);

	moveRelative(numberLeft, 0);
	moveRelative(0, numberDown);
	moveRelative(numberRight, 0);
	moveRelative(numberLeft, 0);
	moveRelative(0, numberDown);
	pen(false);
}

void Robot::drawNine(long x, long y) {
	moveTo(x + numberXoffset, y + numberYoffset);
	pen(true);
	moveRelative(numberRight, 0);
	moveRelative(0, numberUp * 2);
	moveRelative(numberLeft, 0);
	moveRelative(0, numberDown);
	moveRelative(numberRight, 0);
	pen(false);
}

void Robot::moveRelative(long x, long y) {
	stepperX.move(x);
	stepperY.move(y);
	while (stepperX.isRunning() || stepperY.isRunning()) {
		stepperX.run();
		stepperY.run();
	}
}

void Robot::pen(bool down) {
	if (down) {
		IOWR_32DIRECT(0x10004000, 0, 130000);
		usleep(100000);
	} else {
		IOWR_32DIRECT(0x10004000, 0, 80000);
		usleep(100000);
	}
}

void Robot::xAsHoming() {
	while (top.digitalRead(13)) {

		if (!top.digitalRead(13)) {
			stepperX.stop();
			stepperX.setSpeed(0);
		} else {
			stepperX.move(6000);
			stepperX.run();
		}
	}

	OSTimeDlyHMSM(0, 0, 0, 50);
	while (!top.digitalRead(13)) {

		if (top.digitalRead(13)) {
			stepperX.stop();
			stepperX.setSpeed(0);
		} else {
			stepperX.move(-100);
			stepperX.run();
		}
	}

	stepperX.setCurrentPosition(0);

}

void Robot::drawNumberToGrid(int value, long x, long y) {
	if (counter == 5) {
		//moveTo(,y);
		xAsHoming();
		counter = 0;
	} else {
		counter++;
	}
	long totalMovesX = 0;
	long totalMovesY = 0;

	totalMovesX = (-1100 * x) - 780; // -1065 -650
	totalMovesY = ((8 - y) * 134) + 628;
	drawNumber(value, totalMovesX, totalMovesY);
}
