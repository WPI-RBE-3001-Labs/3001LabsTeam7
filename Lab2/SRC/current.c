/*
 * motorCurrent.c
 *
 *  Created on: Feb 5, 2017
 *      Author: coshea
 */
#include "RBELib.h"
#include "current.h"

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

float readCurrent(int motor){
	//initCurrentSense(motor);
	initADC(motor);
	float val = (float) getADC(motor);
	val = (val * (7.2/1023)) - 1.6;
	return val/10;
}
