/*
 * motorCurrent.c
 *
 *  Created on: Feb 5, 2017
 *      Author: coshea
 */
#include "RBELib.h"
#include "current.h"
#include <stdarg.h>
#include "reg_structs.h"

/*
 * initializes the current sensor by setting
 * the pin A to read as the input of the ADC
 * based upon motor parameter 0 for lower link
 * motor and 1 for upper link motor
 */
void initCurrentSense(int motor){

	switch(motor){
		case 0:
			DDRAbits._P0 = INPUT;
			break;

		case 1:
			DDRAbits._P1 = INPUT;
			break;

		default:
			DDRAbits._P0 = INPUT;
			DDRAbits._P1 = INPUT;
			break;
	}
}


/*
 * sets the direction of required pins and polls
 * channel corresponding to the motor parmeter
 * then converts that value from adc ticks to
 * milliAmps
 */
int readCurrent(int motor){
	int val = getADC(motor);
	return val;
}
