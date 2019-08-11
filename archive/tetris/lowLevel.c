//
//  lowLevel.c
//  
//
//  Created by Marcus Hall on 4/11/15.
//
//

#define F_CPU 16000000UL

#include <avr/io.h>

#include "lowLevel.h"

void writeCKIHigh() {
    PORTB |= (1<<0);
}

void writeCKILow() {
    PORTB &= ~(1<<0);
}

void writeSDIHigh() {
    PORTB |= (1<<0);
}

void writeSDILow() {
    PORTB &= ~(1<<0);
}

void PWMOut(uint8_t channel, uint8_t value) {
    //Red
    if (channel == 1) {
        //setup timer 0
        TCCR0A = (1<<COM0A1) | (1<<WGM01) | (1<<WGM00);
        TCCR0B = (1<<CS00);
        
        //Enable timer 0A interupt
        TIMSK0 |= (1<<OCIE0A);
        
        OCR0A = value;
        
        //turn off other channels
        TCCR0A &= ~(1<<COM0B0);
        TCCR1A &= ~(1<<COM1A0);
    }
    //Green
    else if (channel == 2) {
        //setup timer 1
        TCCR0A = (1<<COM0B1) | (1<<WGM01) | (1<<WGM00);
        TCCR0B = (1<<CS00);
        
        //Enable timer 0B interupt
        TIMSK0 |= (1<<OCIE0B);
        
        OCR0B = value;
        
        //turn off other channels
        TCCR0A &= ~(1<<COM0A1);
        TCCR1A &= ~(1<<COM1A0);
    }
    //Blue
    else if (channel == 3) {
        //setup timer 3
        TCCR1A = (1<<COM1A1) | (1<<WGM01) | (1<<WGM00);
        TCCR1B = (1<<CS10);
        
        //Enable timer 1A interupt
        TIMSK0 |= (1<<OCIE0A);
        
        OCR1A = value;
        
        //turn off other channels
        TCCR0A &= ~(1<<COM0A1) & ~(1<<COM0B1);
    }
}