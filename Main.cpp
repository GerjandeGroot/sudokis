#include "Main.h"

//alt_up_av_config_dev* av = alt_up_av_config_open_dev("");

uint16_t map(uint16_t x, uint16_t in_max, uint16_t out_max) {
	return x * out_max / in_max;
}

void Main::startTimer() {
	IOWR(timerBase, 2, 0xFFFF);
	IOWR(timerBase, 3, 0xFFFF);
	IOWR(timerBase, 1, 0b110);
	int n = IORD(timerBase, 0);
	while (n) {
		if (n & 1)
			printf("1");
		else
			printf("0");

		n >>= 1;
	}
	printf("\n");
}

void Main::drawPixel(int x, int y, bool on) {
	int color;
	if (on) {
		color = 0xFFFFFF;
	} else {
		color = 0;
	}
	alt_up_pixel_buffer_dma_draw(pb, color, x, y);
}

void Main::drawPixelRaw(int x, int y, uint16_t value) {
	alt_up_pixel_buffer_dma_draw(pb, value, x, y);
}

void Main::drawPixelRaw(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
	r = map(r, 255, 31);
	g = map(g, 255, 63);
	b = map(b, 255, 31);
	uint16_t color = 0;
	color |= (r & 0b11111) << 11;
	color |= (g & 0b111111) << 5;
	color |= (b & 0b11111);
	alt_up_pixel_buffer_dma_draw(pb, color, x, y);
}

uint16_t Main::readPixel(uint16_t x, uint16_t y) {
	uint32_t addr = 0;
	addr += ((x & pb->x_coord_mask) << pb->x_coord_offset);
	addr += ((y & pb->y_coord_mask) << pb->y_coord_offset);
	return IORD_16DIRECT(pb->back_buffer_start_address, addr);
}

void Main::init() {
	printf("text: %d\n", dma);
	printf("greenLeds: %d\n", greenLeds);
	printf("expansion: %d\n", expansion);
	printf("redLeds: %d\n", redLeds);
	//printf("av: %x\n", av);
	printf("keys: %x\n", keys);
	printf("switches: %x\n", switches);
	printf("ps2: %x\n", ps2);
	startTimer();
	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(10, OUTPUT);

	setRGB(false, true, false);

	Robot robot;

	robot.home();
	//BELANGRIJKE WAARDE MAX X = -10250, 	MAX Y = 1800!!!!
	//BELANGRIJKE WAARDE MIN X = -540, 		MIN Y = 315!!!!

	sleep();

	alt_up_parallel_port_set_port_direction(expansion, 0xFFFFFF);

	while (1) {
		clearScreen();
		alt_up_video_dma_draw_string(dma, "Select program", 0, 0, 0);
		sleep();
		clearScreen();

		if (alt_up_parallel_port_read_data(switches) & (1 << 16)) {
			testOCR();
		} else if (alt_up_parallel_port_read_data(switches) & (1 << 17)) {
			learnOCR();
		} else if (alt_up_parallel_port_read_data(switches) & (1 << 14)) {
			testSudoku();
		} else if (alt_up_parallel_port_read_data(switches) & (1 << 15)) {
			break;
		} else if (alt_up_parallel_port_read_data(switches) & (1 << 13)) {
			rgbTest();
		}

	}
}

void Main::rgbTest() {
	printf("start rgbing\n");
	digitalWrite(8, 1);
	digitalWrite(9, 1);
	usleep(10000000);
	while (1) {
		for (int r = 0; r < 8; ++r) {
			digitalWrite(8, r & 0b1);
			digitalWrite(9, r & 0b10);
			digitalWrite(10, r & 0b100);
			usleep(2000000);
		}
	}

}

void Main::setRGB(bool r, bool g, bool b) {
	digitalWrite(8, r);
	digitalWrite(9, g);
	digitalWrite(10, b);
}

int Main::constrain(int x, int a, int b) {
	if (x < a)
		x = a;
	if (x > b)
		x = b;
	return x;
}

void Main::pinMode(uint8_t pin, uint8_t mode) {
	printf("%d\n", pin);
	if (mode == INPUT) {
		alt_up_parallel_port_set_port_direction(expansion,
				alt_up_parallel_port_read_direction(expansion) & ~(1 << pin));

	} else if (mode == OUTPUT) {
		alt_up_parallel_port_set_port_direction(expansion,
				alt_up_parallel_port_read_direction(expansion) | (1 << pin));
	}
}

void Main::digitalWrite(uint8_t pin, boolean on) {
	if (on) {
		alt_up_parallel_port_write_data(expansion,
				alt_up_parallel_port_read_data(expansion) | (1 << pin));
	} else {
		alt_up_parallel_port_write_data(expansion,
				alt_up_parallel_port_read_data(expansion) & ~(1 << pin));
	}
}

bool Main::digitalRead(uint8_t pin) {
	return alt_up_parallel_port_read_data(expansion) & (1 << pin);
}

unsigned long Main::micros() {
	IOWR(timerBase, 4, 1);
	return 0xFFFFFFFF - (((IORD(timerBase,5) << 16) | IORD(timerBase, 4)) / 50);
}

void Main::clearScreen() {
	alt_up_pixel_buffer_dma_clear_screen(pb, 0);
	alt_up_video_dma_screen_clear(dma, 0);
}

void Main::sleep() {
	usleep(500000);
	printf("sleep: press button to continue.\n");
	while (1) {
		if (alt_up_parallel_port_read_data(keys) & 0b10) {
			return;
		}
	}
}

void Main::testSudoku() {
	Sudoku sudoku;
	clearScreen();
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
			drawPixelRaw(guess * 22 + i, 20, 255, 0, 0);
		}
		object.draw(0, 50);
		bool run = 1;
		while (run) {
			for (uint8_t i = 1; i < 10; i++) {
				if (alt_up_parallel_port_read_data(switches) & (1 << i)) {
					usleep(100000);
					while (alt_up_parallel_port_read_data(switches) & (1 << i)) {
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

int Main::testOCR() {
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
	Sudoku sudoku;
	sudoku.create2DArray();
	sudoku.printSudokuGrid(179, 19);
	while (image.blackPixels()) {
		SubImage object = image.extract();
		if (object.width < 5 || object.height < 10)
			continue;
		if (object.width > 20 || object.height > 20)
			continue;
		uint8_t guess = ocr.recognizeNumber(&object);
		sudoku.drawMainNumber((object.x - grid.x) / (grid.width / 9),
				(object.y - grid.y) / (grid.height / 9));
		sudoku.addNumberTo2DArray((object.x - grid.x) / (grid.width / 9),
				(object.y - grid.y) / (grid.height / 9), guess);
	}
	sudoku.solve();
}

//Functie om een integer naar een char te converteren
char* Main::itoa(int num) {
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

void Main::drawString(uint16_t x, uint16_t y, int text) {
	alt_up_video_dma_draw_string(dma, itoa(text), x, y, 0);
}
