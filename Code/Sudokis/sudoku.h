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
	void printSudokuGrid(int x, int y);
	void resetScreen();
	void printSolutionToSudokuGrid();
	void create2DArray();
	void addNumberTo2DArray(int x, int y, int value);
	void fillRandomNumber(int x, int y, int gridX, int gridY, int randNummer);
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
	void drawMainNumber(int row, int columnn);
	void clearMainNumber(int row, int columnn);
	void drawNewNumber(int row, int columnn);
};
#endif
