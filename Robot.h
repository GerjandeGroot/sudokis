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
#define numberXoffset -280
#define numberYoffset 12
#define numberRight -555
#define numberLeft 555
#define numberUp  25
#define numberDown -25
class Robot {
private:
	stepper stepperY = stepper(1, 0, 1);
	stepper stepperX = stepper(1, 2, 3);
public:
	Robot();
	virtual ~Robot();
	void home();
	void moveTo(long x, long y);
	void drawEight(long x, long y);
	void moveRelative(long x, long y);
	void drawNumber(int value, long x, long y);
};

#include "Main.h"

#endif /* ROBOT_H_ */
