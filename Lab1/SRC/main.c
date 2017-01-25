/* main.c
 *
 *  Created on: August 20, 2016
 *      Author: Joest
 */


#include "RBELib/RBELib.h" //RBELib
#include <avr/io.h> // AVR IO
#include "main.h"
#include "autoADC.h"
#include "globals.h"
#include "PWM.h"
#include "timeStamp.h"
#include "buttonInterrupts.h"
#include <stdlib.h>

//character for receiving serial data
char inchar;
int lowADC = 0;
int highADC=1023;


int main(void)
{
	  //Enable printf() and setServo()
	  initRBELib();

	  // Write the USARTDebug.c file using the function prototypes in the H file to enable the usart
	  //Set the baud rate of the UART
	  debugUSARTInit(115200);
	  DDRB = 0xFF;
	  // printf uses a fair amount of memory to be included but makes serial printing much easier
	  printf("PutCharDebug is complete \n\r");

	  	  while(1)
	  	  {
	  		PORTB =0xFF;
	  				_delay_ms(500);
	  				PORTB =0x00;
	  				_delay_ms(500);

	  		  //The get char debug function will return when a character is received
	  		  inchar = getCharDebug();
	  		  //Comment out this line once you have it working correctly
	  		 //printf("This line will print when a character is received from the serial connection \n\r");

	  		if (inchar == 'A')
	  		{
	  			//Switch which print statement is commented out when your ready for matlab data collection example
	  			//matlab will buffer all characters until \n\r
	  			printf("This will print if the character sent is an A \n\r");
	  	      //printf("%4d\t, %4d,\n\r", lowADC, highADC);
	  		}
	  	  }

}

