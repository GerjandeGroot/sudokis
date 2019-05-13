/*
 * Robot.h
 *
 *  Created on: 26 apr. 2019
 *      Author: Victor
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include "stepper.h"
#include "typedefs.h"
#include <unistd.h>
#define numberXoffset -169
#define numberYoffset 10
#define numberRight -677
#define numberLeft 677
#define numberUp  20
#define numberDown -20
class Robot {
private:
	stepper stepperY = stepper(1, 0, 1);
	stepper stepperX = stepper(1, 2, 3);
public:
	Robot();
	virtual ~Robot();
	void home();
	void moveTo(long x, long y);
	void moveRelative(long x, long y);
	void drawNumber(int value, long x, long y);
	void pen(bool down);
	void testDrive();
	void xAsHoming(int Yas);
	void drawNumberToGrid(int value, long x, long y);
	void drawOne(long x, long y);
	void drawTwo(long x, long y);
	void drawThree(long x, long y);
	void drawFour(long x, long y);
	void drawFive(long x, long y);
	void drawSix(long x, long y);
	void drawSeven(long x, long y);
	void drawEight(long x, long y);
	void drawNine(long x, long y);
	void testDrive();
};

#include "Main.h"

#endif /* ROBOT_H_ */
