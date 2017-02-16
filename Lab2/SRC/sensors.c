/*
 * sensors.c

 *
 *  Created on: Feb 12, 2017
 *      Author: coshea
 */
#include "sensors.h"
#include "Periph.h"


int EncoderCounts( int __chan ){
	int ret;
	if(__chan == 1 || __chan == 0){
		ret = encCount(__chan);
		resetEncCount(__chan);
	}
	else return -1;
	resetEncCount(__chan);
	return ret;
}

int GetAccelerationH48C( int __axis){
		 return getAccel(__axis);
}
