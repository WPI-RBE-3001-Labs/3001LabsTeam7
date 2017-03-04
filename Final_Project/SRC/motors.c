/*
 * motors.c
 *
 *  Created on: Feb 4, 2017
 *      Author: ttruong
 */
#include "RBELib.h"
#include "DAC.h"
#include "kinematics.h"

#define channelLower 2
#define channelUpper 3
/**
 * @brief Helper function to stop the motors on the arm.
 *
 */
void stopMotors(){
	setDAC(0, 0);
	setDAC(1, 0);
	setDAC(2, 0);
	setDAC(3, 0);
}


/**
 * @brief Drive the end effector of the arm to a desired X and Y position in the workspace.
 *
 * @param x The desired x position for the end effector.
 * @param y The desired y position for the end effector.
 *
 */
void gotoXY(int x, int y){
//fwdKin(x, y);
}

/**
 * @brief Drive a link (upper(1) or lower(0)) in a desired direction.
 *
 * @param link Which link to control.
 * @param dir Which way to drive the link.
 *
 */
void driveLink(int link, int dir){

	switch (link){

		case 0:
			if(dir){
				setDAC(0, 3000);
				setDAC(1, 0);    //drive lower link in in a one direction
			}
			else{
				setDAC(0, 0);
				setDAC(1, 3000);
			}
		break;

		case 1:
			if(dir){
				setDAC(2, 3000);
				setDAC(3, 0);   //drive upper link in in a one direction
			}
			else{
				setDAC(2, 0);
				setDAC(3, 3000);
			}
		break;
	}

}

/**
 * @brief Drive the arm to a "home" position using the potentiometers.  This
 * should be called before using the encoders and just goes to a default position.
 * Once this has been called once, you can initialize/clear the encoders.
 *
 */
void homePos(){
	while(getADC(2) > 250){
		driveLink(0, 0);
	}
	while(getADC(3) > 290){
		driveLink(1, 1);
	}
	stopMotors();
}
