/*
 * globals.c
 *
 *  Created on: Jan 22, 2017
 *      Author: coshea
 */

#include "main.h"

//initializes all global variables
void initGlobals(){
	globals.timeStamp = 0;
	globals.s = 0;
	globals.m = 0;
	globals.h = 0;
	globals.PWMPort = 'A';
	globals.PWMPin = 0;
	globals.PWMMaxTime = 0;
	globals.PWMCurrentCount = 0;
	globals.PWMHighTime = 0;
	globals.PWMCompare = 0;
	globals.PWMDuty = 0;
	globals.PWMFrequency = 0;
	globals.sampleDataAvailable = 0;
	globals.elapsedCycles = 0;
}
