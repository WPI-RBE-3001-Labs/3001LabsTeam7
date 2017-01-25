/*
 * globals.h
 *
 *  Created on: Jan 22, 2017
 *      Author: coshea
 */

#ifndef SRC_GLOBALS_H_
#define SRC_GLOBALS_H_

#include "main.h"

typedef struct{
	volatile unsigned short ADCValue;
	volatile unsigned long int timeStamp;
	volatile unsigned int s;
	volatile unsigned int m;
	volatile unsigned int h;
	volatile uint16_t PWMCurrentCount;
	uint8_t PWMPort;
	uint8_t PWMPin;
	uint16_t PWMHighTime;
	uint16_t PWMMaxTime;
	uint16_t PWMCompare;
	float PWMFrequency;
	float PWMDuty;
	volatile uint8_t sampleDataAvailable;
	volatile uint16_t elapsedCycles;
	volatile float latchedCycles;
} Globals;


extern Globals globals;

void initGlobals();

#endif /* SRC_GLOBALS_H_ */
