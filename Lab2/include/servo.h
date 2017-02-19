/*
 * servo.h
 *
 *  Created on: Feb 19, 2017
 *      Author: coshea
 */

#ifndef INCLUDE_SERVO_H_
#define INCLUDE_SERVO_H_

#define HIGHVAL 140
#define LOWVAL 0

/*
 * closes the servo on specified channel
 */
void close(int chan);

/*
 * opens the servo on specified channel
 */
void open(int chan);


#endif /* INCLUDE_SERVO_H_ */
