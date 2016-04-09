//
//  PlayTetris.c
//  TehtrisTsehirt
//
//  Created by Kyler Stole on 3/4/16.
//  Copyright © 2016 Kyler Stole. All rights reserved.
//

#include <time.h> // time
#include <unistd.h> // sleep
#include <ncurses.h> // window / key management
#include <string.h> // strcmp
#include "TetrisSRS_core.h"

#define TICKRATE 1000
#define WORLD_WIDTH 20
#define WORLD_HEIGHT 12

/**
 *  Prints a representation of the array
 */
void printArrayNCURSES(WINDOW *win) {
	wclear(win);
	for (int j = 2; j < H; j++) {
		waddch(win, ' ');
		waddch(win, ' ');
		for (int i = 0; i < W; i++) {
			wattron(win, COLOR_PAIR(board[i][j]+1));
			wprintw(win, " %d", board[i][j]);
			wattroff(win, COLOR_PAIR(board[i][j]+1));
		}
		waddch(win, '\n');
	}
	waddch(win, '\n');
	
	box(win, 0, 0);
	
	wrefresh(win);
}

int main(int argc, char *argv[]) {
	
	for (int argi = 1; argi < argc; argi++)
		if (strcmp(argv[argi], "--debug-in-terminal") == 0) {
			printf("Debugging in terminal enabled\n");
			getchar(); // Without this call debugging will be skipped
			break;
		}
	
	WINDOW *tetris_world;
	int offsetx, offsety, ch;
	
	initscr(); // set up the parent window, stdscr
	cbreak(); // disable line buffering (feeds input to program without newline)
	noecho(); // subvert the terminal from printing back the users key presses
	// sets an input delay, in milliseconds, for stdscr, which is applied during input with getch() and sibling functions.
	// If the user doesn’t input anything within this given time period, getch() returns with value ERR
	timeout(TICKRATE);
	keypad(stdscr, TRUE); // enables special input characters for a given window (e.g. arrow keys)
	
	if (!has_colors()) {
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color(); // start color
	/* Blocks */
	init_pair(1, COLOR_BLACK, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_YELLOW);
	init_pair(3, COLOR_WHITE, COLOR_RED);
	init_pair(4, COLOR_WHITE, COLOR_CYAN);
	init_pair(5, COLOR_BLACK, COLOR_WHITE);
	init_pair(6, COLOR_WHITE, COLOR_GREEN);
	init_pair(7, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(8, COLOR_WHITE, COLOR_BLUE);
	/* Colored letters */
	//	init_pair(1, COLOR_BLACK, COLOR_BLACK);
	//	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	//	init_pair(3, COLOR_RED, COLOR_BLACK);
	//	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	//	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	//	init_pair(6, COLOR_GREEN, COLOR_BLACK);
	//	init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
	//	init_pair(8, COLOR_BLUE, COLOR_BLACK);
	
	
	printw("Tehtris Tsehirt v2.0  -  Press q to quit...");
	
	offsetx = (COLS - WORLD_WIDTH) / 2;
	offsety = (LINES - WORLD_HEIGHT) / 2;
	
	mvprintw(offsety-1, offsetx+7, "Tetris");
 
	tetris_world = newwin(WORLD_HEIGHT, WORLD_WIDTH,
												offsety, offsetx);
	
	mvprintw(offsety + 1, offsetx + WORLD_WIDTH + 3, "Score:");
	mvprintw(offsety + 4, offsetx + WORLD_WIDTH + 3, "Next piece:");
	
	refresh();
	
	/* Initialize Tetris game with random seed */
	initTetris((uint8_t)time(NULL));
	
while (!isGameOver()) {
	// Generate new piece
	generateNewPiece();
	
	mvprintw(offsety + 2, offsetx + WORLD_WIDTH + 3, "%d", score);
	//mvprintw(offsety + 1, offsetx + WORLD_WIDTH + 3, "Score:");
	//mvprintw(offsety + 4, offsetx + WORLD_WIDTH + 3, "Next piece:");
	
	do {
		while ((ch = getch()) != 'q') {
			printArrayNCURSES(tetris_world);
			if (ch != ERR) {
				switch (ch) {
					case KEY_LEFT:
						moveLeft();
						break;
					case KEY_RIGHT:
						moveRight();
						break;
					case KEY_UP:
						rotateCW();
						break;
					case KEY_DOWN:
						drop();
						break;
					default: break;
				} // /switch(ch)
			} else break; // /ch != ERR
			clearFullRows();
		} // /getch()
		if (ch == 'q') break;
	} while (drop());
	if (ch == 'q') break;
	
} // /!isGameOver()
	
	// Clean up ncurses windows
	delwin(tetris_world);
	endwin();
	
	return 0;
}
