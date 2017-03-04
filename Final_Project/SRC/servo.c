/*
 * servo.c
 *
 *  Created on: Feb 19, 2017
 *      Author: coshea
 */
#include "setServo.h"
#include "servo.h"

//closes gripper on specified servo port
void close(int chan){
	setServo(chan, HIGHVAL);
}

//opens grippper on specified servo port
void open(int chan){
	setServo(chan, LOWVAL);
}

//runs the belt at a constant velocity
void belt(int chan){
	setServo(chan, HIGHVAL);
}
