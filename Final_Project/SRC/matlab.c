/*
 * matlab.c
 *
 *  Created on: Feb 18, 2017
 *      Author: coshea
 */

#include "RBELib.h"
#include "matlab.h"
#include "USARTDebug.h"
#include "ADC.h"

void matLabDataCollect(void)
{
		  	  while(1)
		  	  {
		  			//matlab will buffer all characters until \n\r
		  			for(int i=0;i<=1249;i++)
		  			{
		  				printf("%d", (int) getADC(4));
		  				printf(",");
		  				_delay_us(1);
		  			}
		  			printf("\n\r");
		  	  }
}
