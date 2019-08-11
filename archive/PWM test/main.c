//
//  PWMtest.c
//  
//
//  Created by Tekbots on 4/11/15.
//
//

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16000000UL


int main(void) {
    //set data direction registers
    DDRD=0x40;
    DDRB=0x80;
    
    //setup timer 0
    TCCR0A = (1<<COM0A1) | (1<<WGM01) | (1<<WGM00);
    TCCR0B = (1<<CS00);
    
    //Enable timer 0 interupt
    TIMSK0 |= (1<<OCIE0A);
    
    //set initial duty cycle
    OCR0A = 100;
    
    //turn on LED
    PORTD |= (1<<6);
    
    while (1) {
        OCR0A += 20;
        _delay_ms(500);
        TCCR0A &= ~(1<<COM0A1);
        _delay_ms(500);
        TCCR0A |= (1<<COM0A1);
    }
    
    return 0;
}


