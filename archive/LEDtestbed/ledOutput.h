//
//  ledOutput.h
//  
//
//  Created by Marcus Hall on 4/11/15.
//
//

#ifndef __ledOutput
#define __ledOutput

void push_to_grid(uint8_t *array);
void ledOutput(uint8_t *array);
long translate(uint8_t colorCode);
void push_to_strip(long color);
void pixel(uint8_t x, uint8_t y, uint8_t color);

#endif