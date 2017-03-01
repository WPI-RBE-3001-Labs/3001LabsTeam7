/*
 * fwdKin.c

 *
 *  Created on: Feb 12, 2017
 *      Author: coshea
 */
#include <kinematics.h>
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


//double * inverse(float x, float y){
//	y -= L0;
//
//	float x2 = x*x;
//	float y2 = y*y;
//	float a1 = L1*L1;
//	float a2 = L2*L2;
//
//	float b = atan2(y,x);
//	float g = acos((x2 + y2 + a1 - a2)/(2*L1*sqrt(x2+y2)));
//	float theta1a = (b+g)*(180.0/M_PI) - 90.0;
//	float theta1b = (b-g)*(180.0/M_PI) - 90.0;
//	float theta2 = acos(((x2 + y2) - (a1 + a2))/(2*L1*L2))* 180.0/M_PI - 90.0;
//
//	static double jointValues[3];
//
//	jointValues[0] = theta1a;
//	jointValues[1] = theta1b;
//	jointValues[2] = theta2;
//
//	return jointValues;
//}
