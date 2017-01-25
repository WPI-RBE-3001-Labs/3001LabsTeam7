/*
 * buttonInterrupts.c
 *
 *  Created on: Jan 22, 2017
 *      Author: coshea
 */


#include "main.h"

//configures four buttons on pins D4 - D7 to trigger pin change interrupts
void configureButtonInterrupts(){
	cli();//disables interrupts

	//buttons as inputs and clearing old bits
	DDRD &= ~(BIT7|BIT6|BIT5|BIT4);

	//enables pin interrupts
	PCMSK3 |= (BIT7|BIT6|BIT5|BIT4);
	PCICR |= BIT3;

	//clears the flag
	PCIFR |= BIT3;

	sei();//re-enables interrupts
}
