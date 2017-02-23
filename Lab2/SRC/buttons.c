/*
 * buttons.c

 *
 *  Created on: Feb 12, 2017
 *      Author: coshea
 */
#include "buttons.h"
#include "DAC.h"
#include "motors.h"

char oldBits, newBits = 0x00;
#define BIT0 0x00000001b
#define BIT1 0x00000010b
#define BIT2 0x00000100b
#define BIT3 0x00001000b
#define BIT4 0x00010000b
#define BIT5 0x00100000b
#define BIT6 0x01000000b
#define BIT7 0x10000000b

int v;


//initializes buttons to port C inputs
void initButtons(){
	DDRCbits._P0 = INPUT;
	DDRCbits._P4 = INPUT;
	DDRCbits._P3 = INPUT;
	DDRCbits._P6 = INPUT;
}

///* initially returns 0x00 but returns button values
// * as a the lower 4 bits of a char if there is a change
// * in the state of the buttons */
//char readButtons(){
//	newBits = (~(PINCbits._P6<<3) | ~(PINCbits._P3<<2) | ~(PINCbits._P2<<1) | ~(PINCbits._P0));
//	if(newBits != oldBits){
//	oldBits = newBits;
//	return newBits;
//	}
//	return oldBits;  //returns 0x00 if no button pressed
//}  //not sure if this is working yet

void setMotorVoltage(){
//printf("button pressed");
v = buttonToInt(readButtons());
	switch(v){

	case 1: // 0 Volts
		stopMotors();
		//printf("case 1\n\r");
		break;
	case 2: // 3 Volts
		setDAC(0, 2048);
		setDAC(1, 0);
		//printf("case 2\n\r");
		break;
	case 3: // -3 Volts
		setDAC(0, 0);
		setDAC(1, 2048);
		//printf("case 3\n\r");
		break;
	case 4: // 6 Volts
		setDAC(0, 4095);
		setDAC(1, 0);
		//printf("case 4\n\r");
		break;
	default:
		setDAC(0, 0);
		setDAC(1, 0);
		//printf("default\n\r");
	}
}

unsigned char readButtons(){
// Return the state of the buttons as {B4,B3,B2,B1}
// in the lower nibble of the return value

	char b1 = (PINCbits._P0 & BIT0);
	char b2 = (PINCbits._P2 & BIT2);
	char b3 = (PINCbits._P3 & BIT3);
	char b4 = (PINCbits._P6 & BIT6);

	char ret = (b4 << 3) | (b3 << 2) | (b2 << 1) | (b1);
	return ret;
}

int buttonToInt(unsigned char button) {
	if (button == 14) {
  		return 1;
  	}

  	else if (button == 13) {
  		return 2;
  	}

  	else if (button == 11) {
  		return 3;
  	}

  	else if (button == 7) {
  		return 4;
  	}

  	else {
  		return 0;
  	}
}

