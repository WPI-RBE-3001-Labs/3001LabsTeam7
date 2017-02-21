/*
 * servo.c
 *
 *  Created on: Feb 19, 2017
 *      Author: coshea
 */
#include "setServo.h"
#include "servo.h"

void close(int chan){
	setServo(chan, HIGHVAL);
}

void open(int chan){
	setServo(chan, LOWVAL);
}

void belt(int chan){
	setServo(chan, HIGHVAL);
}
