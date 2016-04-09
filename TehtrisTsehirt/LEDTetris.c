//
//  LEDTetris.c
//  TehtrisTsehirt
//
//  Created by Kyler Stole on 3/4/16.
//  Copyright © 2016 Kyler Stole. All rights reserved.
//

#include "TetrisSRS_Core.h" // defines H = 13
#include "LEDGridDriver.h" // defines H = 10

/* Translates the tetris board into the array for the LEDs */
void translateArray() {
	for (uint8_t i = 0; i < H; i++)
		for (uint8_t j = 0; j < W; j++)
			array[i][j] = board[j][H+2-i];
}

///////////////////////////////////////////////////
// User Input
//

/**
 *  Poll for button input
 */
uint8_t isHeld[3] = {0,0,0};
uint8_t getButton(uint8_t but) {
	if (PINF & 1) isHeld[1] = 0;
	else if (but == 1 && !isHeld[1]) {
		isHeld[1] = 1;
		return 1;
	}
	if (PINF & 2) isHeld[2] = 0;
	else if (but == 2 && !isHeld[2]) {
		isHeld[2] = 1;
		return 1;
	}
	if (PINF & 16) isHeld[0] = 0;
	else if (but == 0 && !isHeld[0]) {
		isHeld[0] = 1;
		return 1;
	}
	return 0;
}

//
// Finished: User Input
///////////////////////////////////////////////////

///////////////////////////////////////////////////
// Timing
//

uint8_t lastDrop = 0;
uint8_t isDropTime(void) {
	if (lastDrop > 150) {
		lastDrop = 0;
		return 1;
	}
	lastDrop++;
	return 0;
}

uint8_t lastScroll = 0;
uint8_t isScrollTime(void) {
	if (lastScroll > 50) {
		lastScroll = 0;
		return 1;
	}
	lastScroll++;
	return 0;
}

//
// Finished: Timing
///////////////////////////////////////////////////

uint8_t playTetris(void) {
	if (isDropTime()) {
		if (!drop()) {
			clearFullRows();
			if (isGameOver()) return 1;
			else generateNewPiece();
		}
	} else {
		if (getButton(0)) moveLeft();
		if (getButton(1)) moveRight();
		if (getButton(2)) rotateCW();
		if (getButton(3)) drop();
	}
	return 0;
}

int main(void) {
	/* Hardware initialization for LED grid */
	initLEDGrid();
	
	/* Randomize seed */
	uint8_t manualSeed = 0;
//	while (1) {
//		manualSeed++;
//		if (getButton(0) || getButton(1) || getButton(2) || getButton(3))
//			break;
//	}
	
	/* Initialization for internal Tetris board */
	initTetris(manualSeed);
	
	/* Play Tetris ! */
	while (!playTetris()) {
		// Translate Tetris board into array for use w/ LED grid
		translateArray();
		
		flashLEDs();
	}
	
//	/* Display game results */
//	while (1) {
//		if (showGameOver()) break;
//		
//		// Translate Tetris scoreboard into array for use w/ LED grid
//		translateArray();
//		
//		flashLEDs();
//	}
	
	return 0;   /* never reached */
}
