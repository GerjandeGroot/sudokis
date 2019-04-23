/*
 * OCR.h
 *
 *  Created on: 20 apr. 2019
 *      Author: gerja
 */

#ifndef OCR_H_
#define OCR_H_

#include <io.h>
#include "typedefs.h"
#include "ReferenceImage.h"


#define characters 9
#define flashBase 0x0C000000

class Image;

class OCR {
	ReferenceImage referenceImages[characters];
public:
	OCR();
	virtual ~OCR();
	void draw(uint16_t x, uint16_t y);
	ReferenceImage* getReferenceImage(uint8_t i);
	uint8_t recognizeNumber(Image *image);
	void save();
};

#endif /* OCR_H_ */
