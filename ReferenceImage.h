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
#include "standard_functions.h"

class Image;

class ReferenceImage {
private:
	uint8_t imageData[imageDataSize][imageDataSize];

	/*
	 * zet de score van een pixel in de referenceimage
	 * x: positie (0-19)
	 * y: positie (0-19)
	 */
	void setScore(uint8_t x, uint8_t y, uint8_t value);
	/*
	 * lees waarde uit referenceimage
	 * x: positie (0-19)
	 * y: positie (0-19)
	 * return: score van pixel
	 */
	uint8_t getScore(uint8_t x, uint8_t y);

public:
	ReferenceImage();
	/*
	 * constructor
	 * address: pointer to data reference image
	 */
	ReferenceImage(uint32_t address);
	/*
	 * teken refference image op scherm
	 * x: x positie (0-320)
	 * y: y positie (0-240)
	 */
	void draw(uint16_t x, uint16_t y);
	/*
	 * vergelijk image met reference image en genereer score
	 * image: pointer naar image
	 * return: score
	 */
	uint32_t generateScore(Image *image);
	/*
	 * pas de referenceimage aan op basis van meegegeven image
	 * image: pointer naar image
	 */
	void correct(Image *image);
	/*
	 * sla referenceimage op door alles naar console te printen
	 */
	void save();
};

#include "Image.h"

#endif /* REFERENCEIMAGE_H_ */
