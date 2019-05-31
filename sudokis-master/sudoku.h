#ifndef SUDOKU_H_
#define SUDOKU_H_

#include "Robot.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <unistd.h>
#include <sstream>
#include "standard_functions.h"


#define WHITE 	0xffffff
#define BLACK 	0x000000
#define YELLOW	0x00ff00
#define BLUE	0x0000ff
#define UNKNOWN	0xf0f0f0

#define xPosGrid 179+24
#define yPosGrid 19+36
#define xPosNumbers 52
#define yPosNumbers 15

class Main;

class Sudoku {
private:

public:
	/**
	 * @brief sudoku grid met oplossing
	 **/
	uint8_t grid[9][9];
	/**
	 * @brief sudoku grid zonder oplossing
	 **/
	uint8_t mainNumbers[9][9];

	Sudoku();
	/**
	 * @brief print sudoku grid op het scherm
	 **/
	void printSudokuGrid();
	/**
	 * @brief print oplossing sudoku grid op het scherm
	 **/
	void printSolutionToSudokuGrid();
	/**
	 * @brief maakt de 2d array leeg
	 **/
	void create2DArray();
	/**
	 * @brief plaatst waarde in mainNumbers
	 *
	 * @param x -- De rij positie van 2D array
	 * @param y -- De kolom positie van 2D aray
	 *
	 **/
	void addMainNumber(int x, int y, int value);
	/**
	 * @brief plaatst waarde in grid
	 *
	 * @param x -- De rij positie van 2D array
	 * @param y -- De kolom positie van 2D aray
	 *
	 **/
	void addNumber(int x, int y, int value);
	/**
	 * @brief print getal uit grid oip het scherm
	 *
	 * @param x -- De rij positie van 2D array
	 * @param y -- De kolom positie van 2D aray
	 **/
	void printNumber(int x, int y);
	/*
	* los de sudoku op
	*/
	bool solve();
	/*
	* probeert 1 vakje op te lossen
	* @param x -- De rij positie van 2D array
	* @param y -- De kolom positie van 2D aray
	*/
	bool solveCell(int x, int y);
	/*
	* checkt of getal in vakje mag komen
	* @param x -- De rij positie van 2D array
	* @param y -- De kolom positie van 2D aray
	* @param i -- Het getal dat gechecked moet worden
	*/
	bool checkNumber(int x, int y, int i);
	/*
	* checkt of getal in vakje mag komen regel 2
	* @param x -- De rij positie van 2D array
	* @param y -- De kolom positie van 2D aray
	* @param i -- Het getal dat gechecked moet worden
	*/
	bool posElim(int x, int y, int i);
	/*
	* Reset de 2dArray
	*/
	void reset2Darray();
	/*
	* test Sudokus
	*/
	void testSudoku1();
	void testSudoku2();
	void testSudoku3();
	void testSudoku4();
	/**
	 * @brief weergeeft Hoofdnummer in sudoki d.m.v. achtergrond kleur
	 *
	 * @param row -- de rij positie in het grid (links naar recht)
	 * @param column -- de kolom in positie in het grid (boven naar benenden)
	 *
	 **/
	void drawMainNumber(int row, int columnn);
	/**
	 * @brief maak achtergrond roze
	 *
	 * @param x -- De rij positie van 2D array
	 * @param y -- De colom positie van 2D aray
	 *
	 **/
	void drawBusy(int row, int columnn);
	/**
	 * @brief maak achtergrond zwart
	 *
	 * @param x -- De rij positie van 2D array
	 * @param y -- De colom positie van 2D aray
	 *
	 **/
	void drawIdle(int row, int columnn);
};

#endif
