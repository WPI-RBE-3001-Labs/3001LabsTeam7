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
//void initSPI() {
//
//	PRR = 0;
//
//	DDRB |= (1 << DDB5) | (1 << DDB7) | (1 << DDB4); //MOSI SCK SS enable
//
//	DDRD |= (1 << DDD4) | (1 << DDD7); //sets D4 as output for DAC
//									   // sets D7 as output for Accelerometer
//
//	DDRC |= (1 << DDC4) | (1 << DDC5); //sets C4 and C5 as outputs for Encoders
//
//	PORTD |= ~(1 << PD4); // SS low for soft reset
//
//	PORTD |= (1 << PD4); // SS high to deselect
//
//	PORTC |= (1 << PC4) | (1 << PC5); // SS high to deselect
//
//	DDRB &= ~(1 << DDB6); //MISO enable
//
//	SPCR |= (1 << SPE) |  (1<<MSTR) | (1 << SPR1) | (1 << SPR0); // Enable SPI, set as master, set SCK frequency to oscillation frequency/128
//
//	SPSR &= ~(1 << SPI2X);
//
//}
void initSPI(void){
  //Master SS line = output
  SPI_MASTER_SS = OUTPUT;
  //MOSI = output
  SPIDDRbits._MOSI = OUTPUT;
  //SPI clock = output
  SPIDDRbits._SCK = OUTPUT;
  //MISO = input
  SPIDDRbits._MISO = INPUT;

  //Bit 7: Disable interrupts
  //Bit 6: Enable the SPI lines
  //Bit 5: MSB transmitted first
  //Bit 4: Master mode
  //Bit 3: CLK low when idle
  //Bit 2: Sample on leading edge of signal
  //Bits 1 - 0: 128 CLK prescaler
  SPCR = 0x53;

  //DAC SS = output
  DAC_SS_ddr = OUTPUT;
  //Bring the SS line low first (datasheet)
  //Important after soft-resets.  Then deassert.
  DAC_SS = 0;
  DAC_SS = 1;
DDRDbits._P7=OUTPUT;
PORTDbits._P7=1;
  //Encoders SS lines = outputs
  ENCODER_SS_0_ddr = OUTPUT;
  ENCODER_SS_1_ddr = OUTPUT;
  //Deassert
  ENCODER_SS_0 = 1;
  ENCODER_SS_1 = 1;
}


unsigned char spiTransceive(BYTE data) {
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));

	unsigned char data_reg = SPDR;

	/* Returns the register value */
	return data_reg;
}
