/*
 * Periph.c

 *
 *  Created on: Feb 12, 2017
 *      Author: coshea
 */

#include "Periph.h"
#include "RBELib.h"
#include "SlaveSelects.h"

void chooseEnc(int chan);
void resetEncoders();

/**
 * @brief Find the acceleration in the given axis (X, Y, Z).
 * @param  axis The axis that you want to get the measurement of.
 * @return gVal Value of  acceleration.
 *
 * @todo Create a function that is able to find the acceleration of a given axis.
 */
signed int getAccel(int axis){
	signed int accelVal = 0;

	/*
	 * @todo read accelerometer values
	 */

	return accelVal;
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

	chooseEnc(chan);
	spiTransceive(0x88); //Select MDR0 and set to write
	spiTransceive(0x03);
	resetEncoders();

	chooseEnc(chan);
	spiTransceive(0x48); //Select MDR0 register and read
	resetEncoders();

}

/**
 * @brief Reset the current count of the encoder ticks.
 * @param chan The channel to clear.
 *
 * @todo Clear the encoder count (set to 0).
 */
void resetEncCount(int chan){

	chooseEnc(chan);
	spiTransceive(0x20);
	resetEncoders();

}

/**
 * @brief Finds the current count of one of the encoders.
 * @param  chan Channel that the encoder is on that you would like to read.
 * @return count The current count of the encoder.
 *
 * @todo Find the current encoder ticks on a given channel.
 */
signed long encCount(int chan){
	signed long count = 0;
	chooseEnc(chan);

	/*
	 * @todo insert code to read from SPI
	 */

	resetEncoders();
	if(!chan) count = -count; // accounts for difference in upper and lower encoders
	return count;
}

void chooseEnc(int chan){
	if(!chan) ENCODER_SS_0 = LOW;
	else if(chan) ENCODER_SS_1 = LOW;
	else{
		printf("invalid channel");
		return;
	}
}

void resetEncoders(){
	ENCODER_SS_0 = HIGH;
	ENCODER_SS_1 = HIGH;
}

