/*
 * buttons.c

 *
 *  Created on: Feb 12, 2017
 *      Author: coshea
 */
#include "buttons.h"



//initializes buttons to port B inputs
void initButtons(){
	DDRBbits._P4 = INPUT;
	DDRBbits._P5 = INPUT;
	DDRBbits._P6 = INPUT;
	DDRBbits._P7 = INPUT;
}

/* initially returns 0x00 but returns button values
 * as a the lower 4 bits of a char if there is a change
 * in the state of the buttons */
char readButtons(){
	char oldBits = 0xFF;
	char newBits = (!PINBbits._P4 & !PINBbits._P5 & !PINBbits._P6 & !PINBbits._P7);
	if(newBits != oldBits){
	oldBits = newBits;
	//printf("bits changed\n\r");
	return newBits;
	}
	return oldBits;
}  //not sure if this is working yet


