#include "standard_functions.h"

uint16_t map(uint16_t x, uint16_t in_max, uint16_t out_max) {
	return x * out_max / in_max;
}

int constrain(int x, int a, int b) {
	if (x < a)
		x = a;
	if (x > b)
		x = b;
	return x;
}

char* itoa(int num) {
	static char str[5];
	int i = 0;
	int base = 10;

	if (num == 0) {
		str[i++] = '0';
		str[i] = '\0';
		return str;
	}
	while (num != 0) {
		int rem = num % base;
		str[i++] = rem + '0';
		num = num / base;
	}
	str[i] = '\0';
	return str;
}

void drawPixelBW(int x, int y, bool on) {
	int color;
	if (on) {
		color = 0xFFFFFF;
	} else {
		color = 0;
	}
	alt_up_pixel_buffer_dma_draw(pb, color, x, y);
}

void drawPixelRaw(int x, int y, uint16_t value) {
	alt_up_pixel_buffer_dma_draw(pb, value, x, y);
}

void drawPixelRGB(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
	r = map(r, 255, 31);
	g = map(g, 255, 63);
	b = map(b, 255, 31);
	uint16_t color = 0;
	color |= (r & 0b11111) << 11;
	color |= (g & 0b111111) << 5;
	color |= (b & 0b11111);
	alt_up_pixel_buffer_dma_draw(pb, color, x, y);
}

void clearScreen() {
	alt_up_pixel_buffer_dma_clear_screen(pb, 0);
	alt_up_video_dma_screen_clear(dma, 0);
}

void drawString(uint16_t x, uint16_t y, int text) {
	alt_up_video_dma_draw_string(dma, itoa(text), x, y, 0);
}

void drawString(uint16_t x, uint16_t y, char* text) {
	alt_up_video_dma_draw_string(dma, text, x, y, 0);
}

uint16_t readPixel(uint16_t x, uint16_t y) {
	uint32_t addr = 0;
	addr += ((x & pb->x_coord_mask) << pb->x_coord_offset);
	addr += ((y & pb->y_coord_mask) << pb->y_coord_offset);
	return IORD_16DIRECT(pb->back_buffer_start_address, addr);
}

void pinMode(uint8_t pin, uint8_t mode) {
	if (mode == INPUT) {
		alt_up_parallel_port_set_port_direction(expansion,
				alt_up_parallel_port_read_direction(expansion) & ~(1 << pin));

	} else if (mode == OUTPUT) {
		alt_up_parallel_port_set_port_direction(expansion,
				alt_up_parallel_port_read_direction(expansion) | (1 << pin));
	}
}

void digitalWrite(uint8_t pin, boolean on) {
	if (on) {
		alt_up_parallel_port_write_data(expansion,
				alt_up_parallel_port_read_data(expansion) | (1 << pin));
	} else {
		alt_up_parallel_port_write_data(expansion,
				alt_up_parallel_port_read_data(expansion) & ~(1 << pin));
	}
}

bool digitalRead(uint8_t pin) {
	return alt_up_parallel_port_read_data(expansion) & (1 << pin);
}

bool switchesRead(uint8_t sw){
	return alt_up_parallel_port_read_data(switches) & (1 << sw);
}

bool keysRead(uint8_t key){
	return alt_up_parallel_port_read_data(keys) & (1<< key);
}

void startTimer() {
	IOWR(timerBase, 2, 0xFFFF);
	IOWR(timerBase, 3, 0xFFFF);
	IOWR(timerBase, 1, 0b110);
	int n = IORD(timerBase, 0);
	while (n) {
		n >>= 1;
	}
}

unsigned long micros() {
	IOWR(timerBase, 4, 1);
	return 0xFFFFFFFF - (((IORD(timerBase,5) << 16) | IORD(timerBase, 4)) / 50);
}


