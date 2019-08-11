//
//  main.c
//  
//
//  Created by Tekbots on 4/11/15.
//
//

#define F_CPU 16000000UL

#include <stdio.h>
#include <avr/io.h>

int main(void) {
    DDRB=0x0F;
    DDRF=0x00;
    DDRD=0x40;
    
    uint8_t one, two, three, four;
    
    PORTD |= (1<<6);
    
    while (1) {
        one=~PINF & (1<<0);
        two=~PINF & (1<<1);
        three=~PINF & (1<<5);
        four=~PINF & (1<<6);
        
        PORTB=(one<<0) | (two<<1) | (three<<2) | (four<<3);
        PORTD=((!one && !two && !three && !four)<<6);
    }
        
    return 0;
}