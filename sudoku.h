#ifndef SUDOKU_H_
#define SUDOKU_H_

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "sudoku.h"
#include <time.h>
#include <string>
#include <unistd.h>
#include <sstream>
#include "Main.h"

#define WHITE 	0xffffff
#define BLACK 	0x000000
#define YELLOW	0x00ff00
#define BLUE	0x0000ff
#define UNKNOWN	0xf0f0f0

class Sudoku {
private:
	int grid[9][9];
public:
	/**
	 * @brief print sudoki grid op het scherm
	 *
	 * @param x -- Coordinate x positie
	 * @param y -- Coordinate x positie
	 *
	 **/
	void printSudokuGrid(int x, int y);
	void resetScreen();
	void printSolutionToSudokuGrid();
	void create2DArray();
	/**
		 * @brief plaatst waarde in een 2D array
		 *
		 * @param x -- De rij positie van 2D array
		 * @param y -- De kolom positie van 2D aray
		 *
		 **/
	void addNumberTo2DArray(int x, int y, int value);
	/**
		 * @brief convert een integer naar een string
		 *
		 * @param num --  De int waarde die converteerd moet worden
		 *
		 **/
	char* itoa(int num);
	bool solve();
	bool solveCell(int x, int y);
	bool checkNumber(int x, int y, int i);
	bool posElim(int x, int y, int i);
	void reset2Darray();
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
		 * @brief plaatst waarde in een 2D array
		 *
		 * @param x -- De rij positie van 2D array
		 * @param y -- De colom positie van 2D aray
		 *
		 **/
	void clearNewNumber(int row, int columnn);
	void drawNewNumber(int row, int columnn);
};
#endif