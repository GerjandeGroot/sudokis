/*
 * Robot.h
 *
 *  Created on: 26 apr. 2019
 *      Author: Victor
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include "typedefs.h"
#include "Main.h"
#include "stepper.h"

class stepper;
class Robot {
private:
	stepper stepperX = stepper(1, 0, 1);
	stepper stepperY = stepper(1, 2, 3);
public:
	Robot();
	virtual ~Robot();
	void home();
};

#endif /* ROBOT_H_ */
