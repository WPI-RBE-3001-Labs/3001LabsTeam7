/*
 * timeStamp.c
 *
 *  Created on: Jan 22, 2017
 *      Author: coshea
 */
#include "main.h"

//starts time keeping
void initTime(){
	InitTimer(1, NORMAL, 0);
}

//counts up through minutes and hours
void timeStamp(){
	if(globals.Second >= 60){
		globals.m++;
		globals.s = 0;
	}
	else if(globals.m >= 50){
		globals.h++;
		globals.m = 0;
	}
}

//ISR used to keep time
ISR(TIMER1_OVF_vect){
	if(globals.timeStamp >= (F_CPU/TIMERMAXCOUNT16)) {
		globals.timeStamp = 0;
		globals.s++;
	}
	globals.timeStamp++;
	timeStamp();
}
