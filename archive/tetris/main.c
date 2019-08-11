//
//  main.c
//  
//
//  Created by Marcus Hall on 4/11/15.
//
//

#include <stdio.h>
#include <avr/io.h>

#define F_CPU 16000000UL

void setup();

//make stuff do...
int main() {
    setup();
    
    PORTD &= 0x00;
    PORTD=(1<<4);
    
    //repeats code
    while (1) {
        ;
    }
}

void setup() {
    //set data direction registers
    DDRD=0x51;
    DDRB=0x83;
    DDRF=0x00;
}