/*
 * Main.h
 *
 *  Created on: 16 apr. 2019
 *      Author: gerja
 */

#ifndef MAIN_H_
#define MAIN_H_

/*
* Message voor de robottask
* x,y: positie in het grid van de sudoku
* solution: het getal dat op die plek geschreven moet worden
*/
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
	/*
	* Message queue for sending coordinates to the robot task
	*/
	OS_EVENT *coQueue = 0;
	
	/*
	* Leren van het OCR algoritme (referentieobjecten)
	*/
	void learnOCR();
	/*
	* Leest getallen uit een image en stopt ze in een sudoku
	* sudoku: pointer naar sudoku
	*/
	int testOCR(Sudoku *sudoku);
	/*
	* Zet de kleuren van de ledstrip 
	* r,g,b: 1 aan, 0 uit
	*/
	void setRGB(bool r, bool g, bool b);
	/*
	* Laat het welkomscherm zien
	*/
	void displayStartScreen();
	/*
	* Task laat de tietel zien en knipperen
	*/
	void welcomeSudokis();
	/*
	* druk op een knop om door te gaan
	* unused
	*/
	void sleep();
};

static Main top;


#endif /* MAIN_H_ */
