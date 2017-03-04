/*
 * timer.c

 *
 *  Created on: Aug 24, 2016
 *      Author: joest
 */

#include "RBELib.h"



//only needed timer 0 with 256 prescalar and interrupts

void initTimer(int timer, int mode, unsigned int comp)
{
		//Enables Timer0 Interrupt overflow mode
		//TIMSK0 = 0x01;
		TIMSK0|=(1<<TOIE0);
		sei();
		//TCNT0=0x00;
		//Sets 256 prescalar
		TCCR0B |= (1 << CS01);//|(1 << CS00);

		//Sets all bits LOW
		//OCR0A = 0x00;

		//Sets Clock with no prescaling
		//TCCR0B = 0x01;
		// prescale 256
		//TCCR0B = (1 << CS01)|(1 << CS00);





}

