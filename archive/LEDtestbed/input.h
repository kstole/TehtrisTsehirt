//
//  input.h
//  
//
//  Created by Tekbots on 4/11/15.
//
//

#ifndef ____input__
#define ____input__

#include <avr/io.h>
#include <stdio.h>


/*
 Takes in a value 0-3 to select a button to query.
 Returns the state of the button as a uint8 of either 1 or 0.
*/
uint8_t getButton(uint8_t);

#endif /* defined(____input__) */
