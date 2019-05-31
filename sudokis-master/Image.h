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

	uint16_t firstBlackPixelX;
	uint16_t firstBlackPixelY;

public:
	uint16_t width;
	uint16_t height;

	/*
	 * constructor image
	 * width: breedte van de foto
	 * height: hooghte van de foto
	 */
	Image(uint16_t width, uint16_t height);
	/*
	 * deconstructor
	 */
	virtual ~Image();

	/*
	 * zet een pixel in de image en zet kleur om in zwart wit
	 * x: positie (0-width-1)
	 * y: positie (0-height-1)
	 * value: color 16 bit
	 */
	void setPixel(uint16_t x, uint16_t y, uint16_t value);
	/*
	 * zet een pixel in de image
	 * x: positie (0-width-1)
	 * y: positie (0-height-1)
	 * value: 0 zwart - 1 wit
	 */
	void setPixelRaw(uint16_t x, uint16_t y, uint8_t value);
	/*
	 * lees pixel in image
	 * x: positie (0-width-1)
	 * y: positie (0-height-1)
	 * return: 0 zwart - 1 wit
	 */
	uint8_t getPixel(uint16_t x, uint16_t y);
	/*
	 * lees image uit de pixelbuffer
	 */
	void loadImage();
	/*
	 * resize image
	 * newWidth: nieuwe breedte
	 * newHeight: nieuwe hoogte
	 */
	void resize(uint16_t newWidth, uint16_t newHeight);
	/*
	 * create space for imagedata
	 */
	void createData();
	/*
	 * copy image
	 * newImage: pointer naar image
	 */
	void copy(Image *newImage);
	/*
	 * draw image on screen
	 * x: positie op scherm (0-320)
	 * y: positie op scherm (0-240)
	 */
	void draw(uint16_t x, uint16_t y);
	/*
		 * draw image on screen inverted colors
		 * x: positie op scherm (0-320)
		 * y: positie op scherm (0-240)
		 */
	void drawInverted(uint16_t x, uint16_t y);
	/*
	 * extract een object uit de foto
	 * een object is een groep zwaerte pixels aan elkaar verbonden
	 * return: een sub foto
	 */
	SubImage extract();
	/*
	 * clears image
	 */
	void clearImage();
	/*
	 * check of er nog zwarte pixels aanwezig zijn
	 * return: true als er zwarte pixels aanwezig zijn
	 */
	bool blackPixels();
};

#include "SubImage.h"

#endif /* IMAGE_H_ */
