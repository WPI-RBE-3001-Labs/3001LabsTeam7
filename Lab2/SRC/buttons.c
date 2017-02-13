/*
 * buttons.c

 *
 *  Created on: Feb 12, 2017
 *      Author: coshea
 */
#include "buttons.h"
#include "DAC.h"


//initializes buttons to port B inputs
void initButtons(){
	DDRCbits._P0 = INPUT;
	DDRCbits._P2 = INPUT;
	DDRCbits._P3 = INPUT;
	DDRCbits._P6 = INPUT;
}

/* initially returns 0x00 but returns button values
 * as a the lower 4 bits of a char if there is a change
 * in the state of the buttons */
char readButtons(){
	char oldBits = 0x00;
	char newBits = (~(3<<PINCbits._P6) | ~(2<<PINCbits._P3) | ~(1<<PINCbits._P2) | ~(PINCbits._P0));
	if(newBits != oldBits){
	oldBits = newBits;
	return newBits;
	}
	return oldBits;  //returns 0x00 if no button pressed
}  //not sure if this is working yet

void setMotorVoltage(){
initButtons();
while(readButtons() == 0x00){}
printf("button pressed");
char v = readButtons();
	switch(v){

	case 0x01: // 0 Volts
		setDAC(0, 4095);
		setDAC(1, 4095);
		break;
	case 0x02: // 3 Volts
		setDAC(0, 2048);
		setDAC(1, 0);
		break;
	case 0x04: // -3 Volts
		setDAC(0, 0);
		setDAC(1, 2048);
		break;
	case 0x08: // 6 Volts
		setDAC(0, 4095);
		setDAC(1, 0);
		break;
	}
}

