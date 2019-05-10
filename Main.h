/*
 * Main.h
 *
 *  Created on: 16 apr. 2019
 *      Author: gerja
 */

#ifndef MAIN_H_
#define MAIN_H_


#define timerBase 0x10002000

#include "Robot.h"
#include "typedefs.h"
#include <stdio.h>
#include <altera_up_avalon_video_dma_controller.h>
#include <altera_up_avalon_video_pixel_buffer_dma.h>
#include <altera_up_ps2_keyboard.h>
#include <altera_up_avalon_ps2.h>
#include <altera_up_avalon_parallel_port.h>
#include <unistd.h>
#include <HAL/inc/sys/alt_timestamp.h>
#include <HAL/inc/sys/alt_sys_init.h>
#include "stepper.h"
#include "SubImage.h"
#include "Image.h"
#include "OCR.h"
#include "sudoku.h"
#include "includes.h"
#include <math.h>

class Main {
public:
	alt_up_parallel_port_dev* greenLeds = alt_up_parallel_port_open_dev("/dev/Green_LEDs");
	alt_up_parallel_port_dev* redLeds = alt_up_parallel_port_open_dev("/dev/Red_LEDs");
	alt_up_parallel_port_dev* keys = alt_up_parallel_port_open_dev("/dev/Pushbuttons");
	alt_up_parallel_port_dev* switches = alt_up_parallel_port_open_dev("/dev/Slider_Switches");
	alt_up_parallel_port_dev* expansion = alt_up_parallel_port_open_dev("/dev/Expansion_JP5");
	alt_up_pixel_buffer_dma_dev* pb = alt_up_pixel_buffer_dma_open_dev("/dev/VGA_Subsystem_VGA_Pixel_DMA");
	alt_up_video_dma_dev* dma = alt_up_video_dma_open_dev("/dev/VGA_Subsystem_Char_Buf_Subsystem_Char_Buf_DMA");
	alt_up_ps2_dev* ps2 = alt_up_ps2_open_dev("/dev/PS2_Port");
	//alt_up_pixel_buffer_dma_dev* av = alt_up_pixel_buffer_dma_open_dev("/dev/Video_In_Subsystem_Video_In_DMA");

	void rgbTest();
	void startTimer();
	void drawPixelRaw(int x,int y,uint8_t r, uint8_t g, uint8_t b);
	void init();
	int constrain(int x, int a, int b);
	void pinMode(uint8_t pin, uint8_t mode);
	void digitalWrite(uint8_t pin, boolean on);
	bool digitalRead(uint8_t pin);
	unsigned long micros();
	void drawPixel(int x,int y,bool on);
	void drawPixelRaw(int x,int y,uint16_t value);
	void sleep();
	void microDelay(uint16_t time);
	void learnOCR();
	int testOCR();
	void clearScreen();
	uint16_t readPixel(uint16_t x, uint16_t y);
	void drawString(uint16_t x, uint16_t y, int text);
	char* itoa(int num);
	void testSudoku();
	void setRGB(bool r, bool g, bool b);
	void drawNumberTest();

};

static Main top;

#endif /* MAIN_H_ */
