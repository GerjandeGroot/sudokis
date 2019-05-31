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

class Image;

/*
 * OCR is een library voor het leren en herkennen van getallen.
 */

class OCR {
private:
	ReferenceImage referenceImages[characters];
public:
	OCR();
	/*
	 * teken alle referenceimages horizontaal naast elkaar
	 * x: x positie op het scherm (0-320)
	 * y: y positie op het scherm (0-240)
	 */
	void draw(uint16_t x, uint16_t y);
	/*
	 * return refference image
	 * i: nummer 1-9 (0-8)
	 */
	ReferenceImage* getReferenceImage(uint8_t i);
	/*
	 * probeert het getal te raden
	 * image: foto van een object
	 * return: getal waar het object het meest op lijkt
	 */
	uint8_t recognizeNumber(Image *image);
	/*
	 * sla de refferenceimages op door alles naar de console te printen
	 */
	void save();
};

#endif /* OCR_H_ */
