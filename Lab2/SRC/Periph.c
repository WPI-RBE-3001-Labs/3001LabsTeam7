/*
 * Periph.c

 *
 *  Created on: Feb 12, 2017
 *      Author: coshea
 */

#include "Periph.h"
#include "RBELib.h"
#include "SlaveSelects.h"

#define clr_byte 0x00
#define cntr_byte 0x20
#define read_byte 0x40

void chooseEnc(int chan);
void encSSHigh();

signed long count = 0;
signed long package1 = 0;
signed long package2 = 0;
signed long package3 = 0;
signed long package4 = 0;
int gVal = 0;


/**
 * @brief Find the acceleration in the given axis (X, Y, Z).
 * @param  axis The axis that you want to get the measurement of.
 * @return gVal Value of  acceleration.
 *
 * @todo Create a function that is able to find the acceleration of a given axis.
 */
signed int getAccel(int axis){

	PORTD &= ~(1<<PD7); // assert SS

	spiTransceive(((1 << 4) | (1<<3) | (axis)) << 2);

	gVal = (spiTransceive(0) << 4); //bottom 4 bits
	gVal |= ((spiTransceive(0) >> 4) & 0x0F);

	PORTD |= (1 << PD7); //deassert SS

	return gVal;
}

/**
 * @brief Read an IR sensor and calculate the distance of the block.
 * @param  chan The port that the IR sensor is on.
 * @return value The distance the block is from the sensor.
 *
 * @todo Make a function that is able to get the ADC value of the IR sensor.
 */
int IRDist(int chan){
	return 0; //fix later
}

/**
 * @brief Initialize the encoders with the desired settings.
 * @param chan Channel to initialize.
 *
 * @todo Make a function that can setup both encoder chips on the board.
 */
void encInit(int chan){

	DDRC |= 0x30;

	chooseEnc(chan);  // slave select

	spiTransceive(0x88); //Select MDR0 and set to write
	spiTransceive(0x03);
	encSSHigh();

	chooseEnc(chan);
	spiTransceive(0x48); //Select MDR0 register and read
	encSSHigh(); //slave deselect

}

/**
 * @brief Reset the current count of the encoder ticks.
 * @param chan The channel to clear.
 *
 * @todo Clear the encoder count (set to 0).
 */
void resetEncCount(int chan){
	encSSHigh();
	chooseEnc(chan);
	spiTransceive(clr_byte);
	spiTransceive(0x00);
	encSSHigh();
}

/**
 * @brief Finds the current count of one of the encoders.
 * @param  chan Channel that the encoder is on that you would like to read.
 * @return count The current count of the encoder.
 *
 * @todo Find the current encoder ticks on a given channel.
 */
signed long encCount(int chan){

	chooseEnc(chan); // assert SS for Encoder

	spiTransceive(read_byte | cntr_byte);
	package1 = (spiTransceive(0x00) << 24);
	package2 = (spiTransceive(0x00) << 16);
	package3 = (spiTransceive(0x00) << 8);
	package4 = spiTransceive(0x00);

	encSSHigh(); //deassert encoders
	count = (signed long) (package1 | package2 | package3 | package4); //creates a signed long that contains the results of all spiTransceives bitshifted
	//printf("count = %d\n\r", count);
	if(chan) count = -count; // accounts for difference in upper and lower encoders
	return count;
}
/*
 * slave select based on channel input
 * chan = 0 -> lower link
 * chan = 1 -> upper link
 */
void chooseEnc(int chan){  //slave selects based on channel input
	if(!chan) ENCODER_SS_0 = LOW;
	else ENCODER_SS_1 = LOW;

}

/*
 * deasserts both encoder slave selects
 */
void encSSHigh(){
	ENCODER_SS_0 = HIGH;
	ENCODER_SS_1 = HIGH;
}

