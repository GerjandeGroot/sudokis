/*
 * ReferenceImage.cpp
 *
 *  Created on: 20 apr. 2019
 *      Author: gerja
 */

#include "ReferenceImage.h"

ReferenceImage::ReferenceImage() {};

ReferenceImage::ReferenceImage(uint32_t address) {
	for (int dx = 0; dx < imageDataSize; ++dx) {
		for (int dy = 0; dy < imageDataSize; ++dy) {
			setScore(dy,dx,(uint8_t)IORD_8DIRECT(address,dy*imageDataSize+dx));
		}
	}
}

void ReferenceImage::setScore(uint8_t x, uint8_t y, uint8_t score) {
	if(x>=imageDataSize || y>=imageDataSize) return;
	imageData[x][y] = score;
}

uint8_t ReferenceImage::getScore(uint8_t x, uint8_t y) {
	if(x>=imageDataSize || y>=imageDataSize) return 0;
	return imageData[x][y];
}

uint32_t ReferenceImage::generateScore(Image *image) {
	int score = 0;
	for (uint8_t x = 0; x < imageDataSize; ++x) {
		for (uint8_t y = 0; y < imageDataSize; ++y) {
			if(image->getPixel(x,y)) {
				score += getScore(x,y);
			} else {
				score += 255 - getScore(x,y);
			}
		}
	}
	return score;
}

void ReferenceImage::correct(Image *image) {
	for (int x = 0; x < image->width; ++x) {
		for (int y = 0; y < image->height; ++y) {
			int score = getScore(x,y);
			if(image->getPixel(x,y)){
				score += 10;
			} else {
				score -= 50;
			}
			if(score < 0) score = 0;
			if(score > 255) score = 255;
			setScore(x,y,score);
		}
	}
}

void ReferenceImage::draw(uint16_t x, uint16_t y) {
	for (int dx = 0; dx < imageDataSize; ++dx) {
		for (int dy = 0; dy < imageDataSize; ++dy) {
			drawPixelRGB(x+dx,y+dy,getScore(dx,dy),getScore(dx,dy),getScore(dx,dy));
		}
	}
}

void ReferenceImage::save() {
	for (int dx = 0; dx < imageDataSize; ++dx) {
		for (int dy = 0; dy < imageDataSize; ++dy) {
			printf("%d, ", getScore(dx,dy));
		}
	}
}
