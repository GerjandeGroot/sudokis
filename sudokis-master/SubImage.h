/*
 * SubImage.h
 *
 *  Created on: 21 apr. 2019
 *      Author: gerja
 */

#ifndef SUBIMAGE_H_
#define SUBIMAGE_H_

#include "Image.h"
#include "typedefs.h"

class SubImage: public Image {
public:
    /*
	* Position on image
	*/
	uint16_t x, y;
	/*
	* Constructor
	* x,y: position on top image
	* width, height: size
	*/
	SubImage(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
	virtual ~SubImage();
};

#endif /* SUBIMAGE_H_ */
