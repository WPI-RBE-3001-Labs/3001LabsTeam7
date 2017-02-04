/*
 * pot.c

 *
 *  Created on: Feb 2, 2017
 *      Author: chris oshea coshea@wpi.edu
 */
#include "RBELib.h"

int potAngle(int pot){
return ((int) pot*0.322) - 90;
}

int potVolts(int pot){
return ((int)pot*4.887);
}
