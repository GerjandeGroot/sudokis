/*
 * ReferenceImage.h
 *
 *  Created on: 20 apr. 2019
 *      Author: gerja
 */

#ifndef REFERENCEIMAGE_H_
#define REFERENCEIMAGE_H_

#define imageDataSize 20

#include "typedefs.h"

class Image;
void drawPixelRaw(int x,int y,uint8_t r, uint8_t g, uint8_t b);

class ReferenceImage {
private:
	uint8_t imageData[imageDataSize][imageDataSize];
	uint32_t address;
public:
	ReferenceImage();
	ReferenceImage(uint32_t address);
	virtual ~ReferenceImage();
	void draw(uint16_t x, uint16_t y);
	uint32_t generateScore(Image *image);
	void correct(Image *image);
	void setScore(uint8_t x, uint8_t y, uint8_t value);
	uint8_t getScore(uint8_t x, uint8_t y);
	void save();
};

#include "Image.h"
#include "Main.h"

#endif /* REFERENCEIMAGE_H_ */
