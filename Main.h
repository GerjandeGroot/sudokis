/*
 * Main.h
 *
 *  Created on: 16 apr. 2019
 *      Author: gerja
 */

#ifndef MAIN_H_
#define MAIN_H_

typedef struct Message{
	unsigned char x;
	unsigned char y;
	unsigned char solution;
}message;

#include "sudoku.h"
#include "Robot.h"
#include "typedefs.h"
#include <stdio.h>
#include <unistd.h>
#include "stepper.h"
#include "SubImage.h"
#include "Image.h"
#include "OCR.h"
#include "includes.h"
#include <math.h>
#include <io.h>
#include "standard_functions.h"

class Sudoku;

class Main {
public:
	OS_EVENT *coQueue = 0;

	void learnOCR();
	int testOCR(Sudoku *sudoku);
	void setRGB(bool r, bool g, bool b);
	void displayStartScreen();
	void welcomeSudokis();
	void sleep();
};

static Main top;


#endif /* MAIN_H_ */
