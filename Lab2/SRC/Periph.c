/*
 * Periph.c

 *
 *  Created on: Feb 12, 2017
 *      Author: coshea
 */

#include "Periph.h"
#include "RBELib.h"
#include "SlaveSelects.h"

//Count modes
#define NQUAD 0x00 //non-quadrature mode
#define QUADRX1 0x01 //X1 quadrature mode
#define QUADRX2 0x02 //X2 quadrature mode
#define QUADRX4 0x03 //X4 quadrature mode
//Running modes
#define FREE_RUN 0x00
#define SINGE_CYCLE 0x04
#define RANGE_LIMIT 0x08
#define MODULO_N 0x0C
//Index modes
#define DISABLE_INDX 0x00 //index_disabled
#define INDX_LOADC 0x10 //index_load_CNTR
#define INDX_RESETC 0x20 //index_rest_CNTR
#define INDX_LOADO 0x30 //index_load_OL
#define ASYNCH_INDX 0x00 //asynchronous index
#define SYNCH_INDX 0x80 //synchronous index
//Clock filter modes
#define FILTER_1 0x00 //filter clock frequncy division factor 1
#define FILTER_2 0x80 //filter clock frequncy division factor 2
/* **MDR1 configuration data; any of these***
 ***data segments can be ORed together***/
//Flag modes
#define NO_FLAGS 0x00 //all flags disabled
#define IDX_FLAG 0x10 //IDX flag
#define CMP_FLAG 0x20 //CMP flag
#define BW_FLAG 0x40 //BW flag
#define CY_FLAG 0x80 //CY flag
//1 to 4 bytes data-width
#define BYTE_4 0x00 //four byte mode
#define BYTE_3 0x01 //three byte mode
#define BYTE_2 0x02 //two byte mode
#define BYTE_1 0x03 //one byte mode
//Enable/disable counter
#define EN_CNTR 0x00 //counting enabled
#define DIS_CNTR 0x04 //counting disabled

/* LS7366R op-code list */
#define CLR_MDR0 0x08
#define CLR_MDR1 0x10
#define CLR_CNTR 0x20
#define CLR_STR 0x30
#define READ_MDR0 0x48
#define READ_MDR1 0x50
#define READ_CNTR 0x60
#define READ_OTR 0x68
#define READ_STR 0x70
#define WRITE_MDR1 0x90
#define WRITE_MDR0 0x88
#define WRITE_DTR 0x98
#define LOAD_CNTR 0xE0
#define LOAD_OTR 0xE4
#define Slave_Select_Low PORTB &= ~(1 << PB4)
#define Slave_Select_High PORTB |= (1 << PB4)
/*Configure and initialize the SPI on PortB of uC*/


signed long count = 0;
signed long package1 = 0;
signed long package2 = 0;
signed long package3 = 0;
signed long package4 = 0;
int gVal = 0;
float range;
float m = 0.97;
float k = 4.2;  //GET CONSTANTS
float b = 4.2;
int d = 0;
int numLoops = 1;
float v = 0;


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
	d = (int) getADC(chan);
	//m += d/((d+k)*numLoops);
	numLoops++;
	v = d*(5/1023);
	range = ((1/((m*v) + b))) - k;
	printf("adc = %d  |  1/(R+k) = %f  |  m = %f  |  range = %f\n\r", d, 1/(d+k), d/(d+k), range);
	return range;
}

/**
 * @brief Initialize the encoders with the desired settings.
 * @param chan Channel to initialize.
 *
 * @todo Make a function that can setup both encoder chips on the board.
 */
void encInit(int chan){

	DDRC |= 0x30; //0x00110000b  -- CS ENABLE

	chooseEnc(chan);  // slave select
	spiTransceive(CLR_CNTR);
	encSSHigh();
	chooseEnc(chan);
	spiTransceive(WRITE_MDR0);
	spiTransceive(QUADRX1|FREE_RUN|DISABLE_INDX|ASYNCH_INDX|FILTER_1);
	encSSHigh();
	chooseEnc(chan);
	spiTransceive(WRITE_MDR1);
	spiTransceive(NO_FLAGS | BYTE_2 | EN_CNTR);
	encSSHigh();
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
	spiTransceive(CLR_CNTR);
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
	encSSHigh();
	chooseEnc(chan); // assert SS for Encoder

	spiTransceive(READ_CNTR);
	count  = spiTransceive(0xff) << 8;
	count |= spiTransceive(0xff);

	encSSHigh(); //deassert encoders
	//count = (signed long) (package1 | package2 | package3 | package4); //creates a signed long that contains the results of all spiTransceives bitshifted
	//printf("count = %d\n\r", count);
	if(chan) count = -count; // accounts for difference in upper and lower encoders
	return count;
}
/*
 * slave select based on channel input
 * chan = 0 - lower link
 * chan = 1 - upper link
 */
void chooseEnc(int chan){  //slave selects based on channel input
	encSSHigh();
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

float encToDeg(int chan){

	float ticks = encCount(chan);
	if(!chan) return ticks/(48.0*172.0/(360.0*2.0));
	else return ticks/10.0;
	return 0;
}

