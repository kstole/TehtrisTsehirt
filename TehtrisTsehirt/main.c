//
//  main.c
//  TehtrisTsehirt
//
//  Created by Kyler Stole on 4/10/15.
//  Copyright (c) 2015 Kyler Stole. All rights reserved.
//

#include <time.h> //time
#include <unistd.h> //sleep
#include <stdio.h> //printf
#include <stdlib.h> //malloc
#include <inttypes.h> //Zach's computer
typedef uint8_t u_int8_t;
#define W 8
#define H 10

/* Global Vars */
u_int8_t board[W][H];
u_int8_t piece;
/* 1111 222 333 44  55 666 77
 *        2 3   44 55   6   77 */
u_int8_t o; // orientation
/* 0 | upright
 * 1 | right
 * 2 | down
 * 3 | left
 */
u_int8_t x;
u_int8_t y;


//typedef struct Tetris {
//    u_int8_t** board;
//    u_int8_t height;
//    u_int8_t width;
//    u_int8_t piece;
//    /* 1111 222 333 44  55 666 77
//     *        2 3   44 55   6   77 */
//    u_int8_t o; // orientation
//    /* 0 | upright
//     * 1 | right
//     * 2 | down
//     * 3 | left
//     */
//    u_int8_t x;
//    u_int8_t y;
//    
//} Tetris;

/*
 * parameters: a pointer to a game of tetris
 * fills array with 0s
 */

void fillArray() {
    for (u_int8_t i = 0; i < H; i++) {
        for (u_int8_t j = 0; j < W; j++) {
            board[i][j] = 0;
        }
    }
}

/*
 * parameters: a pointer to a game of tetris
 * return: nothing
 * prints array as a matrix
 */

void printArray() {
    for (u_int8_t i = 0; i < H; i++) {
        for (u_int8_t j = 0; j < W; j++) {
            printf("%d ",board[i][j]);
        }
        printf("\n");
    }
}

/*
 * parameter: a pointer to a game of tetris
 * return: 1 if you lost, 0 if you haven't lost yet
 * checks top row for 1s
 */

int checkLose() {
    for (int j = 0; j < W; j++) {
        if (board[0][j] != 0) {
            return 1;
        }
    }
    return 0;
}

int genPiece() {
    return rand()%7 + 1;
}

/*
 * parameters: a pointer to a game and a button input
 * output: 1 if you shouldnt refresh the page
 * 0 if you should
 */

int moov(u_int8_t btn) {
    u_int8_t lost = checkLose();
    
    if (piece == 0) piece = genPiece();
    
    
    return 0;
}

int main() {
    srand((unsigned int)time(NULL));
    fillArray();
    while(checkLose() != 1) {
        printArray();
        sleep(1);
        board[2][2] = 4;
        printArray();
        sleep(1);
    }
    return 0;
}
