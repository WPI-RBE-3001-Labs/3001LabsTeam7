///*
// * PID.c
//
// *
// *  Created on: Feb 4, 2017
// *      Author: ttruong
// */
//#include "RBELib.h"
//#include "PID.h"
//
//typedef struct{
//
//	int lastPos;
//
//	int sumError;
//
//	int maxSumError;
//
//	int maxError;
//
//} arm;
//
//arm link1;
//pidConst armPID;
//
///**
// * @brief Sets the Kp, Ki, and Kd values for 1 link.
// * @details to set the values, use the following style
// * @code pidConst.Kp = 1.3; @endcode
// * @param link The link you want to set the values for (H or L).
// * @param Kp Proportional value.
// * @param Ki Integral value.
// * @param Kd Derivative value.
// *
// * @todo Create a function to the the PID constants for a given link.
// */
//void setConst(char link, float Kp, float Ki, float Kd){
//
//	if(link == 'H'){
//		armPID.Kp_H = Kp;
//		armPID.Ki_H = Ki;
//		armPID.Kd_H = Kd;
//	}
//	else if(link == 'L'){
//		armPID.Kp_L = Kp;
//		armPID.Ki_L = Ki;
//		armPID.Kd_L = Kd;
//	}
//	else printf("Incorrect link input");
//}
//
///**
// * @brief Calculate the PID value.
// * @param  link Which link to calculate the error for (Use 'H' and 'L').
// * @param setPoint The desired position of the link.
// * @param actPos The current position of the link.
// *
// * @todo Make a function to calculate the PID value for a link.
// */
//signed int calcPID(char link, int setPoint, int actPos){
//
//	int vel = actPos - link1.lastPos;
//		link1.lastPos = actPos;
//
//		int error = setPoint - actPos;
//		if((error < link1.maxError) && ((error + link1.sumError) < link1.maxSumError)) link1.sumError += error;
//
//		return (error * armPID.Kp_H) + (vel * armPID.Kd_H) + (link1.sumError * armPID.Ki_H);
//}

#include "RBELib.h"
#include "PID.h"
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
//long pidErrorSum = 0;
long pidLastError_L = 0;
long pidPrevLastError_L = 0;
long pidLastError_H = 0;
long pidPrevLastError_H = 0;
long pidPrev_L = 0;
long pidPrev_H = 0;
float pidTd_H = 0;
float pidTi_inv_H = 0;
float pidTd_L = 0;
float pidTi_inv_L = 0;
pidConst pidConsts;
void setConst(char link, float Kp, float Ki, float Kd)
{
	switch(link)
	{
	case 'H':
		pidConsts.Kp_H = Kp;
		pidConsts.Ki_H = Ki;
		pidConsts.Kd_H = Kp;
		pidTd_H = Kd / Kp;
		pidTi_inv_H = (Ki / Kp);
		break;
	case 'L':
		pidConsts.Kp_L = Kp;
		pidConsts.Ki_L = Ki;
		pidConsts.Kd_L = Kd;
		pidTd_L = Kd / Kp;
		pidTi_inv_L = (Ki / Kp);
		break;
	}

}

/**
 * @brief Calculate the PID value.
 * @param  link Which link to calculate the error for (Use 'H' and 'L').
 * @param setPoint The desired position of the link.
 * @param actPos The current position of the link.
 *
 * @todo Make a function to calculate the PID value for a link.
 */
signed int calcPID(char link, int setPoint, int actPos)
{
	long error = setPoint - actPos;
	long pidValue = 0;
	if (link == 'L')
	{
		pidValue = pidPrev_L + pidConsts.Kp_L * ((1 + pidTi_inv_L + pidTd_L) * error  + (-1 - 2 * pidTd_L) * pidLastError_L + pidTd_L * pidPrevLastError_L);
		pidPrev_L = pidValue;
		pidPrevLastError_L = pidLastError_L;
		pidLastError_L = error;
	}
	else
	{
		pidValue = pidPrev_H + pidConsts.Kp_H * ((1 + pidTi_inv_H + pidTd_H) * error  + (-1 - 2 * pidTd_H) * pidLastError_H + pidTd_H * pidPrevLastError_H);
		pidPrev_H = pidValue;
		pidPrevLastError_H = pidLastError_H;
		pidLastError_H = error;
	}
	if(pidValue>4000) pidValue=4000;
	if(pidValue<-4000) pidValue=-4000;
	return pidValue;
}

