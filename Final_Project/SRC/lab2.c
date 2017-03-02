/*
 * lab2.c
 *
 *  Created on: Feb 18, 2017
 *      Author: coshea
 */
#include "RBELib.h"
#include "lab2.h"
#include "SPI.h"
#include "DAC.h"
#include "current.h"
#include "USARTDebug.h"

unsigned int lowADC;
float current = 0;




//*************************************************************************************************************************//
//                         LAB2

void lab2(int x){
	switch(x){

	case 0: //triangle wave
		while(1){
		triangle(0,1);
		}
	break;

	case 1: //current sense
		while(1){
			toggleArm(0, 250);
			lab2(1);
		}
	break;

	case 2: //PID
		initSPI();

	break;

	case 3: //armAngle
		initSPI();

	break;
	}
}

//outputs two triangle waveforms (offset by 1/2 their period) based upon specified DAC channels
void triangle(int DAC1, int DAC2){

	for(int i = 0; i < 4096; i++){ //increments DAC SPIVal from 0 - 4095
		setDAC(DAC1, i);
		setDAC(DAC2, 4095 - i);
	}

	for(int j = 4095; j >= 0; j--){ //increments DAC SPIVal from 4095 - 0
		setDAC(DAC1, j);
		setDAC(DAC2, 4095 - j);
	}
}

void toggleArm(int link, int time){
		driveLink(link, 1);
		_delay_ms(time);
		driveLink(link, 0);
		_delay_ms(time);
}

void currentSense(int motor){
	//while(1){
		current = readCurrent(motor);
		printf("Current(mA) = %f \n\r", (double) current);
		//_delay_ms(100);
	//}
}

