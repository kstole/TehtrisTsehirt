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

#include "lowLevel.h"
#include "ledOutput.h"


void ledOutput(uint8_t *array) {
    uint8_t temp;
    for (int i=0; i < 32; i++) {
        temp=array[i];
        push_to_strip(translate(temp));
    }
    
    push_to_grid(array);
    
    writeCKILow();
    _delay_ms(1);
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
void push_to_grid(uint8_t *array) {
    uint8_t x, y;
    
    for (int i=32; i < 80; i++) {
        x=(i % 8);
        y=(i / 8);
        
        pixel(x, y, translate(array[i]));
    }
}

//turns on the line and color
void pixel(uint8_t x, uint8_t y, uint8_t color) {
    //translate color
    if (color == 0) {
        PORTB |= (1<<2); //Red on
        PORTB &= ~(1<<3); //GREEN off
        PORTB &= ~(1<<4); //BLUE off
    }
    else if (color == 1) {
        PORTB |= (1<<2); //Red on
        PORTB |= (1<<3); //GREEN on
        PORTB &= ~(1<<4); //BLUE off
    }
    else if (color == 2) {
        PORTB |= (1<<2); //Red on
        PORTB &= ~(1<<3); //GREEN off
        PORTB |= (1<<4); //BLUE on
    }
    else if (color == 3) {
        PORTB &= ~(1<<2); //Red off
        PORTB &= ~(1<<3); //GREEN off
        PORTB |= (1<<4); //BLUE on
    }
    else if (color == 4) {
        PORTB &= ~(1<<2); //Red off
        PORTB |= (1<<3); //GREEN on
        PORTB &= ~(1<<4); //BLUE off
    }
    else if (color == 5) {
        PORTB |= (1<<2); //Red on
        PORTB |= (1<<3); //GREEN on
        PORTB |= (1<<4); //BLUE on
    }
    else if (color == 6) {
        PORTB &= ~(1<<2); //Red off
        PORTB |= (1<<3); //GREEN on
        PORTB |= (1<<4); //BLUE on
    }

    
    if (x == 0) {
        PORTD=(1<<0);
    }
    else if (x == 1) {
        PORTD=(1<<1);
    }
    else if (x == 2) {
        PORTD=(1<<2);
    }
    else if (x == 3) {
        PORTD=(1<<3);
    }
    else if (x == 4) {
        PORTC=(1<<6);
    }
    else if (x == 5) {
        PORTD=(1<<7);
    }
    else if (x == 6) {
        PORTD=(1<<4);
    }
    else if (x == 7) {
        PORTD=(1<<6);
    }
    
    if (y == 0) {
        PORTC=(1<<7);
    }
    else if (y == 1) {
        PORTB |= (1<<4);
        PORTB &= ~(3<<5);
    }
    else if (y == 2) {
        PORTB |= (1<<5);
        PORTB &= ~(5<<4);
    }
    else if (y == 3) {
        PORTB |= (1<<6);
        PORTB &= ~(3<<4);
    }
    else if (y == 4) {
        PORTF=(1<<1);
    }
    else if (y == 5) {
        PORTF=(1<<0);
    }
}