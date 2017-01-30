/* main.c
 *
 *  Created on: August 20, 2016
 *      Author: Joe st. Germain
 */


#include "RBELib/RBELib.h"
//For use of abs()
#include <stdlib.h>


//character for receiving serial data
char inchar;
unsigned long lowADC = 0;
unsigned long highADC = 0;
float pot1Ang=0;
unsigned long potAngInt;
float mV=0;
volatile unsigned long systemTime = 0;
volatile unsigned long timerCounter;
volatile unsigned long intTime;
volatile double timerCountVal = 9; //9 for ms system time

/*
 * Timer 0 ISR triggered on overflow
 */
ISR(TIMER0_OVF_vect)
{
	timerCounter++;
	//counts to make 1ms timer
	if (timerCounter >=timerCountVal)
	{
	//Port C pin 0 flip for prelab part 8
	//PORTC ^= (1 << 0);
	timerCounter=0;
	systemTime++;
	intTime++;
	}

}

// Part 3 Matlab data collecting
//Functional
void matLabDataCollect(void)
{
		  	  while(1)
		  	  {
		  		  //The get char debug function will return when a character is received
		  		  inchar = getCharDebug();
		  		  //Comment out this line once you have it working correctly
		  		 //printf("This line will print when a character is received from the serial connection \n\r");

		  		if (inchar == 'A')
		  		{
		  			//Switch which print statement is commented out when your ready for matlab data collection example
		  			//matlab will buffer all characters until \n\r
		  			//printf("This will print if the character sent is an A \n\r");
		  			for(int i=0;i<=1249;i++)
		  			{
		  			lowADC = getADC(0);
		  			printf("%d",lowADC);
		  			printf(",");
		  			_delay_us(1);
		  			}
		  	    printf("\n\r");
		  		}
		  	  }
}

int main(void)
{
	  //Enable printf() and setServo()
	  initRBELib();

	  // Write the USARTDebug.c file using the function prototypes in the H file to enable the usart
	  //Set the baud rate of the UART
	  debugUSARTInit(115200);
	  // printf uses a fair amount of memory to be included but makes serial printing much easier
	  printf("PutCharDebug is complete \n\r");

	  initADC(0);
	  initTimer(0, 0, 0);


	  while(1)
	  {
		// matLabDataCollect();
		  //lab1();
	  }

}
