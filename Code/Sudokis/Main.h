/*
 * Main.h
 *
 *  Created on: 16 apr. 2019
 *      Author: gerja
 */

#ifndef MAIN_H_
#define MAIN_H_

#define timerBase 0x10002000

#include "typedefs.h"
#include <stdio.h>
#include <altera_up_avalon_video_dma_controller.h>
#include <altera_up_avalon_video_pixel_buffer_dma.h>
#include <altera_up_avalon_parallel_port.h>
#include <unistd.h>
#include <HAL/inc/sys/alt_timestamp.h>
#include <HAL/inc/sys/alt_sys_init.h>
#include "stepper.h"
#include "SubImage.h"
#include "Image.h"
#include "OCR.h"

#include <math.h>

void init();
int constrain(int x, int a, int b);
void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, boolean on);
unsigned long micros();
void drawPixel(int x,int y,bool on);
void drawPixelRaw(int x,int y,uint16_t value);
void sleep();
void learnOCR();
void testOCR();

#endif /* MAIN_H_ */