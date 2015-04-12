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
u_int8_t loc[4][2];
u_int8_t piece;
// 1111 22  33 44  5     6  7
//      22 33   44 555 666 777
u_int8_t o; // orientation
/* 0 | up
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

void locatePiece() {
    switch (piece) {
        case 1:
            if (o == 0) {
                loc[0][0] = x;
                loc[0][1] = y+1;
                loc[1][0] = x+1;
                loc[1][1] = y+1;
                loc[2][0] = x+2;
                loc[2][1] = y+1;
                loc[3][0] = x+3;
                loc[3][1] = y+1;
            } else if (o == 1) {
                loc[0][0] = x+3;
                loc[0][1] = y;
                loc[1][0] = x+3;
                loc[1][1] = y+1;
                loc[2][0] = x+3;
                loc[2][1] = y+2;
                loc[3][0] = x+3;
                loc[3][1] = y+3;
            } else if (o == 2) {
                loc[0][0] = x;
                loc[0][1] = y+2;
                loc[1][0] = x+1;
                loc[1][1] = y+2;
                loc[2][0] = x+2;
                loc[2][1] = y+2;
                loc[3][0] = x+3;
                loc[3][1] = y+2;
            } else {
                loc[0][0] = x+2;
                loc[0][1] = y;
                loc[1][0] = x+2;
                loc[1][1] = y+1;
                loc[2][0] = x+2;
                loc[2][1] = y+2;
                loc[3][0] = x+2;
                loc[3][1] = y+3;
            }
        case 2:
            loc[0][0] = x;
            loc[0][1] = y;
            loc[1][0] = x+1;
            loc[1][1] = y;
            loc[2][0] = x;
            loc[2][1] = y+1;
            loc[3][0] = x+1;
            loc[3][1] = y+1;
        case 3:
            loc[0][0] = x+1;
            loc[0][1] = y+1;
            loc[1][0] = x;
            loc[1][1] = y+1;
            loc[2][0] = x+1;
            loc[2][1] = y;
            if (o == 1 || o == 2) {
                loc[1][0] = x+2;
            }
            if (o == 2 || o == 3) {
                loc[2][1] = y+2;
            }
            if (o == 0) {
                loc[3][0] = x+2;
                loc[3][1] = y;
            } else if (o == 1) {
                loc[3][0] = x+2;
                loc[3][1] = y+2;
            } else if (o == 2) {
                loc[3][0] = x;
                loc[3][1] = y+2;
            } else {
                loc[3][0] = x;
                loc[3][1] = y;
            }
            break;
        case 4:
            loc[0][0] = x+1;
            loc[0][1] = y+1;
            if (o == 0) {
                loc[1][0] = x;
                loc[1][1] = y+1;
                loc[2][0] = x+1;
                loc[2][1] = y;
                loc[3][0] = x+2;
                loc[3][1] = y;
            } else if (o == 1) {
                loc[1][0] = x+1;
                loc[1][1] = y;
                loc[2][0] = x+2;
                loc[2][1] = y+1;
                loc[3][0] = x+2;
                loc[3][1] = y+2;
            } else if (o == 2) {
                loc[1][0] = x+2;
                loc[1][1] = y+1;
                loc[2][0] = x+1;
                loc[2][1] = y+2;
                loc[3][0] = x;
                loc[3][1] = y+2;
            } else {
                loc[1][0] = x+1;
                loc[1][1] = y+2;
                loc[2][0] = x;
                loc[2][1] = y+1;
                loc[3][0] = x+1;
                loc[3][1] = y+2;
            }
            break;
        case 5:
            loc[0][0] = x+1;
            loc[0][1] = y+1;
            if (o == 0 || o == 2) {
                loc[1][0] = x;
                loc[1][1] = y+1;
                loc[2][0] = x+2;
                loc[2][1] = y+1;
            } else {
                loc[1][0] = x+1;
                loc[1][1] = y;
                loc[2][0] = x+1;
                loc[2][1] = y+2;
            }
            if (o == 0) {
                loc[3][0] = x;
                loc[3][1] = y;
            }
            else if (o == 1) {
                loc[3][0] = x+2;
                loc[3][1] = y;
                }
            else if (o == 2) {
                loc[3][0] = x+2;
                loc[3][1] = y+2;
            } else {
                loc[3][0] = x;
                loc[3][1] = y+2;
            }
            break;
        case 6:
            loc[0][0] = x+1;
            loc[0][1] = y+1;
            if (o == 0 || o == 2) {
                loc[1][0] = x;
                loc[1][1] = y+1;
                loc[2][0] = x+2;
                loc[2][1] = y+1;
            } else {
                loc[1][0] = x+1;
                loc[1][1] = y;
                loc[2][0] = x+1;
                loc[2][1] = y+2;
            }
            if (o == 0) {
                loc[3][0] = x+2;
                loc[3][1] = y;
            }
            else if (o == 1) {
                loc[3][0] = x+2;
                loc[3][1] = y+2;
            }
            else if (o == 2) {
                loc[3][0] = x;
                loc[3][1] = y+2;
            } else {
                loc[3][0] = x;
                loc[3][1] = y;
            }
            break;
        case 7:
            loc[0][0] = x+1;
            loc[0][1] = y+1;
            loc[1][0] = x;
            loc[1][1] = y+1;
            loc[2][0] = x+2;
            loc[2][1] = y+1;
            if (o == 2) {
                loc[3][0] = x+1;
                loc[3][1] = y+2;
            } else {
                loc[3][0] = x+1;
                loc[3][1] = y;
                if (o == 1) {
                    loc[1][0] = x+1;
                    loc[1][1] = y+2;
                } else if (o == 3) {
                    loc[2][0] = x+1;
                    loc[2][1] = y+2;
                }
            }
            break;
            
        default:
            break;
    }
}

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
