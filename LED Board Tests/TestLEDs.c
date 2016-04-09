//
//  TestLEDs.c
//  Board Test
//
//  Created by Kyler Stole on 3/4/16.
//  Copyright © 2016 Kyler Stole. All rights reserved.
//

#ifndef __llvm__
#include <avr/io.h> // PORT_, DDR_, CLKPR
#include <util/delay.h> // _delay_ms
#include <inttypes.h> // uint8_t
#else
#include <stdlib.h> // uint8_t
char PORTB, PORTC, PORTD, PORTF, PINF, DDRB, DDRC, DDRD, DDRF, CLKPR;
#endif

/* Options to configure the CPU Clock Prescale */
#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz		0x00

#define H 10
#define W 8

#ifdef __llvm__
void _delay_ms(unsigned int time) {}
#endif

///////////////////////////////////////////////////
// Global Variables
//

enum color {
	red = 0,
	green = 1,
	blue = 2
};

/**
 *  RGB values of the available colors for the LED grid
 */
// 0b[r][g][b]
uint8_t colors[8] = {
	0b000,	// [ ][ ][ ] off
	0b100,	// [r][ ][ ] red
	0b010,	// [ ][g][ ] green
	0b001,	// [ ][ ][b] blue
	0b110,	// [r][g][ ] yellow
	0b011,	// [ ][g][b] cyan
	0b101,	// [r][ ][b] magenta
	0b111 	// [r][g][b] white
};

uint8_t array[W] = {1,2,3,0,4,5,6,7};

//
// Finished: Global Variables
///////////////////////////////////////////////////

///////////////////////////////////////////////////
// Hardware Initialization
//

/**
 * Provides hardware initialization for the LED Grid
 */
void initLEDGrid(void) {
	CPU_PRESCALE(CPU_16MHz);
	
	/**
	 *  Port B				- select columns
	 *  Port D				- select row[0:7]
	 *  Port C[7:6]		- select row[8:9]
	 *  Port F[7:5]		- select color
	 *  Port F[4,1,0]	- buttons
	 */
	
	// Data Direction Registers
	DDRB = 0xFF;
	DDRD = 0xFF;
	DDRC = 0xFF;
	DDRF = 0xFF;
	
	// Ports
	PORTB = 0x00;
	PORTD = 0x00;
	PORTC = 0x00;
	PORTF = 0x00;
}

//
// Finished: Hardware Initialization
///////////////////////////////////////////////////

void displayColor(uint8_t color) {
	PORTF = 1 << (5 + color);
}

void selectRow(uint8_t row) {
	if (row < 8)
		PORTD = 1 << row, PORTC = 0x00;
	else
		PORTD = 0x00, PORTC = 1 << (row-2);
}

void selectColumn(uint8_t col) {
	PORTB = 1 << col;
}

void selectColumns(uint8_t color) {
	uint8_t colorByte = 0x00;
	
	// Loop through columns
	for (uint8_t col = 0; col < W; col++) {
		if ((colors[array[col]] >> (2-color)) & 1) colorByte |= 1;
		if (col != W-1) colorByte <<= 1;
	}
	
	PORTB = colorByte;
}

void turnOn(uint8_t color) {
	// Enable all rows
	PORTD = 0xFF, PORTC = 0b11000000;
	
	// Enable all columns
	PORTB = 0xFF;
	
	// Set color to red
	displayColor(color);
}

void allColors() {
	// Enable all rows
	PORTD = 0xFF;
	
	while (1) {
		// Loop through all colors
		for (uint8_t color = red; color <= blue; color++) {
			// Select color to display
			displayColor(color);
			
			// Select columns that display the color
			selectColumns(color);
			
			// Display each color for 0.5 ms
			_delay_ms(0.5);
		}
		PORTB = 0x00;
		_delay_ms(2);
	}
}

void selectColors(uint8_t color, uint8_t r, uint8_t g, uint8_t b) {
	switch (color) {
		case red:
			if (r) PORTB = 0xFF;//0b10001111;
			else PORTB = 0b00000000;
			break;
		case green:
			if (g) PORTB = 0xFF;//0b01001111;
			else PORTB = 0b00000000;
			break;
		case blue:
			if (b) PORTB = 0xFF;//0b00101111;
			else PORTB = 0b00000000;
			break;
	}
}

#define STALL3 18
void fadeIn(uint8_t c, uint8_t r, uint8_t g, uint8_t b) {
	for (uint8_t countMax = 1; countMax <= 50; countMax++) {
		for (uint8_t repeat = 0; repeat < STALL3; repeat++) {
			for (uint8_t color = red; color <= blue; color++) {
				// Cycle colors
				displayColor(color);
				// Select colors to display
				selectColors(color, r, g, b);
				if (color == c) {
					for (uint8_t count = 0; count < countMax; count++)
						_delay_ms(0.01);
					PORTB = 0x00;
					for (uint8_t count = countMax; count < 50; count++)
						_delay_ms(0.01);
				} else _delay_ms(0.5);
			}
		}
	}
}

void fadeOut(uint8_t c, uint8_t r, uint8_t g, uint8_t b) {
	for (uint8_t countMax = 50; countMax > 0; countMax--) {
		for (uint8_t repeat = 0; repeat < STALL3; repeat++) {
			for (uint8_t color = red; color <= blue; color++) {
				// Cycle colors
				displayColor(color);
				// Select colors to display
				selectColors(color, r, g, b);
				if (color == c) {
					for (uint8_t count = 0; count < countMax; count++)
						_delay_ms(0.01);
					PORTB = 0x00;
					for (uint8_t count = countMax; count < 50; count++)
						_delay_ms(0.01);
				} else _delay_ms(0.5);
			}
		}
	}
}

void fadeColors() {
	// Enable all rows
	PORTD = 0xFF;
	
	// Enable all columns
	PORTB = 0xFF;
	PORTC = 0b11000000;
	
	while (1) {
		fadeIn(green, 1, 1, 0);
		fadeOut(red, 1, 1, 0);
		fadeIn(blue, 0, 1, 1);
		fadeOut(green, 0, 1, 1);
		fadeIn(red, 1, 0, 1);
		fadeOut(blue, 1, 0, 1);
	}
}

void randomColors() {
	uint8_t row;
	uint8_t col;
	
	while (1) {
		// Select row
		row = rand() % 10;
		if (row < 8) {
			PORTD = 1 << row;
			PORTC = 0x00;
		} else {
			PORTC = 1 << (row - 2);
			PORTD = 0x00;
		}
		
		// Select column
		col = rand() % 8;
		
		// Loop through all colors
		for (uint8_t color = red; color <= blue; color++) {
			// Select color to display
			displayColor(color);
			
			// Select color for column
			PORTB = (rand() % 2) << col;
			
			// Display each color for 0.5 ms
			_delay_ms(10);
		}
		
		PORTB = 0x00;
		_delay_ms(10);
	}
}

#define STALL 50
void colorStreaks() {
	while (1) {
		PORTB = 0xFF;
		displayColor(red);
		for (uint8_t row = 0; row < H; row++)
			selectRow(row), _delay_ms(STALL);
		displayColor(green);
		for (uint8_t row = H-1; row < H; row--)
			selectRow(row), _delay_ms(STALL);
		displayColor(blue);
		for (uint8_t row = 0; row < H; row++)
			selectRow(row), _delay_ms(STALL);
		
		PORTD = 0xFF, PORTC = 0b11000000;
		displayColor(red);
		for (uint8_t col = 0; col < W; col++)
			selectColumn(col), _delay_ms(STALL);
		displayColor(green);
		for (uint8_t col = W-1; col < W; col--)
			selectColumn(col), _delay_ms(STALL);
		displayColor(blue);
		for (uint8_t col = 0; col < W; col++)
			selectColumn(col), _delay_ms(STALL);
		
		PORTB = 0xFF;
		displayColor(red);
		for (uint8_t row = H-1; row < H; row--)
			selectRow(row), _delay_ms(STALL);
		displayColor(green);
		for (uint8_t row = 0; row < H; row++)
			selectRow(row), _delay_ms(STALL);
		displayColor(blue);
		for (uint8_t row = H-1; row < H; row--)
			selectRow(row), _delay_ms(STALL);
		
		PORTD = 0xFF, PORTC = 0b11000000;
		displayColor(red);
		for (uint8_t col = W-1; col < W; col--)
			selectColumn(col), _delay_ms(STALL);
		displayColor(green);
		for (uint8_t col = 0; col < W; col++)
			selectColumn(col), _delay_ms(STALL);
		displayColor(blue);
		for (uint8_t col = W-1; col < W; col--)
			selectColumn(col), _delay_ms(STALL);
	}
}

uint8_t advanceXpos(uint8_t* pos, uint8_t* flag) {
	if (*flag == 1) { // forward
		if (*pos == W-1) {
			*flag = 0;
			return 0;
		} else (*pos)++;
	} else { // backward
		if (*pos == 0) {
			*flag = 1;
			return 0;
		} else (*pos)--;
	}
	return 1;
}

void advanceYpos(uint8_t* pos, uint8_t* flag, uint8_t* color) {
	if (*flag == 1) { // forward
		if (*pos == H-1) {
			(*pos)--;
			*flag = 0;
			(*color)++;
		} else (*pos)++;
	} else { // backward
		if (*pos == 0) {
			(*pos)++;
			*flag = 1;
			(*color)++;
		} else (*pos)--;
	}
	if (*color > blue) *color = red;
}

#define STALL2 25
void colorPath() {
	uint8_t posx = 0, posy = 0;
	uint8_t xflag = 1, yflag = 1;
	uint8_t color = red;
	while (1) {
		do {
			selectColumn(posx);
			_delay_ms(STALL2);
		} while (advanceXpos(&posx, &xflag));
		selectRow(posy);
		displayColor(color);
		advanceYpos(&posy, &yflag, &color);
	}
}

void compileAll() {
	uint8_t counter;
	uint8_t posx = 0, posy = 0;
	uint8_t xflag = 1, yflag = 1;
	uint8_t row, col;
	uint8_t color = red;
	while (1) {
		/* Color Path */
		for (row = 0, color = red; row < H; row++, color++) {
			if (color > blue) color = red;
			selectColumn(W-1);
			selectRow(row);
			displayColor(color);
			_delay_ms(100);
		}
		for (col = W-1, row = H-1; col < W; col--, row--, color++) {
			if (row == H-4 || row == 3) row--;
			if (color > blue) color = red;
			selectColumn(col);
			selectRow(row);
			displayColor(color);
			_delay_ms(100);
		}
		for (row = 0, color = red; row < H; row++, color++) {
			if (color > blue) color = red;
			selectColumn(0);
			selectRow(row);
			displayColor(color);
			_delay_ms(100);
		}
		for (col = 0, row = H-1; col < W; col++, row--, color++) {
			if (row == H-4 || row == 3) row--;
			if (color > blue) color = red;
			selectColumn(col);
			selectRow(row);
			displayColor(color);
			_delay_ms(100);
		}
		counter = H*3-2;
		posx = 0, posy = 0;
		xflag = 1, yflag = 1;
		color = red;
		while (counter--) {
			do {
				selectColumn(posx);
				_delay_ms(STALL2);
			} while (advanceXpos(&posx, &xflag));
			selectRow(posy);
			displayColor(color);
			advanceYpos(&posy, &yflag, &color);
		}
		PORTB = 0x00;
		for (col = 0; col < W; col++) {
			PORTB |= 1 << col;
			_delay_ms(50);
		}
		/* Color streaks */
		counter = 1;
		while (counter--) {
			PORTB = 0xFF;
			displayColor(blue);
			for (uint8_t row = H-1; row < H; row--)
				selectRow(row), _delay_ms(STALL);
			displayColor(green);
			for (uint8_t row = 0; row < H; row++)
				selectRow(row), _delay_ms(STALL);
			displayColor(red);
			for (uint8_t row = H-1; row < H; row--)
				selectRow(row), _delay_ms(STALL);
			
			PORTD = 0xFF, PORTC = 0b11000000;
			displayColor(red);
			for (uint8_t col = 0; col < W; col++)
				selectColumn(col), _delay_ms(STALL);
			displayColor(green);
			for (uint8_t col = W-1; col < W; col--)
				selectColumn(col), _delay_ms(STALL);
			displayColor(blue);
			for (uint8_t col = 0; col < W; col++)
				selectColumn(col), _delay_ms(STALL);
		}
		/* Color fading */
		// Display red
		displayColor(red);
		// Enable all rows
		PORTD = 0xFF;
		// Progressively load columns
		PORTB = 0x00;
		for (col = W-1; col < W; col--) {
			PORTB |= 1 << col;
			_delay_ms(50);
		}
		counter = 1;
		while (counter--) {
			// Enable all columns
			PORTB = 0xFF, PORTC = 0b11000000;
			
			fadeIn(green, 1, 1, 0);
			fadeOut(red, 1, 1, 0);
			fadeIn(blue, 0, 1, 1);
			fadeOut(green, 0, 1, 1);
			fadeIn(red, 1, 0, 1);
			fadeOut(blue, 1, 0, 1);
		}
		/* Random colors */
		counter = 80;
		while (counter--) {
			// Select row
			uint8_t row = rand() % 10;
			if (row < 8) {
				PORTD = 1 << row;
				PORTC = 0x00;
			} else {
				PORTC = 1 << (row - 2);
				PORTD = 0x00;
			}
			
			// Select column
			uint8_t col = rand() % 8;
			
			// Loop through all colors
			for (uint8_t color = red; color <= blue; color++) {
				// Select color to display
				displayColor(color);
				
				// Select color for column
				PORTB = (rand() % 2) << col;
				
				// Display each color for 0.5 ms
				_delay_ms(10);
			}
			
			PORTB = 0x00;
			_delay_ms(10);
		}
	}
}

int main() {
	initLEDGrid();
	
	//turnOn(blue);
	//allColors();
	fadeColors();
	//randomColors();
	//colorStreaks();
	//colorPath();
	//compileAll();
}

