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
//		  			lowADC = getADC(2);
//		  			// 396 is 90degrees - horizontal degrees and 240 is horizontal pot tick
//		  			potAngInt =  ((lowADC - 240) * 90)/ 395 ;
//		  			mV = lowADC * (mVMax/highADC) ;
//		  			printf(" ADC %d, ",lowADC);
//		  			printf("Angle %d, ", potAngInt);
//		  			printf("mV %d", mV);
//		  			_delay_ms(500);
//		  			printf("\n\r");
		  			}
		  		}
		  	  }
}

void initialize(int toggle) {
	initRBELib();
	debugUSARTInit(115200);
	initSPI();
}


void readADC(int channel){
	unsigned int highRange = 635;
	unsigned int lowRange = 240;
	float potAng= 90.00;
	int potAngInt;
	unsigned long mV = 0;
	unsigned long mVMax = 5000;

	inchar = getCharDebug();

	if (inchar == 'a')
	{
		for(int i=0;i<=1249;i++)
		{
		lowADC = getADC(channel);
		// 396 is 90degrees - horizontal degrees and 240 is horizontal pot tick
		potAngInt =  ((lowADC - lowRange) * potAng)/(highRange - lowRange) ;
		mV = lowADC * (mVMax/highRange);
		printf(" ADC %d, ",lowADC);
		printf("Angle %d, ", potAngInt);
		printf("mV %d", mV);
		_delay_ms(500);
		printf("\n\r");
		}
	}
}


int main(void)
{
initialize(0); //sets DAC mode



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
