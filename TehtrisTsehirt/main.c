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
//typedef int int;
#define W 8
#define H 10

/* Global Vars */
int board[W][H];
int loc[4][2];
int curLoc[4][2] = {{-1,-1},{-1,-1},{-1,-1},{-1,-1}};
int piece = 0;
// 1111 22  33 44  5     6  7
//      22 33   44 555 666 777
int orient = 0; // orientation
/* 0 | up
 * 1 | right
 * 2 | down
 * 3 | left
 */
int indx = (W/2)-2;
int indy = -2;
int score = 0;
int combo;

/* Lettering Vars */
int wi = 5;
int hi = 7;
int letter[5][7];

void locatePiece(int x, int y, int o) {
    if (o == 5) o = 0;
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

void zeroBoard() {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            board[i][j] = 0;
        }
    }
}

void zeroLetter() {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            letter[i][j] = 0;
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

int gameOver() {
    if (indy < 0) return 1;
//    for (int j = 0; j < W; j++) {
//        if (board[0][j] != 0) {
//            return 1;
//        }
//    }
    return 0;
}

int genPiece() {
    return 1 + rand() / (RAND_MAX / (7 - 1 + 1) + 1);
}

int drop () {
    locatePiece(indx,indy+1, orient);
    // Clear old placement
    for (int k=0; k < 4; k++)
        if (curLoc[k][1] >= 0) board[curLoc[k][0]][curLoc[k][1]] = 0;
    
    // Check for collisions
    for (int k=0; k < 4; k++) {
        if (loc[k][1] >= H) {
            for (int k=0; k < 4; k++) board[curLoc[k][0]][curLoc[k][1]] = piece;
            return 0; // Fell off the board
        } else if (board[loc[k][0]][loc[k][1]] != 0) {
            for (int k=0; k < 4; k++) board[curLoc[k][0]][curLoc[k][1]] = piece;
            return 0; // Hit another block;
        }
    }

    // Move to new placement
    for (int k=0; k < 4; k++) {
        if (loc[k][1] >= 0) board[loc[k][0]][loc[k][1]] = piece;
        curLoc[k][0] = loc[k][0];
        curLoc[k][1] = loc[k][1];
    }
    
    indy++;
    
    return 1; // Moved a piece down
}

int moveLeft () {
    locatePiece(indx-1,indy,orient);
    // Clear old placement
    for (int k=0; k < 4; k++)
        if (curLoc[k][1] >= 0) board[curLoc[k][0]][curLoc[k][1]] = 0;
    
    // Check for collisions
    for (int k=0; k < 4; k++) {
        if (loc[k][0] < 0) {
            for (int k=0; k < 4; k++) board[curLoc[k][0]][curLoc[k][1]] = piece;
            return 0; // Fell off the board
        } else if (board[loc[k][0]][loc[k][1]] != 0) {
            for (int k=0; k < 4; k++) board[curLoc[k][0]][curLoc[k][1]] = piece;
            return 0; // Hit another block;
        }
    }
    
    // Move to new placement
    for (int k=0; k < 4; k++) {
        if (loc[k][1] >= 0) board[loc[k][0]][loc[k][1]] = piece;
        curLoc[k][0] = loc[k][0];
        curLoc[k][1] = loc[k][1];
    }
    
    indx--;
    
    return 1; // Moved a piece left
}

int moveRight () {
    locatePiece(indx+1,indy,orient);
    // Clear old placement
    for (int k=0; k < 4; k++)
        if (curLoc[k][1] >= 0) board[curLoc[k][0]][curLoc[k][1]] = 0;
    
    // Check for collisions
    for (int k=0; k < 4; k++) {
        if (loc[k][0] >= W) {
            for (int k=0; k < 4; k++) board[curLoc[k][0]][curLoc[k][1]] = piece;
            return 0; // Fell off the board
        } else if (board[loc[k][0]][loc[k][1]] != 0) {
            for (int k=0; k < 4; k++) board[curLoc[k][0]][curLoc[k][1]] = piece;
            return 0; // Hit another block;
        }
    }
    
    // Move to new placement
    for (int k=0; k < 4; k++) {
        if (loc[k][1] >= 0) board[loc[k][0]][loc[k][1]] = piece;
        curLoc[k][0] = loc[k][0];
        curLoc[k][1] = loc[k][1];
    }
    
    indx++;
    
    return 1; // Moved a piece right
}

int rotateCW () {
    locatePiece(indx,indy,orient+1);
    // Clear old placement
    for (int k=0; k < 4; k++)
        if (curLoc[k][1] >= 0) board[curLoc[k][0]][curLoc[k][1]] = 0;
    
    // Check for collisions
    for (int k=0; k < 4; k++) {
        if (loc[k][0] < 0 || loc[k][0] >= W || loc[k][1] >= H) {
            for (int k=0; k < 4; k++) board[curLoc[k][0]][curLoc[k][1]] = piece;
            return 0; // Fell off the board
        } else if (board[loc[k][0]][loc[k][1]] != 0) {
            for (int k=0; k < 4; k++) board[curLoc[k][0]][curLoc[k][1]] = piece;
            return 0; // Hit another block;
        }
    }
    
    // Move to new placement
    for (int k=0; k < 4; k++) {
        if (loc[k][1] >= 0) board[loc[k][0]][loc[k][1]] = piece;
        curLoc[k][0] = loc[k][0];
        curLoc[k][1] = loc[k][1];
    }
    
    orient++;
    if (orient == 5) orient = 0;
    
    return 1; // Rotated a piece
}

void clearRow(int row) {
    for (int i=0; i < W; i++) {
        for (int j=row; j >= 0; j--) {
            if (j != 0) board[i][j] = board[i][j-1];
            else board[i][j] = 0;
        }
    }
    score += combo;
}

int checkRow(int row) {
    for (int i=0; i < W; i++) {
        if (board[i][row] == 0) return 0;
    }
    combo++;
    return 1;
}

void checkRows() {
    combo = 0;
    for (int j=0; j < H; j++) {
        if (checkRow(j)) clearRow(j);
    }
}

/* Scroll text */
void setLetter(int c) {
    wi = 5;
    zeroLetter();
    switch (c) {
        case 0:
            for (int n=1; n < 6; n++) {
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
            for (int n=0; n < 7; n++)
                letter[0][n] = 1;
            break;
        case 2:
            for (int m=0; m < 4; m++)
                letter[m][6] = 1;
            for (int m=0,n=5; m < 4; m++, n--)
                letter[m][n] = 1;
            letter[3][1] = 1;
            letter[0][1] = 1;
            letter[1][0] = 1;
            letter[2][0] = 1;
            break;
        case 3:
            for (int n=0; n < 7; n += 3)
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
            for (int n=0; n < 3; n++) {
                letter[0][n] = 1;
                letter[3][n] = 1;
                letter[3][n+3] = 1;
            }
            for (int m=0; m < 4; m++)
                letter[m][3] = 1;
            break;
        case 5:
            for (int n=0; n < 4; n++)
                letter[0][n] = 1;
            for (int n=0; n < 7; n += 3) {
                letter[1][n] = 1;
                letter[2][n] = 1;
            }
            letter[0][5] = 1;
            letter[3][0] = 1;
            letter[3][4] = 1;
            letter[3][5] = 1;
            break;
        case 6:
            for (int n=0; n < 7; n += 3) {
                letter[1][n] = 1;
                letter[2][n] = 1;
            }
            for (int n=1; n < 6; n++)
                letter[0][n] = 1;
            letter[3][0] = 1;
            letter[3][4] = 1;
            letter[3][5] = 1;
            break;
        case 7:
            for (int n=0; n < 7; n++)
                letter[3][n] = 1;
            for (int m=0; m < 3; m++)
                letter[m][0] = 1;
            break;
        case 8:
            for (int n=0; n < 7; n += 3) {
                letter[1][n] = 1;
                letter[2][n] = 1;
            }
            for (int n=1; n < 6; n++) {
                letter[0][n] = 1;
                letter[3][n] = 1;
            }
            letter[0][3] = 0;
            letter[3][3] = 0;
            break;
        case 9:
            for (int n=1; n < 7; n++)
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

void scrollText(int k) {
    for (int i=0; i < W-1; i++) {
        for (int j=0; j < H; j++)
            board[i][j] = board[i+1][j];
    }
    for (int j=0; j < H; j++)
        board[W-1][j+1] = letter[k][j];
}

int showGameOver() {
    while (1) {
        zeroBoard();
        int mult[] = {1,10,100};
        int num;
        if (score > 10) num = 3;
        else if (score > 1) num = 2;
        else num = 1;
        for (int p=0; p < num; p++) {
            setLetter(score/mult[num-1]);
            score = score - ((score/mult[num-1]) * mult[num-1]);
            for (int k=0; k < wi; k++) {
                scrollText(k);
                sleep(1);
            }
        }
        for (int p=0; p < W; p++) {
            setLetter(10);
            scrollText(1);
        }
    }
    
    return 0;
}


void newPiece() {
    piece = genPiece();
    for (int i=0; i < 4; i++) {
        curLoc[i][0] = -1;
        curLoc[i][1] = -1;
    }
    indx = (W/2)-2;
    indy = -2;
}

void initTetris(){
    srand(8); // Seed random function
    zeroBoard();
}

int main() {
    // Seed random function
    srand((unsigned int)time(NULL));
    zeroBoard();
    do {
        piece = genPiece();
        for (int i=0; i < 4; i++) {
            curLoc[i][0] = -1;
            curLoc[i][1] = -1;
        }
        indx = (W/2)-2;
        indy = -2;
        do {
            char c = 'p';
            while (1) {
                c = fgetc(stdin);
                if (c == 'a')
                    moveLeft();
                else if (c == 'd')
                    moveRight();
                else if (c == 'w')
                    rotateCW();
                else if (c == 's')
                    drop();
                else break;
            }
            printArray();
            //sleep(1);
        } while (drop());
        checkRows();
    } while (!gameOver());
    
    return 0;
}

//int main() {
//    initTetris();
//    do {
//        newPiece();
//        do {
//            printArray();
//            char c = 'p';
//            //while ( getchar() != '\n' );
//            while (1) {
//                //c = fgetc(stdin);
//                c = getchar();
//                if (c == 'a')
//                    moveLeft();
//                else if (c == 'd')
//                    moveRight();
//                else if (c == 'w')
//                    rotateCW();
//                else if (c == 's')
//                    drop();
//                else break;
//            }
//            //sleep(1);
//        } while (drop());
//        checkRows();
//    } while (!gameOver());
//    showGameOver();
//    
//    return 0;
//}
