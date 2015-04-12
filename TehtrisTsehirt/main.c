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
//typedef uint8_t int;
#define W 8
#define H 10

/* Global Vars */
int board[W][H];
int loc[4][2];
int curLoc[4][2] = {{-1,-1},{-1,-1},{-1,-1},{-1,-1}};
int piece = 0;
// 1111 22  33 44  5     6  7
//      22 33   44 555 666 777
int o = 0; // orientation
/* 0 | up
 * 1 | right
 * 2 | down
 * 3 | left
 */
int indx = (W/2)-2;
int indy = -2;


//typedef struct Tetris {
//    int** board;
//    int height;
//    int width;
//    int piece;
//    /* 1111 222 333 44  55 666 77
//     *        2 3   44 55   6   77 */
//    int o; // orientation
//    /* 0 | upright
//     * 1 | right
//     * 2 | down
//     * 3 | left
//     */
//    int x;
//    int y;
//
//} Tetris;

void locatePiece(int x, int y) {
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
            break;
        case 2:
            loc[0][0] = x+1;
            loc[0][1] = y+1;
            loc[1][0] = x+2;
            loc[1][1] = y+1;
            loc[2][0] = x+1;
            loc[2][1] = y+2;
            loc[3][0] = x+2;
            loc[3][1] = y+2;
            break;
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
            loc[1][0] = x+2;
            loc[1][1] = y+1;
            loc[2][0] = x+1;
            loc[2][1] = y;
            if (o == 2 || o == 3) {
                loc[1][0] = x;
            }
            if (o == 1 || o == 2) {
                loc[2][1] = y+2;
            }
            if (o == 0) {
                loc[3][0] = x;
                loc[3][1] = y;
            } else if (o == 1) {
                loc[3][0] = x+2;
                loc[3][1] = y;
            } else if (o == 2) {
                loc[3][0] = x+2;
                loc[3][1] = y+2;
            } else {
                loc[3][0] = x;
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
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
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
    for (int j = 0; j < H; j++) {
        for (int i = 0; i < W; i++) {
            printf("%d ",board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
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
    return 1 + rand() / (RAND_MAX / (7 - 1 + 1) + 1);
}

int drop () {
    locatePiece(indx,indy+1);
    // Clear old placement
    for (int k=0; k < 4; k++) {
        if (curLoc[k][1] >= 0) board[curLoc[k][0]][curLoc[k][1]] = 0;
    }
    
    for (int k=0; k < 4; k++) {
        if (loc[k][1] >= H) {
            for (int k=0; k < 4; k++) board[curLoc[k][0]][curLoc[k][1]] = piece;
            return 0; // Fell off the board
        } else if (board[loc[k][0]][loc[k][1]] != 0) {
            for (int k=0; k < 4; k++) board[curLoc[k][0]][curLoc[k][1]] = piece;
            return 0; // Hit another block;
        }
    }

    // Move new placement
    for (int k=0; k < 4; k++) {
        if (loc[k][1] >= 0) board[loc[k][0]][loc[k][1]] = piece;
        curLoc[k][0] = loc[k][0];
        curLoc[k][1] = loc[k][1];
    }
    
    indy++;
    
    return 1; // Moved a piece down
}

void clearRow(int row) {
    for (int i=0; i < W; i++) {
        for (int j=row; j >= 0; j--) {
            if (j != 0) board[i][j] = board[i][j-1];
            else board[i][j] = 0;
        }
    }
}

int checkRow(int row) {
    for (int i=0; i < W; i++) {
        if (board[i][row] == 0) return 0;
    }
    return 1;
}

void checkRows() {
    for (int j=0; j < H; j++) {
        if (checkRow(j)) clearRow(j);
    }
}

/*
 * parameters: a pointer to a game and a button input
 * output: 1 if you shouldnt refresh the page
 * 0 if you should
 */

int moov(int btn) {
    int lost = checkLose();
    
    if (piece == 0) piece = genPiece();
    
    
    return 0;
}

int main() {
    // Seed random function
    srand((unsigned int)time(NULL));
    fillArray();
    do {
        piece = genPiece();
        for (int i=0; i < 4; i++) {
            curLoc[i][0] = -1;
            curLoc[i][1] = -1;
        }
        indx = (W/2)-2;
        indy = -2;
        do {
            printArray();
            sleep(1);
        } while (drop());
        checkRows();
    } while (1);
    
    return 0;
}
