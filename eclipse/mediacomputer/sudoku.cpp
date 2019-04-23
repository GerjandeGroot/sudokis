#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "sudoku.h"
#include <time.h>
#include <string>
#include <unistd.h>
#include <sstream>

#define WHITE 	0xffffff
#define BLACK 	0x000000
#define YELLOW	0x00ff00
#define BLUE	0x0000ff
#define UNKNOWN	0xf0f0f0

alt_up_pixel_buffer_dma_dev* pb = alt_up_pixel_buffer_dma_open_dev(
		"/dev/VGA_Subsystem_VGA_Pixel_DMA");
alt_up_video_dma_dev* dma = alt_up_video_dma_open_dev(
		"/dev/VGA_Subsystem_Char_Buf_Subsystem_Char_Buf_DMA");

int grid[9][9];

void resetScreen();
void printSudokuGrid(int x, int y);
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

int main() {
//	alt_up_video_dma_dev* dma = alt_up_video_dma_open_dev(
//			"/dev/VGA_Subsystem_Char_Buf_Subsystem_Char_Buf_DMA");
	resetScreen();
	create2DArray();

	printSudokuGrid(179, 19);

	//while(1){
	testSudoku1();
//		usleep(5000000);
//		reset2Darray();
//		alt_up_video_dma_screen_clear(dma, 0);
//		testSudoku1();
//
//	usleep(5000000);
//	reset2Darray();
//		alt_up_video_dma_screen_clear(dma, 0);
//		testSudoku1();

	return 0;
}

//Functie om het scherm te verversen
void resetScreen() {
	alt_up_video_dma_screen_clear(dma, 0);
	alt_up_pixel_buffer_dma_clear_screen(pb, 0);
}

//Functie om sudoku grid op het scherm te printen
void printSudokuGrid(int x, int y) {

	for (int j = 0; j < 9; j++) {
		for (int i = 0; i < 9; i++) {
			alt_up_pixel_buffer_dma_draw_rectangle(pb, x + i * 12, y + j * 12,
					x + i * 12 + 12, y + j * 12 + 12, WHITE, 0);
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			alt_up_pixel_buffer_dma_draw_rectangle(pb, x + i * 36, y + j * 36,
					x + i * 36 + 36, y + j * 36 + 36, YELLOW, 0);
		}
	}
}

//Functie om een een 2D array aan te maken, standaard gevuld met nullen
void create2DArray() {
	int i, j;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			grid[i][j] = 0;
		}
	}
}

//Functie om een nummer in de 2D array te zetten en weer te geven in sudoku grid
void addNumberTo2DArray(int x, int y, int value) {
	if (x > 9 || y > 9) {
		printf("ERROR number to high");
	} else {
		grid[x][y] = value;
		int newX = x * 3 + 46;
		int newY = y * 3 + 6;
		alt_up_video_dma_draw_string(dma, itoa(value), newX, newY, 0); // het \em grid gaat per stappen van 3
	}
}

void printSolutionToSudokuGrid() {
	resetScreen();
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 0; x++) {
			int value = grid[x][y];
			int newX = x * 3 + 46;
			int newY = y * 3 + 6;
			alt_up_video_dma_draw_string(dma, itoa(value), newX, newY, 0);
		}
	}
}

void drawMainNumber(int row, int columnn) {
	alt_up_pixel_buffer_dma_draw_box(pb, 180 + row * 12, 20 + columnn * 12,
			180 + row * 12 + 10, 20 + columnn * 12 + 10, BLUE, 0);
}

void drawNewNumber(int row, int columnn) {
	alt_up_pixel_buffer_dma_draw_box(pb, 180 + row * 12, 20 + columnn * 12,
			180 + row * 12 + 10, 20 + columnn * 12 + 10, UNKNOWN, 0);
}

void clearMainNumber(int row, int columnn) {
	alt_up_pixel_buffer_dma_draw_box(pb, 180 + row * 12, 20 + columnn * 12,
			180 + row * 12 + 10, 20 + columnn * 12 + 10, BLACK, 0);
}
//Functie om een integer naar een char te converteren
char* itoa(int num) {
	static char str[5];
	int i = 0;
	int base = 10;

	if (num == 0) {
		str[i++] = '0';
		str[i] = '\0';
		return str;
	}
	while (num != 0) {
		int rem = num % base;
		str[i++] = rem + '0';
		num = num / base;
	}
	str[i] = '\0';
	return str;
}

//Functie om willekeurige cijfers in het grid toe te voegen
void fillRandomNumber(int x, int y, int gridX, int gridY, int randNummer) {

	int newX = x * 3 + 46;
	int newY = y * 3 + 12;

	alt_up_video_dma_draw_string(dma, itoa(randNummer), newX, newY, 0);
	addNumberTo2DArray(gridX - 1, gridY - 1, randNummer);
}

bool solve() {
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

bool solveCell(int x, int y) {
	int solution = 0;
	for (int i = 1; i <= 9; i++) {
		if (checkNumber(x, y, i)) {
			if (solution > 0) {
				solution = 10;
			} else {
				solution = i;
			}
			if (posElim(x, y, i)) {
				grid[x][y] = i;
				drawNewNumber(x, y);
				addNumberTo2DArray(x, y, i);
				usleep(1000000);
				clearMainNumber(x, y);
				addNumberTo2DArray(x, y, i);
				return true;
			}
		}
	}
	if (solution < 10 && solution > 0) {
		grid[x][y] = solution;
		drawNewNumber(x, y);
		addNumberTo2DArray(x, y, solution);
		usleep(1000000);
		clearMainNumber(x, y);
		addNumberTo2DArray(x, y, solution);
		return true;
	}
	return false;
}

bool checkNumber(int x, int y, int i) {
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

bool posElim(int x, int y, int i) {
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

void reset2Darray() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			grid[j][i] = 0;
		}
	}
}

void testSudoku1() {
	int row = 0;
	//rij 1
	drawMainNumber(0, row);
	addNumberTo2DArray(0, row, 5);
	drawMainNumber(1, row);
	addNumberTo2DArray(1, row, 3);
	drawMainNumber(4, row);
	addNumberTo2DArray(4, row, 7);
	row++;
	//rij 2
	drawMainNumber(0, row);
	addNumberTo2DArray(0, row, 6);
	drawMainNumber(3, row);
	addNumberTo2DArray(3, row, 1);
	drawMainNumber(4, row);
	addNumberTo2DArray(4, row, 9);
	drawMainNumber(5, row);
	addNumberTo2DArray(5, row, 5);
	row++;
	//rij 3
	drawMainNumber(1, row);
	addNumberTo2DArray(1, row, 9);
	drawMainNumber(2, row);
	addNumberTo2DArray(2, row, 8);
	drawMainNumber(7, row);
	addNumberTo2DArray(7, row, 6);
	row++;
	//rij 4
	drawMainNumber(0, row);
	addNumberTo2DArray(0, row, 8);
	drawMainNumber(4, row);
	addNumberTo2DArray(4, row, 6);
	drawMainNumber(8, row);
	addNumberTo2DArray(8, row, 3);
	row++;
	//rij 5
	drawMainNumber(0, row);
	addNumberTo2DArray(0, row, 4);
	drawMainNumber(3, row);
	addNumberTo2DArray(3, row, 8);
	drawMainNumber(5, row);
	addNumberTo2DArray(5, row, 3);
	drawMainNumber(8, row);
	addNumberTo2DArray(8, row, 1);
	row++;
	//rij 6
	drawMainNumber(0, row);
	addNumberTo2DArray(0, row, 7);
	drawMainNumber(4, row);
	addNumberTo2DArray(4, row, 2);
	drawMainNumber(8, row);
	addNumberTo2DArray(8, row, 6);
	row++;
	//rij 7
	drawMainNumber(1, row);
	addNumberTo2DArray(1, row, 6);
	drawMainNumber(6, row);
	addNumberTo2DArray(6, row, 2);
	drawMainNumber(7, row);
	addNumberTo2DArray(7, row, 8);
	row++;
	//rij 8
	drawMainNumber(3, row);
	addNumberTo2DArray(3, row, 4);
	drawMainNumber(4, row);
	addNumberTo2DArray(4, row, 1);
	drawMainNumber(5, row);
	addNumberTo2DArray(5, row, 9);
	drawMainNumber(8, row);
	addNumberTo2DArray(8, row, 5);
	row++;

	//rij 9
	drawMainNumber(4, row);
	addNumberTo2DArray(4, row, 8);
	drawMainNumber(7, row);
	addNumberTo2DArray(7, row, 7);
	drawMainNumber(8, row);
	addNumberTo2DArray(8, row, 9);

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int test = grid[j][i];
			alt_up_video_dma_draw_string(dma, itoa(test), j, i + 1, 0);
		}
	}
	usleep(5000000);
	solve();
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int test = grid[j][i];
			alt_up_video_dma_draw_string(dma, itoa(test), j, i + 1, 0);
		}
	}
}

void testSudoku2() {
	int row = 0;
	//rij 1
	drawMainNumber(3, row);
	addNumberTo2DArray(3, row, 2);
	drawMainNumber(4, row);
	addNumberTo2DArray(4, row, 7);
	drawMainNumber(5, row);
	addNumberTo2DArray(5, row, 1);
	row++;
	//rij 2
	drawMainNumber(5, row);
	addNumberTo2DArray(5, row, 6);
	drawMainNumber(8, row);
	addNumberTo2DArray(8, row, 4);
	row++;
	//rij 3
	drawMainNumber(1, row);
	addNumberTo2DArray(1, row, 9);
	drawMainNumber(2, row);
	addNumberTo2DArray(2, row, 8);
	drawMainNumber(7, row);
	addNumberTo2DArray(7, row, 6);
	row++;
	//rij 4
	drawMainNumber(0, row);
	addNumberTo2DArray(0, row, 8);
	drawMainNumber(4, row);
	addNumberTo2DArray(4, row, 6);
	drawMainNumber(8, row);
	addNumberTo2DArray(8, row, 3);
	row++;
	//rij 5
	drawMainNumber(0, row);
	addNumberTo2DArray(0, row, 4);
	drawMainNumber(3, row);
	addNumberTo2DArray(3, row, 8);
	drawMainNumber(5, row);
	addNumberTo2DArray(5, row, 3);
	drawMainNumber(8, row);
	addNumberTo2DArray(8, row, 1);
	row++;
	//rij 6
	drawMainNumber(0, row);
	addNumberTo2DArray(0, row, 7);
	drawMainNumber(4, row);
	addNumberTo2DArray(4, row, 2);
	drawMainNumber(8, row);
	addNumberTo2DArray(8, row, 6);
	row++;
	//rij 7
	drawMainNumber(1, row);
	addNumberTo2DArray(1, row, 6);
	drawMainNumber(6, row);
	addNumberTo2DArray(6, row, 2);
	drawMainNumber(7, row);
	addNumberTo2DArray(7, row, 8);
	row++;
	//rij 8
	drawMainNumber(3, row);
	addNumberTo2DArray(3, row, 4);
	drawMainNumber(4, row);
	addNumberTo2DArray(4, row, 1);
	drawMainNumber(5, row);
	addNumberTo2DArray(5, row, 9);
	drawMainNumber(8, row);
	addNumberTo2DArray(8, row, 5);
	row++;

	//rij 9
	drawMainNumber(4, row);
	addNumberTo2DArray(4, row, 8);
	drawMainNumber(7, row);
	addNumberTo2DArray(7, row, 7);
	drawMainNumber(8, row);
	addNumberTo2DArray(8, row, 9);

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int test = grid[j][i];
			alt_up_video_dma_draw_string(dma, itoa(test), j, i + 1, 0);
		}
	}
	usleep(5000000);
	solve();
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int test = grid[j][i];
			alt_up_video_dma_draw_string(dma, itoa(test), j, i + 1, 0);
		}
	}
}

