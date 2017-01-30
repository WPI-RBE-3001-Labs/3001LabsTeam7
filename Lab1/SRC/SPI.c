/*
 * SPI.c
 *
 *  Created on: Jan 29, 2017
 *      Author: ttruong
 */
#include "RBELib/RBELib.h"

/**
 * @brief Initializes the SPI bus for communication with all of your
 * SPI devices.
 *
 * @todo Create the function that will allow you to initialize the SPI
 * in a mode compatible with all devices.  Do not forget to deassert all
 * of your SS lines!
 */
void initSPI(){

	SPI_MISO_DDR = 0; // MISO = input
	SPI_MOSI_DDR, SPI_SCK_DDR = 1; // MOSI, SCK = outputs

	SPI_MISO, SPI_MOSI, SPI_SCK= 0; //MOSI, MISO and SCK set to low

	DDRB |= (1<<DDB4);

	SPCR |= (0<<SPIE);  // do not enable interrupt
	SPCR |= (1<<SPE);   // enables SPI
	SPCR |= (0<<DORD);  // MSB transmitted first
	SPCR |= (1<<MSTR);  // master mode enabled
	SPCR |= (0<<CPOL);  // clock signal is positive
	SPCR |= (0<<CPHA);  // sends on rising edge
	SPCR |= (1<<SPR1);  // set clock to oscillation_frequency/64
	SPCR |= (0<<SPR0);  // set clock to oscillation_frequency/64

	SPSR = (0<<SPI2X);  // do not enable 2x speed mode - not sure if necessary


}

/**
 * @brief Send and receive a byte out of the MOSI line.
 *
 * Please note that even if you do not want to receive any data back
 * from a SPI device, the SPI standard requires you still receive something
 * back even if it is junk data.
 *
 * @param data The byte to send down the SPI bus.
 * @return value The byte shifted in during transmit
 *
 * @todo Make a function that will send a byte of data through the SPI
 * and return whatever was sent back.
 */
unsigned char spiTransceive(BYTE data){
	//Start Transmission

	SPDR = data;

	// Wait for Transmission to Finish

	while(!((SPSR) & (1<<SPIF)));

	//Return Data Transmitted by the SPI

	return SPDR;

}
