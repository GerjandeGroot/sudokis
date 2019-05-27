#include "sudoku.h"

Sudoku::Sudoku(){
	create2DArray();
}

//Functie om sudoku grid op het scherm te printen
void Sudoku::printSudokuGrid() {

	for (int j = 0; j < 9; j++) {
		for (int i = 0; i < 9; i++) {
			alt_up_pixel_buffer_dma_draw_rectangle(pb, xPosGrid + i * 12, yPosGrid + j * 12,
					xPosGrid + i * 12 + 12, yPosGrid + j * 12 + 12, WHITE, 0);
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			alt_up_pixel_buffer_dma_draw_rectangle(pb, xPosGrid + i * 36, yPosGrid + j * 36,
					xPosGrid + i * 36 + 36, yPosGrid + j * 36 + 36, YELLOW, 0);
		}
	}
}

void Sudoku::printNumber(int x,int y) {
	if(grid[x][y] == 0) return;
	int newX = x * 3 + xPosNumbers;
	int newY = y * 3 + yPosNumbers;
	drawString(newX,newY,grid[x][y]); // het \em grid gaat per stappen van 3
}

//Functie om een een 2D array aan te maken, standaard gevuld met nullen
void Sudoku::create2DArray() {
	int i, j;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			grid[i][j] = 0;
			mainNumbers[i][j] = 0;
		}
	}
}

//Functie om een nummer in de 2D array te zetten en weer te geven in sudoku grid
void Sudoku::addMainNumber(int x, int y, int value) {
	if (x > 9 || y > 9) {
		printf("ERROR number to high");
	} else {
		mainNumbers[x][y] = value;
		grid[x][y] = value;
		drawMainNumber(x,y);
		printNumber(x,y);
	}
}

//Functie om een nummer in de 2D array te zetten en weer te geven in sudoku grid
void Sudoku::addNumber(int x, int y, int value) {
	if (x > 9 || y > 9) {
		printf("ERROR number to high");
	} else {
		grid[x][y] = value;
		printNumber(x,y);
	}
}

void Sudoku::printSolutionToSudokuGrid() {
	clearScreen();
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 0; x++) {
			drawMainNumber(x,y);
		}
	}
}

void Sudoku::drawMainNumber(int row, int columnn) {
	alt_up_pixel_buffer_dma_draw_box(pb, xPosGrid+1 + row * 12, yPosGrid+1 + columnn * 12,
			xPosGrid+1 + row * 12 + 10, yPosGrid+1 + columnn * 12 + 10, BLUE, 0);
}

void Sudoku::drawBusy(int row, int columnn) {
	alt_up_pixel_buffer_dma_draw_box(pb, xPosGrid+1 + row * 12, yPosGrid+1 + columnn * 12,
				xPosGrid+1 + row * 12 + 10, yPosGrid+1 + columnn * 12 + 10, UNKNOWN, 0);
}

void Sudoku::drawIdle(int row, int columnn) {
	alt_up_pixel_buffer_dma_draw_box(pb, xPosGrid+1 + row * 12, yPosGrid+1 + columnn * 12,
					xPosGrid+1 + row * 12 + 10, yPosGrid+1 + columnn * 12 + 10, BLACK, 0);
}

bool Sudoku::solve() {
	for (int x = 0; x < 9; x++) {
		for (int y = 0; y < 9; y++) {
			grid[x][y] = mainNumbers[x][y];
		}
	}

	bool changed = true;
	while (changed) {
		changed = false;

		for (int x = 0; x < 9; x++) {
			for (int y = 0; y < 9; y++) {

				if (grid[x][y] > 0)
					continue;

				if (solveCell(x, y)) {
					changed = true;
				}
			}
		}
	}
	return true;
}

bool Sudoku::solveCell(int x, int y) {
	uint8_t solution = 0;
	uint8_t err;
	struct Message message;
	for (int i = 1; i <= 9; i++) {
		if (checkNumber(x, y, i)) {
			if (solution > 0) {
				solution = 10;
			} else {
				solution = i;
			}
			if (posElim(x, y, i)) {
				grid[x][y] = i;
				addNumber(x, y, i);
				return true;
			}
		}
	}
	if (solution < 10 && solution > 0) {
		grid[x][y] = solution;
		addNumber(x, y, solution);
		return true;
	}
	return false;
}

bool Sudoku::checkNumber(int x, int y, int i) {
	if (grid[x][y] > 0)
		return false;

	for (int j = 0; j < 9; j++) {
		if (grid[x][j] == i) {
			return false;
		}
	}
	for (int j = 0; j < 9; j++) {
		if (grid[j][y] == i) {
			return false;
		}
	}
	int gx = x / 3;
	int gy = y / 3;

	for (int dx = 0; dx < 3; dx++) {
		for (int dy = 0; dy < 3; dy++) {
			if (grid[gx * 3 + dx][gy * 3 + dy] == i) {
				return false;
			}
		}
	}
	return true;
}

bool Sudoku::posElim(int x, int y, int i) {
	bool succes = true;
	for (int j = 0; j < 9; j++) {
		if (j == x)
			continue;
		if (checkNumber(j, y, i)) {
			succes = false;
		}
	}
	if (succes)
		return true;

	succes = true;
	for (int j = 0; j < 9; j++) {
		if (j == y)
			continue;
		if (checkNumber(x, j, i)) {
			succes = false;
		}
	}
	if (succes)
		return true;

	int gx = x / 3;
	int gy = y / 3;

	succes = true;
	for (int dx = 0; dx < 3; dx++) {
		for (int dy = 0; dy < 3; dy++) {
			if (x == gx * 3 + dx && gy * 3 + dy == y)
				continue;
			if (checkNumber(gx * 3 + dx, gy * 3 + dy, i)) {
				succes = false;
			}
		}
	}
	if (succes)
		return true;
	return false;
}

void Sudoku::reset2Darray() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			grid[j][i] = 0;
		}
	}
}
