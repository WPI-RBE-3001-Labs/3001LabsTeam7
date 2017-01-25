/*
 * ADC.c
 *
 *  Created on: Jan 22, 2017
 *      Author: Chris O'Shea, Carolyn Lowe, Tung Truong
 */

#include "main.h"

void initADC(int channel){
	//Set Port A register for the corresponding channel to input
	DDRA &= ~(1 << channel);

	//Disable digital input on ADC channel to save power
	DIDR0 |= (1 << channel);

	//Set ADC voltage reference to AVCC with external capacitor at AREF pin (5V)
	ADMUX &= (1<<REFS1);
	ADMUX |= (1<<REFS0);

	//Select the ADC prescaler to division factor of 128
	ADCSRA |= (1<<ADPS2);
	ADCSRA |= (1<<ADPS1);
	ADCSRA |= (1<<ADPS0);

	//Enable the ADC
	ADCSRA |= (1<<ADEN);

}

void clearADC(int channel){
	//Set PORT A register for corresponding channel to input
	DDRA |= (1 << channel);

	//Enable digital input on this channel
	DIDR0 &= ~(1 << channel);

	//Clear ADC data registers
	ADCH = 0;
	ADCL = 0;
	ADC = 0;
}

unsigned short getADC(int channel){
	//Select the channel
	ADMUX &= (1<<REFS1);
	ADMUX &= (1<<REFS0);
	ADMUX &= (1<<ADLAR);
	ADMUX |= channel;

	//Start an ADC conversion
	ADCSRA |= (1<<ADCSC);

	//wait for conversion to complete
	while(ADCSRA & (1<<ADSC));
	return ADC;
}


