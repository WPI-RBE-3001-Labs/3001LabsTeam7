/*
 * autoADC.h
 *
 *  Created on: Jan 22, 2017
 *      Author: coshea
 */


#ifndef SRC_AUTOADC_H_
#define SRC_AUTOADC_H_

#include "main.h"

void initFreeRunADC(unsigned char channel);
void initTimedADC(unsigned char channel, float frequency, unsigned short int compare);

#endif /* SRC_AUTOADC_H_ */
