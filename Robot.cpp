/*
 * Robot.cpp
 *
 *  Created on: 26 apr. 2019
 *      Author: Victor
 */

#include "Robot.h"

Robot::Robot() {
	pinMode(12, INPUT); //Y
	pinMode(13, INPUT); //X
	stepperX.setMaxSpeed(3500); // 1500
	stepperX.setAcceleration(5000); // 2500
	stepperX.setMinPulseWidth(1);

	stepperY.setMaxSpeed(2000);
	stepperY.setAcceleration(1000);
	stepperY.setMinPulseWidth(1);

	pen(false);
}

void Robot::home() {
	//stepperX.move(10);
	//stepperX.
	//stepperY.setSpeed(-100);
	while (digitalRead(12) || digitalRead(13)) {
		if (!digitalRead(12)) {
			stepperY.stop();
			stepperY.setSpeed(0);
		} else {
			stepperY.move(-50);
			stepperY.run();
		}
		if (!digitalRead(13)) {
			stepperX.stop();
			stepperX.setSpeed(0);
		} else {
			stepperX.move(6000);
			stepperX.run();
		}
	}
	OSTimeDlyHMSM(0, 0, 0, 50);
	while (!digitalRead(12) || !digitalRead(13)) {
		if (digitalRead(12)) {
			stepperY.stop();
			stepperY.setSpeed(0);
		} else {
			stepperY.move(10);
			stepperY.run();
		}
		if (digitalRead(13)) {
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
	if (down && !switchesRead(0)) {
		IOWR_32DIRECT(0x10004000, 0, 120000);
		usleep(100000);
	} else {
		IOWR_32DIRECT(0x10004000, 0, 80000);
		usleep(100000);
	}
}

void Robot::xAsHoming() {
	while (digitalRead(13)) {

		if (!digitalRead(13)) {
			stepperX.stop();
			stepperX.setSpeed(0);
		} else {
			stepperX.move(6000);
			stepperX.run();
		}
	}

	OSTimeDlyHMSM(0, 0, 0, 50);
	while (!digitalRead(13)) {

		if (digitalRead(13)) {
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

	totalMovesX = (-2200 * x) - 1560; // -1100 -780
	totalMovesY = ((8 - y) * 134) + 628; //134 628
	drawNumber(value, totalMovesX, totalMovesY);
}
