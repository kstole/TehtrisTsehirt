/* Name: main.c
 * Author: Ryan Kitchen, Kyler Stole, Zachary Stark
 * Copyright: Copyright (c) 2015 Ryan Kitchen, Kyler Stole, and Zachary Stark. All rights reserved.
 */


#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz       0x00
#define CPU_8MHz        0x01
#define CPU_4MHz        0x02
#define CPU_2MHz        0x03
#define CPU_1MHz        0x04
#define CPU_500kHz      0x05
#define CPU_250kHz      0x06
#define CPU_125kHz      0x07
#define CPU_62kHz       0x08

#define HI 10
#define W 8
#define H 13  // 10

char colors[8]={
	0b00000000,
	0b11000000,
	0b10000000,
	0b01100000,
	0b11100000,
	0b01000000,
	0b10100000,
	0b00100000
};

char rowSelect[HI]={
	0b00000001,
	0b00000010,
	0b00000100,
	0b00001000,
	0b00010000,
	0b00100000,
	0b01000000,
	0b10000000,
	0b00000000,
	0b00000000
};

void delay_ms(unsigned int xms) {
	while (xms) {
		_delay_ms(0.96);
		xms--;
	}
}

char setColor(char r, char g, char b) {
	char f=PORTF & 0b00011111;
	if (r) f|=(1<<5);
	if (g) f|=(1<<6);
	if (b) f|=(1<<7);
	PORTF = f;
}

char setColorBits(char c,char x, char array[][8]) {
	char r=0;
	if (c==1) c=0b00100000;
	else if (c==2) c=0b01000000;
	else if (c==3) c=0b10000000;
	for (char i=7; i<8; i--) {
		if (colors[array[x][i]] & c) r++;
		if (i!=0) r = r<<1;
	}
	return r;
}

char setBits(char x, char array[][8]) {
	char r=0;
	for (char i=7; i<8; i--) {
		if (array[x][i]) r++;
		if (i!=0) r = r<<1;
	}
	return r;
}

char isHeld[3] = {0,0,0};
char getButton(char b) {
	if ((PINF & 1)) isHeld[1]=0;
	else if (b==1 && !isHeld[1]) {
		isHeld[1]=1;
		return 1;
	}
	if ((PINF & 2)) isHeld[2]=0;
	else if (b==2 && !isHeld[2]) {
		isHeld[2]=1;
		return 1;
	}
	if ((PINF & 16)) isHeld[0]=0;
	else if (b==0 && !isHeld[0]) {
		isHeld[0]=1;
		return 1;
	}
	return 0;
}

#include "tetrisrs.c"

void translate(char array[][W]) {
	for (char i=0; i < HI; i++)
		for (char j=0; j < W; j++)
			array[i][j] = board[j][H-1-i];
}

uint8_t manualSeed = 0;
int main(void) {
	CPU_PRESCALE(CPU_16MHz);
    /* insert your hardware initialization here */
    DDRB = 0xFF;
    DDRD = 0xFF;
    DDRF = 0b11100000;
	DDRC |=0b11000000;
	PORTC&=0b00111111;
	//DDRC &=0b00111111;
	//PORTC |=0b11000000;
	PORTF = 0b00010011;
    PORTD = 0x0;
	PORTB = 0x0;
	
	char array[10][8]={
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0}
	};
	
	initTetris();
	
	while (1) {
		manualSeed++;
		if (getButton(0) || getButton(1) || getButton(2) || getButton(3)) {
			srand(manualSeed);
			break;
		}
	}
	
	while (1) {
		if (play()) break;
		translate(array);
		char r;
		char cbits;
		for (char i=0; i<10; i++) {
			PORTD = rowSelect[i];
			if (i == 8) {
				PORTC |= 0b01000000;
			} else if(i==9){
				PORTC &= 0b00111111;
				PORTC |= 0b10000000;
			} else PORTC &=0b00111111;
			for (char c=0; c<3; c++) {
				PORTB=0;
				setColor(c==0,c==1,c==2);
				PORTB=setColorBits(c+1,i,array);
				_delay_ms(0.5);
			}
		}
		PORTB=0;
    }
	while (1) {
		if (showGameOver()) break;
		translate(array);
		char r;
		char cbits;
		for (char i=0; i<10; i++) {
			PORTD = rowSelect[i];
			if (i == 8) {
				PORTC |= 0b01000000;
			}
			else if(i==9){
				PORTC &= 0b00111111;
				PORTC |= 0b10000000;
			}
			else PORTC &=0b00111111;
			for (char c=0; c<3; c++) {
				PORTB=0;
				setColor(c==0,c==1,c==2);
				PORTB=setColorBits(c+1,i,array);
				_delay_ms(0.5);
			}
		}
		PORTB=0;
	}
	
    return 0;   /* never reached */
}
