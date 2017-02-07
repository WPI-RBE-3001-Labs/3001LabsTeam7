/*
 * motorCurrent.c
 *
 *  Created on: Feb 5, 2017
 *      Author: coshea
 */
#include "RBELib.h"
#include "current.h"

/*
 * initializes the current sensor by setting
 * the pin A to read as the input of the adc
 * based upon motor parameter 0 for lower link
 * motor and 1 for upper link motor
 */
void initCurrentSense(int motor){

	switch(motor){
		case 0:
			setPinsDir('A', INPUT, 1, 0);
			break;

		case 1:
			setPinsDir('A', INPUT, 1, 1);
			break;

		default:
			setPinsDir('A', INPUT, 1, 0);
			setPinsDir('A', INPUT, 1, 1);
			break;
	}
}


/*
 * sets the direction of required pins and polls
 * channel corresponding to the motor parmeter
 * then converts that value from adc ticks to
 * milliAmps
 */
float readCurrent(int motor){
	initCurrentSense(motor);
	initADC(motor);
	float val = (float) getADC(motor);
	val = (val * (7.2/1023)) - 2.5;
	return val*100;
}
