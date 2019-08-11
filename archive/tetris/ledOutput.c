//
//  ledOutput.c
//  
//
//  Created by Marcus Hall on 4/11/15.
//
//

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "ledOutput.h"
#include "lowLevel.h"

void ledOutput(uint8_t array[80]) {
    for (int i=0; i < 32; i++) {
        push_to_strip(translate(array[i]));
    }
    
    /*
     for the grid portion because we ran out of LED strips
        push_to_grid();
     */
    
    writeCKILow();
    delay_ms(1);
}

//writes one led color to the led strip
void push_to_strip(long color) {
    for (int i=23; i >= 0; i--) {
        writeCKILow();
        
        long mask = 1L << i;
        
        if (color & mask)
            writeSDIHigh();
        else
            writeSDILow();
        
        writeCKIHigh();
    }
}

//translates programing color code into led color output value
long translate(uint8_t colorCode) {
    long output;
    
    //Red
    if (colorCode == 0)
        output=0xFA1100;
    //orange
    else if (colorCode == 1)
        output=0xFCA503;
    //magenta
    else if (colorCode == 2)
        output=0xF900FF;
    //blue
    else if (colorCode == 3)
        output=0x0000FF;
    //lime
    else if (colorCode == 4)
        output=0x80FF01;
    //olive
    else if (colorCode == 5)
        output=0x808001;
    //cyan
    else if (colorCode == 6)
        output=0x3EFEFF;
    
    return output;
}

//writes data to LED grid
void push_to_grid(uint8_t array[80]) {
    uint8_t x, y;
    
    for (int i=32; i < 80; i++) {
        x=(i % 8);
        y=(i / 8);
        
        pixel(x, y, translate(array[i]));
    }
}

//turns on the line and color
void pixel(uint8_t x, uint8_t y, long color) {
    uint8_t red, green, blue, xPin, yPin;
    
    //translate color
    red=((color & (255L<<16))>>16);
    green=((color & (255L<<8))>>8);
    blue=((color & (255L<<0))>>0);
    
    //Turn on correct x/y via look-up array
    //xPin=
    //yPin=
    
    PWMOut(1, red);
    delay_us(5);
    PWMOut(2, green);
    delay_us(5);
    PWMOut(3, blue);
    delay_us(5);
    
    //Turn off x/y
}