#ifndef SUDOKU_H_
#define SUDOKU

#include <altera_up_avalon_video_dma_controller.h>
#include <altera_up_avalon_video_pixel_buffer_dma.h>

class Sudoku {
public:
	void resetScreen();
	void printSudokuGrid(int x, int y);
	void greateGrid();
	void addNumberToGrid(int x, int y, int value);
	void fillRandomNumber(int x, int y, int gridX, int gridY, int randNummer);
	char* itoa(int num);
	bool solve();
	bool solveCell(int x, int y);
	bool checkNumber(int x, int y, int i);
	bool posElim(int x, int y, int i);
	void testSudoku1();
	void testSudoku2();
	void testSudoku3();
	void testSudoku4();
	void reset2Darray();
	void drawMainNumber(int row, int columnn);
	void clearMainNumber(int row, int columnn);
	void drawNewNumber(int row, int columnn);
protected:

private:
};

#endif
