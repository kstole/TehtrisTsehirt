//
//  main.c
//  
//
//  Created by Tekbots on 4/12/15.
//
//

#include <stdio.h>
#include <avr/io.h>

#include "lowLevel.h"
#include "input.h"

#define F_CPU 16000000UL

void setup(void);

int main(void) {
    setup();
//    if (getButton(0)) {
//        <#statements#>
//    }
    
    for (int i=0; i<8; i++) {
        for (int j=0; j<6; j++) {
            pixel(i, j, 0);
        }
    }
    
    for (int i=0; i<32; i++) {
        push_to_strip(0xFF00FF);
    }
    
    _delay_ms(1);
    
    
    return 0;
}

void setup(void) {
    DDRB=0xFF;
    DDRF=0xFF;
    DDRF=0xF0;
    DDRC=0xC0;
}