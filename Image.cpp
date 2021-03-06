/*
 * Image.cpp
 *
 *  Created on: 17 apr. 2019
 *      Author: gerja
 */

#include "Image.h"

Image::Image(uint16_t width, uint16_t height) {
	firstBlackPixelX = 0;
	firstBlackPixelY = 0;
	this->width = width;
	this->height = height;
	createData();
}

Image::~Image() {
	//delete[] imageData;
	printf("delete\n");
	free(imageData);
}

void Image::createData() {
	free(imageData);
	imageData = NULL;
	//delete[] imageData;
	//imageData = new uint8_t[(width*height)/8+1];
	//imageData = (uint8_t *) realloc(imageData,(width*height)/8+1);

	if (width < 1 || height < 1)
		return;
	printf("creating memory for image: %d\n", (width * height) / 8 + 1);
	imageData = (uint8_t *) malloc((width * height) / 8 + 1);
	if (imageData == NULL) {
		printf("error: \n");
		exit(1);
	}
}

void Image::clearImage() {
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			setPixelRaw(x, y, 1);
		}
	}
}

bool Image::blackPixels() {
	while(firstBlackPixelX < width) {
		while(firstBlackPixelY < height){
			if (!getPixel(firstBlackPixelX, firstBlackPixelY))
				return true;
			firstBlackPixelY++;
		}
		firstBlackPixelX++;
		firstBlackPixelY = 0;
	}
	return false;
}

void Image::setPixel(uint16_t x, uint16_t y, uint16_t value) {
	if (((value & (0b11111 << 11)) >> 11) > 20
			|| ((value & (0b111111 << 5)) >> 5) > 50
			|| ((value & (0b11111))) > 30) {
		setPixelRaw(x, y, 1);
	} else {
		setPixelRaw(x, y, 0);
	}
}

void Image::setPixelRaw(uint16_t x, uint16_t y, uint8_t value) {
	if (x >= width || y >= height)
		return;
	if (value) {
		imageData[(y * width + x) / 8] |= 1 << (y * width + x) % 8;
	} else {
		imageData[(y * width + x) / 8] &= ~(1 << (y * width + x) % 8);
	}
}

uint8_t Image::getPixel(uint16_t x, uint16_t y) {
	if (x >= width || y >= height)
		return 1;
	return imageData[(y * width + x) / 8] & 1 << ((y * width + x) % 8);
}

void Image::loadImage() {
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			uint16_t value = readPixel(x, y);
			setPixel(x, y, value);
		};
	};
}

void Image::resize(uint16_t newWidth, uint16_t newHeight) {
	Image newImage = Image(newWidth, newHeight);
	double widthScale = (double) newWidth / (double) width;
	double heightScale = (double) newHeight / (double) height;

	double nx = 0;
	double ny = 0;
	if (widthScale < 1) {
		newImage.clearImage();

		for (int y = 0; y < height - 1; ++y) {
			nx = 0;
			for (int x = 0; x < width - 1; ++x) {
				if (!getPixel(x, y)) {
					if (!getPixel(x + 1, y))
						newImage.setPixelRaw(nx, ny, 0);
					if (!getPixel(x, y + 1))
						newImage.setPixelRaw(nx, ny, 0);
				}
				nx += widthScale;
			}
			ny += heightScale;
		}
		newImage.draw(0, 0);
		clearScreen();
	}
	copy(&newImage);
}

void Image::copy(Image *newImage) {
	width = newImage->width;
	height = newImage->height;
	createData();

	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			setPixelRaw(x, y, newImage->getPixel(x, y));
		}
	}
}

void Image::draw(uint16_t x, uint16_t y) {
	for (int dx = 0; dx < width; ++dx) {
		for (int dy = 0; dy < height; ++dy) {
			drawPixelBW(x + dx, y + dy, getPixel(dx, dy));
		};
	};
}

void Image::drawInverted(uint16_t x, uint16_t y) {
	for (int dx = 0; dx < width; ++dx) {
		for (int dy = 0; dy < height; ++dy) {
			drawPixelBW(x + dx, y + dy, !getPixel(dx, dy));
		};
	};
}

SubImage Image::extract() {
	uint16_t xc[9000];
	uint16_t yc[9000];
	uint32_t pointer = 0;
	uint32_t checkedPointer = 0;
	uint16_t minX, minY, maxX, maxY;

	blackPixels();
	setPixelRaw(firstBlackPixelX, firstBlackPixelY, 1);
	xc[pointer] = firstBlackPixelX;
	yc[pointer] = firstBlackPixelY;
	pointer++;
	minX = firstBlackPixelX;
	minY = firstBlackPixelY;
	maxX = firstBlackPixelX;
	maxY = firstBlackPixelY;

	while (checkedPointer < pointer) {
		uint16_t x = xc[checkedPointer];
		uint16_t y = yc[checkedPointer];
		checkedPointer++;

		if (x < minX)
			minX = x;
		if (x > maxX)
			maxX = x;
		if (y < minY)
			minY = y;
		if (y > maxY)
			maxY = y;

		if (x < width - 1) {
			if (!getPixel(x + 1, y)) {
				xc[pointer] = x + 1;
				yc[pointer] = y;
				pointer++;
				setPixelRaw(x + 1, y, 1);
			}
		}
		if (x > 0) {
			if (!getPixel(x - 1, y)) {
				xc[pointer] = x - 1;
				yc[pointer] = y;
				pointer++;
				setPixelRaw(x - 1, y, 1);
			}
		}
		if (y < height - 1) {
			if (!getPixel(x, y + 1)) {
				xc[pointer] = x;
				yc[pointer] = y + 1;
				pointer++;
				setPixelRaw(x, y + 1, 1);
			}
		}
		if (y > 0) {
			if (!getPixel(x, y - 1)) {
				xc[pointer] = x;
				yc[pointer] = y - 1;
				pointer++;
				setPixelRaw(x, y - 1, 1);
			}
		}
		if (pointer > 8995)
			break;
	}
	uint16_t width = maxX - minX + 1;
	uint16_t height = maxY - minY + 1;
	SubImage subImage = SubImage(minX, minY, width, height);
	subImage.clearImage();
	printf("%d\t%d\n", minX, minY);
	printf("%d\n", pointer);
	while (pointer > 0) {
		pointer--;
		subImage.setPixelRaw(xc[pointer] - minX, yc[pointer] - minY, 0);
	}
	subImage.setPixelRaw(xc[0] - minX, yc[0] - minY, 0);
	return subImage;
}

