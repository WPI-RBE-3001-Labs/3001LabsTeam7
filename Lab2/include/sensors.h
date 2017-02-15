/*
 * sensors.h
 *
 *  Created on: Feb 15, 2017
 *      Author: coshea
 */

#ifndef INCLUDE_SENSORS_H_
#define INCLUDE_SENSORS_H_

int EncoderCounts( int __chan );
//Outputs the number of encoder pulses received since the last sample time.
//If __chan = 0, the function returns the number of counts for motor channel 0, if __chan = 1, the
//function returns the number of counts for motor channel 1
//The function must return a value of ‐1 in an invalid channel is requested

int GetAccelerationH48C ( int __axis );
//Reads 12‐bit data from the H48C accelerometer module.
//__axis refers to the selected axis: x‐axis (__axis = 0), y‐axis (__axis = 1) or z‐axis (__axis = 2)

#endif /* INCLUDE_SENSORS_H_ */
