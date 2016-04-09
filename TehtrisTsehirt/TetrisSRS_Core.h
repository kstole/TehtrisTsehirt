//
//  TetrisSRS_Core.h
//  TehtrisTsehirt
//
//  Created by Kyler Stole on 2/29/16.
//  Copyright © 2016 Kyler Stole. All rights reserved.
//

#ifndef TetrisSRS_Core_h
#define TetrisSRS_Core_h

#include <stdlib.h> // rand, srand, RAND_MAX, uint8_t (llvm)
#ifndef __llvm__
#include <inttypes.h> // uint8_t (avr)
#endif

// Define uint8_t as char if not otherwise defined
#ifndef __UINT8_TYPE__
#define __UINT8_TYPE__
typedef char uint8_t;
#endif

#define W 8
#define H 13  // 10

// Expose game board
extern uint8_t board[W][H];
extern uint8_t score;

/* Initialize the Tetris game environment */
void initTetris(uint8_t seed);

/* Sets a new piece to drop */
void generateNewPiece(void);

/* Piece Movement Commands */
uint8_t moveLeft(void);
uint8_t moveRight(void);
uint8_t rotateCW(void);
uint8_t drop(void);

/* Returns 1 if game is over; 0 otherwise */
uint8_t isGameOver(void);

/* Removes rows that have filled up */
void clearFullRows(void);

uint8_t showGameOver(void);

#endif /* TetrisSRS_Core_h */
