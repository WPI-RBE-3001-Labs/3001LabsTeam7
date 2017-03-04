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

static int v; // switch variable for setMotorVoltages


//initializes buttons to port C inputs 0, 2, 3 and 6 (the spare pins on c)
void initButtons(){
	DDRCbits._P0 = INPUT; // B1 = C_0_M
	DDRCbits._P2 = INPUT; // B2 = C_2_M
	DDRCbits._P3 = INPUT; // B3 = C_3_M
	DDRCbits._P6 = INPUT; // B4 = C_6_M
}

/*
 * Used to test motors and drive at
 * different voltages according to
 * the button pressed
 *
 * B1 = all motors STOP
 * B2 = 3 volts forward on the lower link
 * B3 = 3 volts backwards on the lower link
 * B4 = 6 volts forwards on the lower link
 *
 */
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


/*
 * reads the state of all buttons and returns a char representing
 * the various states of the buttons which are default HIGH or 1
 */
unsigned char readButtons(){
// Return the state of the buttons as {B4,B3,B2,B1}
// in the lower nibble of the return value

	char B1 = (PINCbits._P0 & BIT0);
	char B2 = (PINCbits._P2 & BIT2);
	char B3 = (PINCbits._P3 & BIT3);
	char B4 = (PINCbits._P6 & BIT6);

	char ret = (B4 << 3) | (B3 << 2) | (B2 << 1) | (B1);
	return ret;
}

/*
 * returns an integer based on what button was pressed
 * ex: B4 -> 4
 *
 */
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

