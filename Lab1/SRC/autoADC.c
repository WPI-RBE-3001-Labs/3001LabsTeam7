/*
 * autoADC.c
 *
 *  Created on: Jan 22, 2017
 *      Author: coshea
 */


#include "main.h"

//Initializes ADC to operate in free-run mode
//meaning new conversions will start when previous is complete
void initFreeRunADC(unsigned char channel){
	//global interrupts disabled
	cli();

	//ADC initialization
	InitADC(channel);

	//sets ADC channel
	ADMUX &= (1<<REFS1);
	ADMUX &= (1<<REFS0);
	ADMUX &= (1<<ADLAR);
	ADMUX |= channel;

	//Enables ADC free-run mode
	ADCSRB &= (1<<ADTS2);
	ADCSRB &= (1<<ADTS1);
	ADCSRB &= (1<<ADTS0);

	//enable trigger and ADC interrupts and starts conversion
	ADCSRA |= (1<<ADATE);
	ADCSRA |= (1<<ADIE);
	ADCSRA |= (1<<ADEN);


	//global interrupts enabled
	sei();
}

//this ISR gets called when the ADC completes its conversion
ISR(ADC_vect){
//save ADC value to a global variable
}
