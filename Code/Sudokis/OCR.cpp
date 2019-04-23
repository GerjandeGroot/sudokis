/*
 * OCR.cpp
 *
 *  Created on: 20 apr. 2019
 *      Author: gerja
 */

#include "OCR.h"

uint8_t data[] = {255, 195, 10, 205, 255, 255, 255, 255, 255, 255, 205, 15, 0, 55, 155, 255, 255, 255, 255, 255, 205, 15, 0, 145, 205, 255, 255, 255, 255, 255, 205, 10, 0, 55, 155, 255, 255, 255, 255, 255, 75, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 55, 155, 255, 255, 255, 255, 255, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 0, 10, 0, 55, 155, 255, 255, 255, 255, 255, 225, 225, 225, 225, 225, 225, 225, 255, 255, 255, 155, 10, 0, 55, 155, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 95, 0, 55, 155, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 125, 105, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 205, 0, 205, 255, 255, 255, 255, 255, 255, 245, 205, 20, 0, 0, 155, 255, 255, 255, 255, 255, 10, 0, 165, 255, 255, 255, 255, 255, 245, 205, 20, 0, 0, 0, 215, 255, 255, 255, 255, 255, 0, 0, 225, 255, 255, 255, 255, 245, 205, 20, 0, 0, 10, 0, 215, 255, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 245, 205, 20, 0, 15, 105, 10, 0, 155, 255, 255, 255, 255, 255, 10, 0, 255, 255, 245, 245, 205, 0, 0, 75, 225, 145, 10, 0, 215, 255, 255, 255, 255, 255, 10, 0, 0, 135, 135, 0, 0, 0, 105, 255, 245, 145, 10, 0, 215, 255, 255, 255, 255, 255, 255, 10, 0, 0, 0, 0, 0, 165, 255, 255, 245, 145, 10, 0, 215, 255, 255, 255, 255, 255, 255, 255, 10, 10, 10, 155, 255, 255, 255, 255, 255, 245, 10, 0, 215, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 205, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 205, 75, 255, 255, 255, 255, 255, 255, 255, 255, 245, 0, 0, 225, 255, 255, 255, 255, 255, 255, 0, 10, 175, 255, 255, 255, 255, 255, 255, 255, 245, 45, 0, 45, 255, 255, 255, 255, 255, 255, 0, 10, 255, 255, 255, 205, 255, 255, 255, 255, 255, 95, 0, 0, 205, 255, 255, 255, 255, 255, 0, 10, 255, 255, 255, 0, 10, 255, 255, 255, 255, 125, 0, 0, 205, 255, 255, 255, 255, 255, 0, 0, 255, 255, 185, 0, 0, 255, 255, 255, 255, 125, 0, 0, 255, 255, 255, 255, 255, 255, 0, 0, 195, 185, 35, 10, 0, 0, 205, 205, 185, 0, 0, 45, 255, 255, 255, 255, 255, 255, 65, 10, 10, 10, 10, 10, 10, 0, 0, 0, 0, 10, 0, 205, 255, 255, 255, 255, 255, 255, 255, 175, 0, 0, 55, 255, 225, 0, 0, 0, 0, 115, 205, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 205, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 185, 10, 0, 0, 235, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 185, 0, 0, 0, 0, 175, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 85, 0, 0, 55, 10, 0, 175, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 185, 0, 0, 0, 205, 195, 10, 0, 175, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 125, 0, 0, 115, 255, 255, 225, 10, 0, 175, 255, 255, 255, 255, 255, 255, 255, 255, 255, 125, 0, 0, 0, 75, 65, 20, 20, 10, 0, 0, 20, 55, 195, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 205, 255, 255, 255, 255, 255, 145, 85, 85, 85, 85, 85, 85, 25, 0, 0, 0, 25, 75, 105, 205, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 10, 0, 185, 235, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 215, 155, 205, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 135, 0, 0, 10, 10, 10, 205, 255, 255, 255, 75, 0, 0, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 60, 255, 255, 255, 195, 0, 0, 65, 255, 255, 255, 255, 255, 255, 10, 20, 65, 185, 0, 10, 85, 255, 255, 255, 255, 75, 0, 65, 255, 255, 255, 255, 255, 255, 10, 30, 255, 255, 75, 10, 145, 255, 255, 255, 255, 75, 0, 5, 255, 255, 255, 255, 255, 255, 10, 30, 255, 255, 75, 0, 10, 255, 255, 255, 235, 0, 0, 65, 255, 255, 255, 255, 255, 255, 10, 40, 255, 255, 195, 0, 10, 85, 195, 195, 0, 0, 0, 115, 255, 255, 255, 255, 255, 255, 10, 70, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 155, 255, 255, 255, 255, 255, 255, 255, 10, 175, 255, 255, 255, 255, 155, 0, 0, 50, 165, 165, 245, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 205, 205, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 185, 45, 0, 0, 0, 0, 10, 55, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 185, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 35, 245, 255, 255, 255, 255, 255, 255, 235, 0, 0, 0, 85, 10, 0, 85, 255, 255, 75, 0, 0, 10, 215, 255, 255, 255, 255, 255, 35, 0, 55, 255, 235, 0, 0, 255, 255, 255, 235, 135, 0, 0, 215, 255, 255, 255, 255, 255, 0, 0, 255, 255, 175, 0, 0, 255, 255, 255, 235, 215, 0, 0, 155, 255, 255, 255, 255, 255, 0, 20, 255, 255, 235, 0, 0, 145, 255, 235, 175, 215, 0, 0, 155, 255, 255, 255, 255, 255, 0, 0, 255, 255, 255, 0, 0, 0, 45, 125, 165, 0, 0, 10, 215, 255, 255, 255, 255, 255, 85, 135, 255, 255, 255, 245, 0, 0, 0, 0, 0, 0, 10, 185, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 235, 75, 15, 0, 35, 125, 185, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 205, 205, 205, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 25, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 225, 25, 15, 215, 205, 255, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 255, 255, 125, 25, 0, 0, 10, 165, 205, 255, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 125, 25, 0, 0, 10, 155, 205, 205, 205, 255, 255, 255, 255, 255, 0, 0, 255, 255, 185, 25, 0, 0, 10, 155, 215, 255, 245, 255, 255, 255, 255, 255, 255, 255, 0, 0, 135, 25, 0, 0, 10, 155, 215, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 35, 155, 215, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 135, 195, 235, 235, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 155, 155, 155, 205, 205, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 205, 205, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 205, 205, 255, 255, 255, 165, 55, 55, 115, 255, 255, 255, 255, 255, 255, 255, 255, 255, 105, 55, 55, 55, 55, 205, 55, 55, 55, 55, 55, 55, 255, 255, 255, 255, 255, 255, 255, 165, 55, 55, 215, 55, 55, 55, 55, 215, 215, 215, 105, 55, 115, 255, 255, 255, 255, 255, 255, 55, 55, 255, 255, 255, 55, 55, 115, 255, 255, 255, 255, 55, 55, 205, 255, 255, 255, 255, 255, 55, 115, 255, 255, 255, 165, 55, 115, 255, 255, 255, 255, 105, 55, 205, 255, 255, 255, 255, 255, 55, 55, 255, 255, 255, 255, 55, 55, 255, 255, 255, 255, 55, 55, 205, 255, 255, 255, 255, 255, 165, 55, 175, 205, 205, 55, 55, 55, 115, 255, 255, 165, 55, 115, 205, 255, 255, 255, 255, 255, 215, 55, 55, 55, 55, 55, 215, 55, 55, 55, 55, 55, 55, 215, 255, 255, 255, 255, 255, 255, 255, 215, 165, 115, 215, 215, 255, 215, 165, 55, 55, 115, 215, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 205, 205, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 135, 0, 0, 0, 0, 0, 195, 255, 255, 255, 255, 225, 255, 255, 255, 255, 255, 255, 255, 135, 0, 0, 0, 0, 0, 0, 0, 135, 255, 255, 95, 65, 5, 215, 255, 255, 255, 255, 255, 0, 0, 145, 255, 255, 255, 30, 0, 25, 255, 255, 95, 105, 0, 155, 255, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 195, 10, 0, 235, 245, 35, 45, 0, 155, 255, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 145, 45, 0, 235, 85, 95, 45, 0, 155, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 45, 0, 0, 20, 20, 5, 0, 75, 205, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 45, 165, 255, 255, 255, 255, 255, 255, 255, 175, 55, 0, 0, 0, 0, 0, 0, 0, 55, 115, 225, 255, 255, 255, 255, 255, 255, 255, 255, 255, 205, 105, 105, 105, 105, 105, 105, 165, 205, 205, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, };
uint32_t minScore = 30000;

OCR::OCR() {
	for (int i = 0; i < characters; ++i) {
		referenceImages[i] = ReferenceImage((uint32_t)data+i*imageDataSize*imageDataSize);
	}
}

OCR::~OCR() {
	// TODO Auto-generated destructor stub
}

void OCR::draw(uint16_t x, uint16_t y) {
	for (uint8_t i = 0; i < characters; ++i) {
		referenceImages[i].draw(x + i * 22,y);
	}
}

ReferenceImage* OCR::getReferenceImage(uint8_t i) {
	return &referenceImages[i];
}

uint8_t OCR::recognizeNumber(Image *image) {
	uint32_t scores[characters] = {0};
	for (int i = 0; i < characters; ++i) {
		scores[i] = getReferenceImage(i)->generateScore(image);
	}

	uint8_t highestScore = 0;
	for (int i = 1; i < characters; ++i) {
		if(scores[i] > scores[highestScore]) highestScore = i;
	}
	printf("score: %d\n",scores[highestScore]);
	if(scores[highestScore] > minScore) {
		return highestScore+1;
	} else {
		return 0;
	}

}

void OCR::save() {
	//IOWR_32DIRECT(0x0BFF0000,0,flashBase);
	printf("=================\n");
	printf("{");
	for (uint8_t i = 0; i < characters; ++i) {
		getReferenceImage(i)->save();
	}
	printf("}\n");
	printf("=================\n");
	printf("reference data saved.\n");
}