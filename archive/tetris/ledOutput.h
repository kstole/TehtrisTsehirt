//
//  ledOutput.h
//  
//
//  Created by Marcus Hall on 4/11/15.
//
//

#ifdef ledOutput
#define ledOutput

#include <stdio.h>
#include <avr/io.h>

void ledOutput(uint8_t[80]);
long translate(uint8_t);
void push_to_strip(long);
void push_to_grid(long);
void coordiante(uint8_t, uint8_t, long);

#endif