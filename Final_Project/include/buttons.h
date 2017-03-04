/*
 * buttons.h

 *
 *  Created on: Feb 12, 2017
 *      Author: coshea
 */

#include "reg_structs.h"
#include "RBELib.h"

#ifndef INCLUDE_BUTTONS_H_
#define INCLUDE_BUTTONS_H_

/*
 * BUTTON LAYOUT
 * PORT C
 * VCC = VCC of port
 * BU_0 - PIN0
 * BU_1 - PIN2
 * BU_2 - PIN3
 * BU_3 - PIN6
 */

//sets up buttons as inputs to port B
void initButtons();

//returns a char of the button values
//only updates if there is a change in the button values
unsigned char readButtons();

/*
 * uses the buttons to choose different DAC values which drive the motors
 */
void setMotorVoltage();

//takes character of button pressed and returns it as an integer
int buttonToInt(unsigned char button);

#endif /* INCLUDE_BUTTONS_H_ */
