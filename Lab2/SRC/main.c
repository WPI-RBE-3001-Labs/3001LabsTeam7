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
unsigned int lowADC;
unsigned int highADC = 635;
float potAng=90;
int potAngInt;
unsigned long mV = 0;
unsigned long mVMax = 5000;
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
		  			for(int i=0;i<=1249;i++)
		  			{
		  			lowADC = getADC(2);
		  			// 396 is 90degrees - horizontal degrees and 240 is horizontal pot tick
		  			potAngInt =  ((lowADC - 240) * 90)/ 395 ;
		  			mV = lowADC * (mVMax/highADC) ;
		  			printf(" ADC %d, ",lowADC);
		  			printf("Angle %d, ", potAngInt);
		  			printf("mV %d", mV);
		  			_delay_ms(500);
		  			printf("\n\r");
		  			}
		  		}
		  	  }
}

int main(void)
{
	  //Enable printf() and setServo()
	  initRBELib();
	  debugUSARTInit(115200);
	  initSPI();
	  _delay_ms(3000);
	  setDAC(1, 4095);


	  //Set the baud rate of the UART

	  // printf uses a fair amount of memory to be included but makes serial printing much easier
	 // printf("PutCharDebug is complete \n\r");

	  //initADC(2);

	 // initTimer(0, 0, 0);


	  while(1)
	  {
		  //matLabDataCollect();
		 //lab1();
		  /*for(int i = 0; i < 4096; i++){
			  setDAC(0, i);
			  _delay_ms(100);
		  }
		  for(int j = 4095; j > 0; j--){
			  setDAC(0, j);
			  _delay_ms(100);
		  }*/

	  }


}
