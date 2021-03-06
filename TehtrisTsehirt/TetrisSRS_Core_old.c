//
//  TetrisSRS_Core.c
//  TehtrisTsehirt
//
//  Created by Kyler Stole on 4/10/15.
//  Copyright (c) 2015 Kyler Stole. All rights reserved.
//

#include "TetrisSRS_Core.h"

///////////////////////////////////////////////////
// Global Variables
//

uint8_t board[W][H];
uint8_t loc[4][2];
uint8_t curLoc[4][2] = {{-1,-1},{-1,-1},{-1,-1},{-1,-1}};
uint8_t piece = 0;
// 1111 22  33 44  5     6  7
//      22 33   44 555 666 777
uint8_t orient = 0; // orientation
/* 0 | up
 * 1 | right
 * 2 | down
 * 3 | left
 */
uint8_t indx = (W/2)-2;
uint8_t indy = 0; // CHANGED (-2)
uint8_t offx = 0;
uint8_t offy = 0;

uint8_t score = 0;

uint8_t ranPlace = 0;
uint8_t ranGen[7] = {1,2,3,4,5,6,7};

/* Lettering Vars */
uint8_t wi = 5;
uint8_t hi = 7;
uint8_t letter[5][7];

//
// Finished: Global Variables
///////////////////////////////////////////////////

///////////////////////////////////////////////////
// Tetris Initialization
//

/**
 *  Fills Tetris board with 0s
 */
void zeroBoard(void) {
	for (uint8_t i = 0; i < H; i++) {
		for (uint8_t j = 0; j < W; j++) {
			board[i][j] = 0;
		}
	}
}

/**
 *  Fills letter board with 0s
 */
void zeroLetter(void) {
	for (uint8_t i = 0; i < H; i++) {
		for (uint8_t j = 0; j < W; j++) {
			letter[i][j] = 0;
		}
	}
}

void initTetris(uint8_t seed) {
	srand(seed); // Seed random function
	zeroBoard();
	generateNewPiece();
}

//
// Finished: Tetris Initialization
///////////////////////////////////////////////////

void locatePiece(uint8_t x, uint8_t y, uint8_t o) {
	if (o > 3) o = 0;
	switch (piece) {
		case 1:
			if (o == 0) {
				loc[0][0] = x+0; loc[0][1] = y+1;
				loc[1][0] = x+1; loc[1][1] = y+1;
				loc[2][0] = x+2; loc[2][1] = y+1;
				loc[3][0] = x+3; loc[3][1] = y+1;
			} else if (o == 1) {
				loc[0][0] = x+3; loc[0][1] = y+0;
				loc[1][0] = x+3; loc[1][1] = y+1;
				loc[2][0] = x+3; loc[2][1] = y+2;
				loc[3][0] = x+3; loc[3][1] = y+3;
			} else if (o == 2) {
				loc[0][0] = x+0; loc[0][1] = y+2;
				loc[1][0] = x+1; loc[1][1] = y+2;
				loc[2][0] = x+2; loc[2][1] = y+2;
				loc[3][0] = x+3; loc[3][1] = y+2;
			} else {
				loc[0][0] = x+2; loc[0][1] = y+0;
				loc[1][0] = x+2; loc[1][1] = y+1;
				loc[2][0] = x+2; loc[2][1] = y+2;
				loc[3][0] = x+2; loc[3][1] = y+3;
			}
			break;
		case 2:
			loc[0][0] = x+1; loc[0][1] = y+0;
			loc[1][0] = x+2; loc[1][1] = y+0;
			loc[2][0] = x+1; loc[2][1] = y+1;
			loc[3][0] = x+2; loc[3][1] = y+1;
			break;
		case 3:
			if (o == 0) {
				loc[0][0] = x+0; loc[0][1] = y+1;
				loc[1][0] = x+1; loc[1][1] = y+1;
				loc[2][0] = x+1; loc[2][1] = y+0;
				loc[3][0] = x+2; loc[3][1] = y+0;
			} else if (o == 1) {
				loc[0][0] = x+1; loc[0][1] = y+0;
				loc[1][0] = x+1; loc[1][1] = y+1;
				loc[2][0] = x+2; loc[2][1] = y+1;
				loc[3][0] = x+2; loc[3][1] = y+2;
			} else if (o == 2) {
				loc[0][0] = x+0; loc[0][1] = y+2;
				loc[1][0] = x+1; loc[1][1] = y+2;
				loc[2][0] = x+1; loc[2][1] = y+1;
				loc[3][0] = x+2; loc[3][1] = y+1;
			} else {
				loc[0][0] = x+0; loc[0][1] = y+0;
				loc[1][0] = x+0; loc[1][1] = y+1;
				loc[2][0] = x+1; loc[2][1] = y+1;
				loc[3][0] = x+1; loc[3][1] = y+2;
			}
			break;
		case 4:
			if (o == 0) {
				loc[0][0] = x+0; loc[0][1] = y+0;
				loc[1][0] = x+1; loc[1][1] = y+0;
				loc[2][0] = x+1; loc[2][1] = y+1;
				loc[3][0] = x+2; loc[3][1] = y+1;
			} else if (o == 1) {
				loc[0][0] = x+1; loc[0][1] = y+2;
				loc[1][0] = x+1; loc[1][1] = y+1;
				loc[2][0] = x+2; loc[2][1] = y+1;
				loc[3][0] = x+2; loc[3][1] = y+0;
			} else if (o == 2) {
				loc[0][0] = x+0; loc[0][1] = y+1;
				loc[1][0] = x+1; loc[1][1] = y+1;
				loc[2][0] = x+1; loc[2][1] = y+2;
				loc[3][0] = x+2; loc[3][1] = y+2;
			} else {
				loc[0][0] = x+0; loc[0][1] = y+2;
				loc[1][0] = x+0; loc[1][1] = y+1;
				loc[2][0] = x+1; loc[2][1] = y+1;
				loc[3][0] = x+1; loc[3][1] = y+0;
			}
			break;
		case 5:
			if (o == 0) {
				loc[0][0] = x+0; loc[0][1] = y+0;
				loc[1][0] = x+0; loc[1][1] = y+1;
				loc[2][0] = x+1; loc[2][1] = y+1;
				loc[3][0] = x+2; loc[3][1] = y+1;
			} else if (o == 1) {
				loc[0][0] = x+1; loc[0][1] = y+2;
				loc[1][0] = x+1; loc[1][1] = y+1;
				loc[2][0] = x+1; loc[2][1] = y+0;
				loc[3][0] = x+2; loc[3][1] = y+0;
			} else if (o == 2) {
				loc[0][0] = x+0; loc[0][1] = y+1;
				loc[1][0] = x+1; loc[1][1] = y+1;
				loc[2][0] = x+2; loc[2][1] = y+1;
				loc[3][0] = x+2; loc[3][1] = y+2;
			} else {
				loc[0][0] = x+0; loc[0][1] = y+2;
				loc[1][0] = x+1; loc[1][1] = y+2;
				loc[2][0] = x+1; loc[2][1] = y+1;
				loc[3][0] = x+1; loc[3][1] = y+0;
			}
			break;
		case 6:
			if (o == 0) {
				loc[0][0] = x+0; loc[0][1] = y+1;
				loc[1][0] = x+1; loc[1][1] = y+1;
				loc[2][0] = x+2; loc[2][1] = y+1;
				loc[3][0] = x+2; loc[3][1] = y+0;
			} else if (o == 1) {
				loc[0][0] = x+1; loc[0][1] = y+0;
				loc[1][0] = x+1; loc[1][1] = y+1;
				loc[2][0] = x+1; loc[2][1] = y+2;
				loc[3][0] = x+2; loc[3][1] = y+2;
			} else if (o == 2) {
				loc[0][0] = x+0; loc[0][1] = y+2;
				loc[1][0] = x+0; loc[1][1] = y+1;
				loc[2][0] = x+1; loc[2][1] = y+1;
				loc[3][0] = x+2; loc[3][1] = y+1;
			} else {
				loc[0][0] = x+0; loc[0][1] = y+0;
				loc[1][0] = x+1; loc[1][1] = y+0;
				loc[2][0] = x+1; loc[2][1] = y+1;
				loc[3][0] = x+1; loc[3][1] = y+2;
			}
			break;
		case 7:
			loc[0][0] = x+0; loc[0][1] = y+1;
			loc[1][0] = x+1; loc[1][1] = y+1;
			loc[2][0] = x+2; loc[2][1] = y+1;
			if (o == 2) {
				loc[3][0] = x+1; loc[3][1] = y+2;
			} else {
				loc[3][0] = x+1; loc[3][1] = y;
				if (o == 1) {
					loc[0][0] = x+1; loc[0][1] = y+2;
				} else if (o == 3) {
					loc[2][0] = x+1; loc[2][1] = y+2;
				}
			}
			break;
	}
}

void setOffsets(uint8_t test) {
	if (test == 1) {
		offx = 0; offy = 0;
	} else if (piece != 1) {
		switch (test) {
			case 2:
				if (orient == 0) {offx = -1; offy = 0;}
				else if (orient == 1) {offx = 1; offy = 0;}
				else if (orient == 2) {offx = 1; offy = 0;}
				else if (orient == 3) {offx = -1; offy = 0;}
				break;
			case 3:
				if (orient == 0) {offx = -1; offy = -1;}
				else if (orient == 1) {offx = 1; offy = 1;}
				else if (orient == 2) {offx = 1; offy = -1;}
				else if (orient == 3) {offx = -1; offy = 1;}
			case 4:
				if (orient == 0) {offx = 0; offy = 2;}
				else if (orient == 1) {offx = 0; offy = -2;}
				else if (orient == 2) {offx = 0; offy = 2;}
				else if (orient == 3) {offx = 0; offy = -2;}
			case 5:
				if (orient == 0) {offx = -1; offy = 2;}
				else if (orient == 1) {offx = 1; offy = -2;}
				else if (orient == 2) {offx = 1; offy = 2;}
				else if (orient == 3) {offx = -1; offy = -2;}
				
			default:
				break;
		}
	} else { // the I piece has it's own kick data
		switch (test) {
			case 2:
				if (orient == 0) {offx = -2; offy = 0;}
				else if (orient == 1) {offx = -1; offy = 0;}
				else if (orient == 2) {offx = 2; offy = 0;}
				else if (orient == 3) {offx = 1; offy = 0;}
				break;
			case 3:
				if (orient == 0) {offx = 1; offy = 0;}
				else if (orient == 1) {offx = 2; offy = 0;}
				else if (orient == 2) {offx = -1; offy = 0;}
				else if (orient == 3) {offx = -2; offy = 0;}
			case 4:
				if (orient == 0) {offx = -2; offy = 1;}
				else if (orient == 1) {offx = -1; offy = -2;}
				else if (orient == 2) {offx = 2; offy = -1;}
				else if (orient == 3) {offx = 1; offy = 2;}
			case 5:
				if (orient == 0) {offx = 1; offy = -2;}
				else if (orient == 1) {offx = 2; offy = 1;}
				else if (orient == 2) {offx = -1; offy = 2;}
				else if (orient == 3) {offx = -2; offy = -1;}
				
			default:
				break;
		}
	}
}

/**
 *  @return 1 if game is over; 0 otherwise
 */
uint8_t isGameOver(void) {
	if (indy < 0) return 1;
	return 0;
}

uint8_t genPiece(void) {
	//return 5;
	//return 1 + rand()%7;
	if (ranPlace == 0) {
		ranPlace = 7;
		for (uint8_t i = 0; i < 7 - 1; i++) {
			uint8_t j = i + rand() / (RAND_MAX / (7 - i) + 1);
			uint8_t t = ranGen[j];
			ranGen[j] = ranGen[i];
			ranGen[i] = t;
		}
	}
	ranPlace--;
	return ranGen[ranPlace];
}

void generateNewPiece(void) {
	piece = genPiece();
	for (uint8_t i = 0; i < 4; i++)
		curLoc[i][0] = curLoc[i][1] = -1;
	indx = (W/2)-2;
	indy = 0; //CHANGED (previous value: -2)
}

///////////////////////////////////////////////////
// Piece Movement Commands
//

uint8_t drop(void) {
	locatePiece(indx,indy+1, orient);
	// Clear old placement
	for (uint8_t k=0; k < 4; k++)
		if ((curLoc[k][1] < H)) board[curLoc[k][0]][curLoc[k][1]] = 0;
	
	// Check for collisions
	for (uint8_t k=0; k < 4; k++) {
		if (loc[k][1] >= H || board[loc[k][0]][loc[k][1]] != 0) {
			for (uint8_t k=0; k < 4; k++) board[curLoc[k][0]][curLoc[k][1]] = piece;
			return 0; // Fell off the board or Hit another block
		}
	}
	
	// Move to new placement
	for (uint8_t k=0; k < 4; k++) {
		if (loc[k][1] < H) board[loc[k][0]][loc[k][1]] = piece;
		curLoc[k][0] = loc[k][0];
		curLoc[k][1] = loc[k][1];
	}
	
	indy++;
	
	return 1; // Moved a piece down
}

uint8_t moveLeft(void) {
	locatePiece(indx-1,indy,orient);
	// Clear old placement
	for (uint8_t k=0; k < 4; k++)
		if (curLoc[k][1] < H) board[curLoc[k][0]][curLoc[k][1]] = 0;
	
	// Check for collisions
	for (uint8_t k=0; k < 4; k++) {
		if (loc[k][0] < 0 || board[loc[k][0]][loc[k][1]] != 0) {
			for (uint8_t k=0; k < 4; k++) board[curLoc[k][0]][curLoc[k][1]] = piece;
			return 0; // Fell off the board or Hit another block
		}
	}
	
	// Move to new placement
	for (uint8_t k=0; k < 4; k++) {
		if (loc[k][1] < H) board[loc[k][0]][loc[k][1]] = piece;
		curLoc[k][0] = loc[k][0];
		curLoc[k][1] = loc[k][1];
	}
	
	indx--;
	
	return 1; // Moved a piece left
}

uint8_t moveRight(void) {
	locatePiece(indx+1,indy,orient);
	// Clear old placement
	for (uint8_t k=0; k < 4; k++)
		if (curLoc[k][1] < H) board[curLoc[k][0]][curLoc[k][1]] = 0;
	
	// Check for collisions
	for (uint8_t k=0; k < 4; k++) {
		if (loc[k][0] >= W || board[loc[k][0]][loc[k][1]] != 0) {
			for (uint8_t k=0; k < 4; k++) board[curLoc[k][0]][curLoc[k][1]] = piece;
			return 0; // Fell off the board or Hit another block
		}
	}
	
	// Move to new placement
	for (uint8_t k=0; k < 4; k++) {
		if (loc[k][1] < H) board[loc[k][0]][loc[k][1]] = piece;
		curLoc[k][0] = loc[k][0];
		curLoc[k][1] = loc[k][1];
	}
	
	indx++;
	
	return 1; // Moved a piece right
}

uint8_t rotateCW(void) { // Clear old placement
	for (uint8_t k = 0; k < 4; k++)
		if (curLoc[k][1] < H) board[curLoc[k][0]][curLoc[k][1]] = 0;
	
	uint8_t allClear = 0;
	
	for (uint8_t test = 1; test <= 5; test++) {
		setOffsets(test);
		locatePiece(indx+offx, indy+offy, orient+1);
		
		// Check for collisions
		for (uint8_t k = 0; k < 4; k++)
			if (loc[k][0] < 0 || loc[k][0] >= W || loc[k][1] >= H || board[loc[k][0]][loc[k][1]] != 0)
				continue; // Fell off the board or Hit another block
		
		allClear = 1;
		break; // If block did not collide, then it's a fit!
	}
	
	if (allClear) {
		// Move to new placement
		for (uint8_t k = 0; k < 4; k++) {
			if (loc[k][1] < H) board[loc[k][0]][loc[k][1]] = piece;
			curLoc[k][0] = loc[k][0];
			curLoc[k][1] = loc[k][1];
		}
		
		orient++;
		if (orient == 5) orient = 0;
		
		return 1; // Rotated a piece
	} else {
		for (uint8_t k=0; k < 4; k++) board[curLoc[k][0]][curLoc[k][1]] = piece;
		return 0; // Failed all rotation tests
	}
}

//
// Finished: Piece Movement Commands
///////////////////////////////////////////////////

///////////////////////////////////////////////////
// Manage Full Rows
//

/**
 *  Clears a row and moves everything else down
 */
void clearRow(uint8_t row) {
	for (uint8_t i = 0; i < W; i++) {
		for (uint8_t j = row; j < H; j--) {
			if (j != 0) board[i][j] = board[i][j-1];
			else board[i][j] = 0;
		}
	}
}

/**
 *	Checks a row to see if it should be cleared
 *  @return 1 if row is full; 0 otherwise
 */
uint8_t isRowFilled(uint8_t row) {
	for (uint8_t i = 0; i < W; i++)
		if (board[i][row] == 0) return 0;
	return 1;
}

/**
 *  Loops through all rows and clears any that are full
 */
void clearFullRows(void) {
	uint8_t combo = 0;
	for (uint8_t j = 0; j < H; j++) {
		if (isRowFilled(j)) {
			clearRow(j);
			score += ++combo;
		}
	}
}

//
// Finished: Manage Full Rows
///////////////////////////////////////////////////

///////////////////////////////////////////////////
// Text Scrolling
//

/* Scroll text */
void setLetter(uint8_t c) {
	wi = 5;
	zeroLetter();
	switch (c) {
		case 0:
			for (uint8_t n=1; n < 6; n++) {
				letter[0][n] = 1;
				letter[3][n] = 1;
			}
			letter[1][0] = 1;
			letter[2][0] = 1;
			letter[1][6] = 1;
			letter[2][6] = 1;
			break;
		case 1:
			wi = 2;
			for (uint8_t n=0; n < 7; n++)
				letter[0][n] = 1;
			break;
		case 2:
			for (uint8_t m=0; m < 4; m++)
				letter[m][6] = 1;
			for (uint8_t m=0,n=5; m < 4; m++, n--)
				letter[m][n] = 1;
			letter[3][1] = 1;
			letter[0][1] = 1;
			letter[1][0] = 1;
			letter[2][0] = 1;
			break;
		case 3:
			for (uint8_t n=0; n < 7; n += 3)
				letter[2][n] = 1;
			letter[0][1] = 1;
			letter[0][5] = 1;
			letter[1][0] = 1;
			letter[1][6] = 1;
			letter[3][1] = 1;
			letter[3][2] = 1;
			letter[3][4] = 1;
			letter[3][5] = 1;
			break;
		case 4:
			for (uint8_t n=0; n < 3; n++) {
				letter[0][n] = 1;
				letter[3][n] = 1;
				letter[3][n+3] = 1;
			}
			for (uint8_t m=0; m < 4; m++)
				letter[m][3] = 1;
			break;
		case 5:
			for (uint8_t n=0; n < 4; n++)
				letter[0][n] = 1;
			for (uint8_t n=0; n < 7; n += 3) {
				letter[1][n] = 1;
				letter[2][n] = 1;
			}
			letter[0][5] = 1;
			letter[3][0] = 1;
			letter[3][4] = 1;
			letter[3][5] = 1;
			break;
		case 6:
			for (uint8_t n=0; n < 7; n += 3) {
				letter[1][n] = 1;
				letter[2][n] = 1;
			}
			for (uint8_t n=1; n < 6; n++)
				letter[0][n] = 1;
			letter[3][0] = 1;
			letter[3][4] = 1;
			letter[3][5] = 1;
			break;
		case 7:
			for (uint8_t n=0; n < 7; n++)
				letter[3][n] = 1;
			for (uint8_t m=0; m < 3; m++)
				letter[m][0] = 1;
			break;
		case 8:
			for (uint8_t n=0; n < 7; n += 3) {
				letter[1][n] = 1;
				letter[2][n] = 1;
			}
			for (uint8_t n=1; n < 6; n++) {
				letter[0][n] = 1;
				letter[3][n] = 1;
			}
			letter[0][3] = 0;
			letter[3][3] = 0;
			break;
		case 9:
			for (uint8_t n=1; n < 7; n++)
				letter[3][n] = 1;
			letter[0][1] = 1;
			letter[0][2] = 1;
			letter[1][0] = 1;
			letter[2][0] = 1;
			letter[1][3] = 1;
			letter[2][3] = 1;
			break;
			
		default:
			break;
	}
}

void scrollText(uint8_t k) {
	for (uint8_t i = 0; i < W-1; i++)
		for (uint8_t j = 0; j < H; j++)
			board[i][j] = board[i+1][j];
	
	for (uint8_t j = 0; j < H; j++)
		board[W-1][j+1] = letter[k][j];
}

uint8_t showGameOver(void) {
	while (1) {
		zeroBoard();
		int mult[] = {1, 10, 100};
		int num;
		if (score > 10) num = 3;
		else if (score > 1) num = 2;
		else num = 1;
		for (uint8_t p = 0; p < num; p++) {
			setLetter(score/mult[num-1]);
			score = score - ((score/mult[num-1]) * mult[num-1]);
			for (uint8_t k = 0; k < wi; k++) {
				scrollText(k);
				//sleep(1);
			}
		}
		for (uint8_t p = 0; p < W; p++) {
			setLetter(10);
			scrollText(1);
		}
	}
	
	return 0;
}

//
// Finished: Text Scrolling
///////////////////////////////////////////////////
