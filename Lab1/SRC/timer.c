/*
 * timer.c

 *
 *  Created on: Aug 24, 2016
 *      Author: joest
 */

#include <RBELib/RBELib.h>



//currently only timer 0
//currently only normal mode =0 and CTC mode = 4

void initTimer(int timer, int mode, unsigned int comp)
{
	//if (timer == 0)
//	{
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




//	}
}

/*
void initTimer(int timer, int mode, unsigned int comp)
{
	switch(timer)
	{
	case 0:
		comp &= 0xFF;
		if (mode == 0x00) //normal mode
		{
			TCCR0A = 0x00;
			TCCR0B = (1 << CS01);	//prescalar is 8
			TIMSK0 = (1 << TOIE0);
		}
		else if(mode == 0x01) // CTC Phase Corrected PWM mode
		{
			TCCR0A = (1 << COM0A0)| (1 << WGM00); //Use toggling outpit pin of OC0A only OC0B is disconnected
			TCCR0B = (1 << WGM02) | (1 << CS01); //Use toggling on output and 8 prescalar
			TIMSK0 = (1 << OCIE0A);
			OCR0A = comp;
		}
		else if (mode == 0x2) //CTC mode
		{
			TCCR0A = (1 << WGM01);
		}
		break;
	case 1: //timer1
		break;
	default: //timer 2
		break;
	}
}
*/

void setCompValue(unsigned char timer, unsigned short int comp)
{
	// For using Timer 0
	if (timer == 0){

		// Sets an 8-bit value for the clock to count to
		OCR0A = comp;
	}
}
/*
 * void setCompValue(unsigned char timer, unsigned short int comp)
{
	switch(timer)
	{
	case 0:
		comp &= 0xFF;
		OCR0A = comp;
		break;
	case 1:
		OCR1A = comp;
		break;
	default:
		comp &= 0xFF;
		OCR2A = comp;
		break;
	}
}
*/


