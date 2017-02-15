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

	PRR = 0;

	DDRB |= (1 << DDB5) | (1 << DDB7) | (1 << DDB4); //MOSI SCK SS enable

	DDRD |= (1 << DDD4) | (1 << DDD7); //sets D4 as output for DAC
									   // sets D7 as output for Accelerometer

	DDRC |= (1 << DDC4) | (1 << DDC5); //sets C4 and C5 as outputs for Encoders

	PORTD |= (1 << PD4); // SS high to deselect

	PORTC |= (1 << PC4) | (1 << PC5); // SS high to deselect

	DDRB &= ~(1 << DDB6); //MISO enable

	SPCR |= (1 << SPE) |  (1<<MSTR) | (1 << SPR1) | (1 << SPR0); // Enable SPI, set as master, set SCK frequency to oscillation frequency/128

	SPSR &= ~(1 << SPI2X);

}


unsigned char spiTransceive(BYTE data) {
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
	unsigned char stat_reg = SPSR; //read these to clear interrupts
	unsigned char data_reg = SPDR;

	/* Returns the register value */
	return SPDR;
}
