

#ifndef STANDARD_FUNCTIONS_H_
#define STANDARD_FUNCTIONS_H_

#define timerBase 0x10002000

#include <io.h>
#include "typedefs.h"

#include <altera_up_avalon_video_dma_controller.h>
#include <altera_up_avalon_video_pixel_buffer_dma.h>
#include <altera_up_avalon_parallel_port.h>

static alt_up_parallel_port_dev* greenLeds = alt_up_parallel_port_open_dev("/dev/Green_LEDs");
static alt_up_parallel_port_dev* redLeds = alt_up_parallel_port_open_dev("/dev/Red_LEDs");
static alt_up_parallel_port_dev* keys = alt_up_parallel_port_open_dev("/dev/Pushbuttons");
static alt_up_parallel_port_dev* switches = alt_up_parallel_port_open_dev("/dev/Slider_Switches");
static alt_up_parallel_port_dev* expansion = alt_up_parallel_port_open_dev("/dev/Expansion_JP5");
static alt_up_pixel_buffer_dma_dev* pb = alt_up_pixel_buffer_dma_open_dev("/dev/VGA_Subsystem_VGA_Pixel_DMA");
static alt_up_video_dma_dev* dma = alt_up_video_dma_open_dev("/dev/VGA_Subsystem_Char_Buf_Subsystem_Char_Buf_DMA");

/*
 * Waardes relatief converteren naar nieuwe waardes
 * x: De waarde die geconverteerd moet worden
 * in_max:	Maximale waarde die x kan hebben
 * out_max: Maximale waarde van de nieuwe waardes
 *
 * geeft de geconverteerde terug
*/
uint16_t map(uint16_t x, uint16_t in_max, uint16_t out_max);
/*
 * Zorgt ervoor dat waardes niet buiten een bepaald gebied kan komen
 * x: De waarde die begrensd moet worden
 * a: De ondergrens waar x boven moet blijven
 * b: De bovengrens waar x onder moet blijven
 *
 * geeft de begrensde waarde terug
 */
int constrain(int x, int a, int b);
/*
 * Functie om een integer naar een constant character te converteren
 * num: De integer die geconverteerd moet worden
 *
 * geeft karakter van de integer terug
 */
char* itoa(int num);

/*
 * Teken een zwarte\witte pixel op het scherm
 * x: x coordinaat op het scherm (0-320)
 * y: y coordinaat op het scherm (0-240)
 * on: De kleur van de pixel wit: 1 zwart: 0
 */
void drawPixelBW(int x,int y,bool on);
/*
 * Teken een pixel op het scherm met alle kleuren
 * x: x coordinaat op het scherm (0-320)
 * y: y coordinaat op het scherm (0-240)
 * value: kleur waarde (16-bit)
 */
void drawPixelRaw(int x,int y,uint16_t value);
/*
 * Teken een pixel op het scherm met alle kleuren
 * x: x coordinaat op het scherm (0-320)
 * y: y coordinaat op het scherm (0-240)
 * r: rood waarde van de kleur
 * g: groen waarde van de kleur
 * b: blauw waarde van de kleur
 */
void drawPixelRGB(int x, int y, uint8_t r, uint8_t g, uint8_t b);
/*
 * Verwijder alle attributen op het scherm
 */
void clearScreen();
/*
 * Schrijf een teken op het scherm
 * x: x coordinaat op het scherm (0-320)
 * y: y coordinaat op het scherm (0-240)
 * text: Het teken wat op het scherm wordt getoond
 */
void drawString(uint16_t x, uint16_t y, int text);
/*
 * Schrijf een aantal tekens op het scherm
 * x: x coordinaat op het scherm (0-320)
 * y: y coordinaat op het scherm (0-240)
 * text: De zin of de tekens die op het scherm worden getoond
 */
void drawString(uint16_t x, uint16_t y, char* text);
/*
 * Leest de kleur van een pixel uit
 * x: x coordinaat op het scherm (0-320)
 * y: y coordinaat op het scherm (0-240)
 */
uint16_t readPixel(uint16_t x, uint16_t y);

/*
 * Stelt een pin van de gpio in als input of output
 * pin: De pin die ingesteld moet worden (0-31)
 * mode: De modus waarin de pin ingesteld moet worden (input of output)
 */
void pinMode(uint8_t pin, uint8_t mode);
/*
 * Zet een pin hoog of laag
 * pin: De pin die veranderd moet worden
 * on: 1/true is hoog 0/false is laag
 */
void digitalWrite(uint8_t pin, boolean on);
/*
 * Leest de waarde van een pin uit
 * pin: De pin die uitgelezen moet worden
 */
bool digitalRead(uint8_t pin);

bool switchesRead(uint8_t sw);
bool keysRead(uint8_t key);
/*
 * Start de interval timer
 */
void startTimer();
/*
 *
 * Geeft de passeerde tijd terug in milliseconden terug
 */
unsigned long micros();
/*
 * delay aantal microseconden 
 * time: tijd in microseconden
 */
void microDelay(uint16_t time);

#endif /* STANDARD_FUNCTIONS_H_ */
