/*
 * SPI.c
 *
 *  Created on: Jan 29, 2017
 *      Author: ttruong
 */


#include "RBELib.h"
#include "avr/io.h"
#include <avr/interrupt.h>


void initSPI(){
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

//sends a byte to the spi and returns what is sent back from the interface
unsigned char spiTransceive(BYTE data) {
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));

	unsigned char data_reg = SPDR;

	/* Returns the register value */
	return data_reg;
}
