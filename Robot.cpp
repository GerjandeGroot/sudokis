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

	stepperX.setMaxSpeed(1500);
	stepperX.setAcceleration(2000);
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
	
	OSTimeDlyHMSM(0,0,0,50);
	while(!top.digitalRead(12) || !top.digitalRead(13)){
		if(top.digitalRead(12)){
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

void Robot::testDrive() {
	int tempY = 0;
	int tempX = 0;
	int tempXas = 0;
	int tempYas = 0;
	bool xAs = false;
	bool yAs = false;
	int totalMovesX = 0;
	int totalMovesY = 0;
	while (1) {
		for (int x = 0; x < 9; x++) {
			for (int y = 0; y < 9; y++) {

				if (tempXas != x) {
					xAs = true;
				}
				if ((x == 3 || x == 6) && xAs == true) {

					tempX = 59;
					printf("tempX %d\n", tempX);
					xAs = false;
				} else {
					tempX = 0;
				}

				if (tempYas != y) {
					yAs = true;
				}
				if ((y == 3 || y == 6) && yAs == true) {
					tempY = 9;
					printf("tempY %d\n", tempY);
					yAs = false;

				} else {
					tempY = 0;
				}

				totalMovesX = (x * 996) + tempX;
				totalMovesY = (y * 59) + tempY;
				printf("Xas = %d \t\t Yas = %d\n", totalMovesX, totalMovesY);
				usleep(1000000);
				//stepperX.moveTo(totalMovesX, totalMovesY);
				tempXas = x;
				tempYas = y;
			}
		}
	}
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

