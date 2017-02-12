/*
 * Lab3Lib.h
 *
 *  Created on: Feb 12, 2017
 *      Author: coshea
 */
#include "Periph.h"


#ifndef INCLUDE_LAB3LIB_H_
#define INCLUDE_LAB3LIB_H_

int EncoderCounts( int __chan){

	if((__chan != 0) && (__chan != 1)) return -1; //returns -1 for invalid input

	encInit(__chan); //init encoders

	int count = 0;
	int diff = 0;
	int oldCount = 0;
	int newCount = encCount(__chan); // sets value of newCount to current encoder value

	if(!count){
		oldCount = newCount;
		count++;
	}
	else{
		diff = newCount - oldCount;
		oldCount = newCount;
	}
	return diff;

}

int GetAcceration( int __axis){
	int accel = 0;

	return accel;
}

#endif /* INCLUDE_LAB3LIB_H_ */
