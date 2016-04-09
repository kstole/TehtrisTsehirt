//
//  PieceOfCakeSnake.c
//  PieceOfCakeSnake
//
//	Based on tutorial at:
//	http://rhardih.io/2010/04/using-ncurses-in-c-for-text-user-interfaces-featuring-xcode/
//
//  Created by Kyler Stole on 3/9/16.
//  Copyright © 2016 Kyler Stole. All rights reserved.
//

#include <ncurses.h>
#include <string.h>

#define TICKRATE 100

#define WORLD_WIDTH 50
#define WORLD_HEIGHT 20

#define SNAKEY_LENGTH 40

enum direction { UP, DOWN, RIGHT, LEFT };

typedef struct spart {
	int x;
	int y;
} snakeypart;

int move_snakey(WINDOW *win, int direction, snakeypart snakey[]);

int main(int argc, char *argv[]) {
	
	for (int argi = 1; argi < argc; argi++)
		if (strcmp(argv[argi], "--debug-in-terminal") == 0) {
			printf("Debugging in terminal enabled\n");
			getchar(); // Without this call debugging will be skipped
			break;
		}
 
	WINDOW *snakeys_world;
	int offsetx, offsety, i, ch;
 
	initscr(); // sets up the parent window, stdscr
	noecho(); // subverts the terminal from printing back the users key presses
	cbreak(); // disable line buffering (feeds input to program without newline)
	// sets an input delay, in milliseconds, for stdscr, which is applied during input with getch() and sibling functions.
	// If the user doesn’t input anything within this given time period, getch() returns with value ERR
	timeout(TICKRATE);
	keypad(stdscr, TRUE); // enables or disables special input characters for a given window
 
	printw("PieceOfCakeSnake v. 1.0  -  Press x to quit...");
 
	refresh();
 
	offsetx = (COLS - WORLD_WIDTH) / 2;
	offsety = (LINES - WORLD_HEIGHT) / 2;
 
	snakeys_world = newwin(WORLD_HEIGHT,
												 WORLD_WIDTH,
												 offsety,
												 offsetx);
 
	snakeypart snakey[SNAKEY_LENGTH];
 
	int sbegx = (WORLD_WIDTH - SNAKEY_LENGTH) / 2;
	int sbegy = (WORLD_HEIGHT - 1) / 2;
 
	for (i = 0; i < SNAKEY_LENGTH; i++) {
		snakey[i].x = sbegx + i;
		snakey[i].y = sbegy;
	}
 
	int cur_dir = RIGHT;
 
	while ((ch = getch()) != 'x') {
		move_snakey(snakeys_world, cur_dir, snakey);
		if(ch != ERR) {
			switch(ch) {
				case KEY_UP:
					cur_dir = UP;
					break;
				case KEY_DOWN:
					cur_dir = DOWN;
					break;
				case KEY_RIGHT:
					cur_dir = RIGHT;
					break;
				case KEY_LEFT:
					cur_dir = LEFT;
					break;
				default:
					break;
			}
			
		}
	}
 
	delwin(snakeys_world);
 
	endwin();
 
	return 0;
 
}

int move_snakey(WINDOW *win, int direction, snakeypart snakey[]) {
 
	wclear(win);
 
	for (int i = 0; i < SNAKEY_LENGTH - 1; i++) {
		snakey[i] = snakey[i + 1];
		mvwaddch(win, snakey[i].y, snakey[i].x, 'o');
	}
 
	int x = snakey[SNAKEY_LENGTH - 1].x;
	int y = snakey[SNAKEY_LENGTH - 1].y;
	switch (direction) {
		case UP:
			y - 1 == 0 ? y = WORLD_HEIGHT - 2 : y--;
			break;
		case DOWN:
			y + 1 == WORLD_HEIGHT - 1 ? y = 1 : y++;
			break;
		case RIGHT:
			x + 1 == WORLD_WIDTH - 1 ? x = 1 : x++;
			break;
		case LEFT:
			x - 1 == 0 ? x = WORLD_WIDTH - 2 : x--;
			break;
		default:
			break;
	}
 
	snakey[SNAKEY_LENGTH - 1].x = x;
	snakey[SNAKEY_LENGTH - 1].y = y;
 
	mvwaddch(win, y, x, '#');
 
	box(win, 0 , 0);
 
	wrefresh(win);
 
	return 0;
}
