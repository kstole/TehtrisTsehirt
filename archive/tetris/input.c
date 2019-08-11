//
//  input.c
//  
//
//  Created by Tekbots on 4/11/15.
//
//

#include <avr/io.h>

#define F_CPU 16000000UL

#include "input.h"

uint8_t getButton(uint8_t button) {
    uint8_t state;
    
    return (PINF & (1<<button));
}