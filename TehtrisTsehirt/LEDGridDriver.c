//
//  LEDGridDriver.c
//  TehtrisTsehirt
//
//  Created by Kyler Stole and Zachary Stark on 1/24/16.
//  Copyright (c) 2015 Kyler Stole and Zachary Stark. All rights reserved.
//

#include "LEDGridDriver.h"

#ifdef __llvm__
void _delay_ms(unsigned int time) {}
#endif

///////////////////////////////////////////////////
// Global Variables
//

/**
 *  RGB values of the available colors for the LED grid
 */
// 0b[r][g][b]
uint8_t colors[8] = {
	0b000,	// [ ][ ][ ] off
	0b110,	// [r][g][ ] yellow
	0b100,	// [r][ ][ ] red
	0b011,	// [ ][g][b] cyan
	0b111,	// [r][g][b] white
	0b010,	// [ ][g][ ] green
	0b101,	// [r][ ][b] magenta
	0b001		// [ ][ ][b] blue
};

uint8_t rowSelect[H] = {
	0b00000001,
	0b00000010,
	0b00000100,
	0b00001000,
	0b00010000,
	0b00100000,
	0b01000000,
	0b10000000,
	0b00000000,	// managed by Port C
	0b00000000	// managed by Port C
};

/**
 *  An array representing the LED array
 */
uint8_t array[H][W] = {
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0}
};

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
	DDRF = 0b11100000;
	
	// Ports
	PORTB = 0x00;
	PORTD = 0x00;
	PORTC = 0x00;
	PORTF = 0b00010011;
}

//
// Finished: Hardware Initialization
///////////////////////////////////////////////////

///////////////////////////////////////////////////
// LED Position & Color Selectors
//

/**
 *  Selects which row to enable
 */
void selectRow(uint8_t row) {
	PORTD = rowSelect[row];
	
	// Correction for rows 9 and 10
	switch (row) {
		case 8:
			PORTC |= 0b01000000;
			break;
		case 9:
			PORTC &= 0b00111111;
			PORTC |= 0b10000000;
		default:
			PORTC &= 0b00111111;
			break;
	}
}

/**
 *  Selects a color to display
 */
void displayColor(uint8_t color) {
	uint8_t f = PORTF & 0b00011111;
	
	f |= 1 << (5 + color);
	
	PORTF = f;
	
	// PORTF = 1 << (5 + color);
}

/**
 *  Selects which columns to enable
 */
void selectColumns(uint8_t color, uint8_t row) {
	uint8_t colorByte = 0x00;

	// Loop through columns
	for (uint8_t col = 7; col < W; col--) {
		if ((colors[array[row][col]] >> (2-color)) & 1) colorByte |= 1;
		if (col != W-1) colorByte <<= 1;
	}
	
	PORTB = colorByte;
}

//
// Finished: LED Position & Color Selectors
///////////////////////////////////////////////////

void flashLEDs() {
	// Loop through rows
	for (uint8_t row = 0; row < H; row++) {
		// Set row
		selectRow(row);
		
		// Loop through all colors
		for (uint8_t color = red; color < blue; color++) {
			// Select color to display
			displayColor(color);
			
			// Select columns that display the color
			selectColumns(color, row);
			
			// Display each color for 0.5 ms
			_delay_ms(0.5);
		}
	}
	// Clear all LEDs
	PORTB = 0x00;
}
