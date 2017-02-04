/*
 * PID.c

 *
 *  Created on: Feb 4, 2017
 *      Author: ttruong
 */
#include "RBELib.h"
#include "PID.h"

typedef struct{

	int lastPos;

	int sumError;

	int maxSumError;

	int maxError;

} arm;

arm link1;
pidConst armPID;

/**
 * @brief Sets the Kp, Ki, and Kd values for 1 link.
 * @details to set the values, use the following style
 * @code pidConst.Kp = 1.3; @endcode
 * @param link The link you want to set the values for (H or L).
 * @param Kp Proportional value.
 * @param Ki Integral value.
 * @param Kd Derivative value.
 *
 * @todo Create a function to the the PID constants for a given link.
 */
void setConst(char link, float Kp, float Ki, float Kd){

	if(link == 'H'){
		armPID.Kp_H = Kp;
		armPID.Ki_H = Ki;
		armPID.Kd_H = Kd;
	}
	else if(link == 'L'){
		armPID.Kp_L = Kp;
		armPID.Ki_L = Ki;
		armPID.Kd_L = Kd;
	}
	else printf("Incorrect link input");
}

/**
 * @brief Calculate the PID value.
 * @param  link Which link to calculate the error for (Use 'H' and 'L').
 * @param setPoint The desired position of the link.
 * @param actPos The current position of the link.
 *
 * @todo Make a function to calculate the PID value for a link.
 */
signed int calcPID(char link, int setPoint, int actPos){

	int vel = actPos - link1.lastPos;
		link1.lastPos = actPos;

		int error = setPoint - actPos;
		if((error < link1.maxError) && ((error + link1.sumError) < link1.maxSumError)) link1.sumError += error;

		return (error * armPID.Kp_H) + (vel * armPID.Kd_H) + (link1.sumError * armPID.Ki_H);
}
