//
//  main.c
//  TehtrisTsehirt
//
//  Created by Kyler Stole on 4/10/15.
//  Copyright (c) 2015 Kyler Stole. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Tetris {
    u_int8_t** board;
    u_int8_t height;
    u_int8_t width;
} Tetris;

void fillArray(Tetris* game) {
    for (u_int8_t i = 0; i < game->height; i++) {
        for (u_int8_t j = 0; j < game->width; j++) {
            game->board[i][j] = 0;
        }
    }
}

void pru_int8_tArray(Tetris* game) {
    for (u_int8_t i = 0; i < game->height; i++) {
        for (u_int8_t j = 0; j < game->width; j++) {
            printf("%d ",game->board[i][j]);
        }
        printf("\n");
    }
}

int checkLose(Tetris* game) {
    for (int j = 0; j < game->width; j++) {
        if (game->board[0][j] != 0) {
            return 1;
        }
    }
    return 0;
}

int moov(u_int8_t btn, Tetris* game) {
    u_int8_t lost = checkLose(game);
    
    return 0;
}

int main() {
    
    Tetris* game = malloc(sizeof(Tetris));
    game->height = 7;
    game->width = 5;
    game->board = malloc(sizeof(u_int8_t*) * game->height);
    for (u_int8_t i=0; i < game->height; i++) {
        game->board[i] = malloc(sizeof(u_int8_t) * game->width);
    }
    
    fillArray(game);
    pru_int8_tArray(game);
    
    
    return 0;
}