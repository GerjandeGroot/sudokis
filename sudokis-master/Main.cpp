#include "Main.h"

void Main::setRGB(bool r, bool g, bool b) {
	digitalWrite(8, r);
	digitalWrite(9, g);
	digitalWrite(10, b);
}

void Main::learnOCR() {
	printf("capture image\n");
	IOWR(0x10003060, 3, 0b100);
	setRGB(true, true, true);
	sleep();
	IOWR(0x10003060, 3, 0b000);

	printf("load and display image\n");
	Image image = Image(320, 240);
	image.loadImage();
	image.draw(0, 0);
	sleep();

	printf("looping through objects in photo to find grid\n");
	SubImage grid = image.extract();
	while (1) {
		if (grid.width < 230 && grid.height < 230 && grid.width > 150
				&& grid.height > 150)
			break;
		grid = image.extract();
	}
	clearScreen();
	grid.draw(0, 0);
	sleep();

	printf("load ocr\n");
	clearScreen();
	OCR ocr;

	printf("looping through objects in photo\n");
	while (image.blackPixels()) {
		SubImage object = image.extract();
		if (object.width < 5 || object.height < 10)
			continue;
		if (object.width > 20 || object.height > 20)
			continue;
		clearScreen();
		printf("Select number\n");
		ocr.draw(22, 0);
		uint8_t guess = ocr.recognizeNumber(&object);
		for (int i = 0; i < 20; ++i) {
			drawPixelRGB(guess * 22 + i, 20, 255, 0, 0);
		}
		object.draw(0, 50);
		bool run = 1;
		while (run) {
			for (uint8_t i = 1; i < 10; i++) {
				if (switchesRead(i)) {
					usleep(100000);
					while (switchesRead(i)) {
					};
					ocr.getReferenceImage(i - 1)->correct(&object);
					run = 0;
				}
			}
			if (alt_up_parallel_port_read_data(keys) & (0b100))
				ocr.save();
			if (alt_up_parallel_port_read_data(keys) & (0b1000))
				run = false;
		}
	}
	ocr.save();
	while (1) {
	};
}

void Main::sleep() {
	usleep(500000);
	//printf("sleep: press button to continue.\n");
	while (1) {
		if (alt_up_parallel_port_read_data(keys) & 0b10) {
			return;
		}
	}
}

int Main::testOCR(Sudoku *sudoku) {
	printf("load and display image\n");
	Image image = Image(320, 240);
	image.loadImage();
	image.draw(0, 0);

	printf("looping through objects in photo to find grid\n");
	SubImage grid = image.extract();
	while (1) {
		if (image.blackPixels()) {
			if (grid.width < 230 && grid.height < 230 && grid.width > 150
					&& grid.height > 150) {
				break;
			}
			grid = image.extract();
		} else {
			return -1;
		}
	}
	clearScreen();
	printf("find");

	printf("load ocr\n");
	clearScreen();
	OCR ocr;
	printf("looping through objects in photo\n");

	#define xOffset 0
	#define yOffset 0

	grid.drawInverted(xOffset,yOffset);
	sudoku->printSudokuGrid();

	while (image.blackPixels()) {
		SubImage object = image.extract();
		if (object.y > (grid.y + grid.height)) continue;
		if (object.width < 5 || object.height < 10)
			continue;
		if (object.width > 20 || object.height > 20)
			continue;
		uint8_t guess = ocr.recognizeNumber(&object);
		sudoku->addMainNumber((object.x - grid.x) / (grid.width / 9),
				(object.y - grid.y) / (grid.height / 9), guess);
		object.drawInverted(object.x+xOffset-grid.x, object.y+yOffset-grid.y);
		if (object.x > (grid.x + grid.width)) break;
	}
	sudoku->solve();
	return 0;
}

void Main::welcomeSudokis(){
		drawString(15,5,"Welcome to SUDOKIS world!");
		OSTimeDlyHMSM(0,0,0,125);

		drawString(15,5,"                                ");
		OSTimeDlyHMSM(0,0,0,125);
}


void Main::displayStartScreen() {


	drawString(5,11,"How to use this device:");
	OSTimeDlyHMSM(0,0,1,125);
	drawString(5,13,"Step 1: place your Sudoku in the robot and secure it with the magnets.");
	OSTimeDlyHMSM(0,0,1,125);
	drawString(5,14,"Step 2: Press key 1 to start the robot.");
	OSTimeDlyHMSM(0,0,1,125);
	drawString(5,16,"For emergency press key 3.");
	OSTimeDlyHMSM(0,0,1,125);
	drawString(5,17,"Reset the system by pressing key 2.");
}
