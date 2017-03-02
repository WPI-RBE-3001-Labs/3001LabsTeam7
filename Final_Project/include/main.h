/*
 * main.h
 *
 *  Created on: Feb 27, 2017
 *      Author: coshea
 */

#ifndef INCLUDE_MAIN_H_
#define INCLUDE_MAIN_H_

#include "RBELib.h"
//For use of abs()
#include <stdlib.h>
#include "buttons.h"
#include "current.h"
#include "sensors.h"
#include "servo.h"

int inits(int in);

#define __POT 1
#define __OTHER 2
#define __USART 3

#endif /* INCLUDE_MAIN_H_ */
