/*
 * fwdKin.c

 *
 *  Created on: Feb 12, 2017
 *      Author: coshea
 */
#include "fwdKin.h"
#include <math.h>

#define L0 142.4
#define L1 152.4
#define L2 124

double degtoRad(double theta){
	return theta*(M_PI/180);
}

double * calcPos(int JA1, int JA2){

	static double xyPos[2];

	xyPos[0] = cos(degtoRad(JA1))*L1 + cos(degtoRad(JA1 + JA2))*L2;
	xyPos[1] = sin(degtoRad(JA1))*L1 + sin(degtoRad(JA1 + JA2))*L2 + L0;

	return xyPos; //returns mem loc of xy coords of end effector
}
