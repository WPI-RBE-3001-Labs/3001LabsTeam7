/*
 * SPI.c
 *
 *  Created on: Jan 29, 2017
 *      Author: ttruong
 */


#include "RBELib.h"
#include "avr/io.h"
#include <avr/interrupt.h>

/**
 * @brief Initializes the SPI bus for communication with all of your
 * SPI devices.
 *
 * @todo Create the function that will allow you to initialize the SPI
 * in a mode compatible with all devices.  Do not forget to deassert all
 * of your SS lines!
 */
void initSPI() {
	PORTC = 0x00;

	DDRD |= (OUTPUT<<DDD4);
	PORTD |= (HIGH<<PD4);

	/* Set MOSI and SCK output, all others input */
	DDRB = (1<<DDB5)|(1<<DDB7)|(1<<DDB4);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR);

	DDRC = 0x80;
}


unsigned char spiTransceive(BYTE data) {
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
	/* Read the register to see what was sent back*/
	return SPDR;
}
