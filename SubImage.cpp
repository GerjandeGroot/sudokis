/*
 * SubImage.cpp
 *
 *  Created on: 21 apr. 2019
 *      Author: gerja
 */

#include "SubImage.h"

SubImage::SubImage(uint16_t x, uint16_t y, uint16_t width, uint16_t height) : Image(width, height) {
	this->x = x;
	this->y = y;
}

SubImage::~SubImage() {
	// TODO Auto-generated destructor stub
}

