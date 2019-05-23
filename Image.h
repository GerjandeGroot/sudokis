/*
 * Image.h
 *
 *  Created on: 17 apr. 2019
 *      Author: gerja
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include "typedefs.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stack>
#include <io.h>
#include "standard_functions.h"

class SubImage;

class Image {
private:
	uint8_t *imageData = 0;

public:
	uint16_t width;
	uint16_t height;

	Image(uint16_t width, uint16_t height);
	virtual ~Image();

	void setPixel(uint16_t x, uint16_t y, uint16_t value);
	void setPixelRaw(uint16_t x, uint16_t y, uint8_t value);
	uint8_t getPixel(uint16_t x, uint16_t y);
	void loadImage();
	void resize(uint16_t newWidth, uint16_t newHeight);
	void createData();
	void copy(Image *newImage);
	void draw(uint16_t x, uint16_t y);
	SubImage extract();
	void clearImage();
	bool blackPixels();
};

#include "SubImage.h"

#endif /* IMAGE_H_ */
