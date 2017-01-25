/*
 * Timer.c
 *
 *  Created on: Jan 23, 2017
 *      Author: chris
 */

#include "main.h"

/*
 * Inits one of the 3 timers (0 - 2) in NORMAL or CTC mode
 *
 */
void initTimer(unsigned char number, unsigned char mode, unsigned short int comp) {
	//disable global interrupts
	cli();

	switch(number) {
		case 0:
			//Initialize timer to 0
			TCNT0 = 0;
			//disable prescaler
			TCCR0B = (1<<CS02);
			TCCR0B = (1<<CS01);
			TCCR0B = (~(1<<CS00));
			//enable Timer overflow interrupt:
			TIMSK0bits._TOIE0 = 1;
			//Enable Timer interrupt flag
			TIFR0bits._TOV0 = 1;
			break;
		case 1:
			//Initialize timer to 0
			TCNT1 = 0;
			//disable prescaler
			TCCR1Bbits._CS12 = 0;
			TCCR1Bbits._CS11 = 0;
			TCCR1Bbits._CS10 = 1;
			//enable Timer overflow interrupt:
			TIMSK1bits._TOIE1 = 1;
			//Enable Timer interrupt flag
			TIFR1bits._TOV1 = 1;
			break;
		case 2:
			//Initialize timer to 0
			TCNT2 = 0;
			//disable prescaler
			TCCR2Bbits._CS22 = 0;
			TCCR2Bbits._CS21 = 0;
			TCCR2Bbits._CS20 = 1;
			//enable Timer overflow interrupt:
			TIMSK2bits._TOIE2 = 1;
			//Enable Timer interrupt flag
			TIFR2bits._TOV2 = 1;
			break;
	}

	//write CTC mode
	//re-enable global interrupts
	sei();
}
