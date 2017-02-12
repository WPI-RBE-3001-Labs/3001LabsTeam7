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
 * VCC = VCC of port
 * BU_0 - PIN4
 * BU_1 - PIN5
 * BU_2 - PIN6
 * BU_3 - PIN7
 */

//sets up buttons as inputs to port B
void initButtons();

//returns a char of the button values
//only updates if there is a change in the button values
char readButtons();

#endif /* INCLUDE_BUTTONS_H_ */
