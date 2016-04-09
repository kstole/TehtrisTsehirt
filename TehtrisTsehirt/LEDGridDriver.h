//
//  LEDGridDriver.h
//  TehtrisTsehirt
//
//  Created by Kyler Stole on 2/26/16.
//  Copyright © 2016 Kyler Stole. All rights reserved.
//

#ifndef LEDGridDriver_h
#define LEDGridDriver_h

#ifndef __llvm__
#include <avr/io.h> // PORT_, DDR_, CLKPR
#include <util/delay.h> // _delay_ms
#include <inttypes.h> // uint8_t
#else
#include <stdlib.h> // uint8_t
char PORTB, PORTC, PORTD, PORTF, PINF, DDRB, DDRC, DDRD, DDRF, CLKPR;
#endif

/* Options to configure the CPU Clock Prescale */
#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz		0x00
#define CPU_8MHz		0x01
#define CPU_4MHz		0x02
#define CPU_2MHz		0x03
#define CPU_1MHz		0x04
#define CPU_500kHz	0x05
#define CPU_250kHz	0x06
#define CPU_125kHz	0x07
#define CPU_62kHz		0x08

#define H 10
#define W 8

enum color {
	red = 0,
	green = 1,
	blue = 2
};

extern uint8_t array[H][W];

/* Hardware Initialization */
void initLEDGrid(void);

/* Loops all LEDs in 3(0.5)*HI = 15 ms */
void flashLEDs(void);

#endif /* LEDGridDriver_h */
