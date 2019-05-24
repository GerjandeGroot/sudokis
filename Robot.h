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
#include "standard_functions.h"

#define numberXoffset -169*2 //-169
#define numberYoffset 20	//20
#define numberRight -1200 // -600
#define numberLeft 1200 // 600
#define numberUp  40
#define numberDown -40

class Robot {
private:
	stepper stepperY = stepper(1, 0, 1);
	stepper stepperX = stepper(1, 2, 3);
public:
	Robot();
	uint8_t counter;
	/*
	 *home de robot
	 */
	void home();
	/*
	 * beweeg de robot naar een positie
	 * x: positie
	 * y: positie
	 */
	void moveTo(long x, long y);
	/*
	 * beweeg de robot rlatief
	 * x: relatief x
	 * y: relatief y
	 */
	void moveRelative(long x, long y);
	/*
	 * teken een nummer'
	 * value: nummer dat getekend moet worden
	 * x, y positie
	 */
	void drawNumber(int value, long x, long y);
	/*
	 * beweeg pen omhoog of omlaag
	 * down: 1 = omlaag 0=omhoog
	 */
	void pen(bool down);

	/*
	 * teken functie voor elk getal
	 */
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
	void drawNumberToGrid(int value, long x, long y);
	void xAsHoming();
};

#include "main.h"

#endif /* ROBOT_H_ */
