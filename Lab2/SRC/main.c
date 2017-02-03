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

void triangle(int DAC1, int DAC2, int delayTime);
void initialize();

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

		  			}
		  		}
		  	  }
}

void initialize() {
	initRBELib();
	debugUSARTInit(115200);
	initSPI();
}

void triangle(int DAC1, int DAC2, int delayTime){
	 for(int i = 0; i < 4096; i++){
				  setDAC(DAC1, i);
				  setDAC(DAC2, 4095 - i);
				  _delay_ms(100);
			  }
			  for(int j = 4095; j >= 0; j--){
				  setDAC(DAC1, j);
				  setDAC(DAC2, 4095 - j);
				  _delay_ms(100);
			  }
}

int main(void)
{
initialize(); //inits libs, USART and DAC



	  while(1)
	  {
		  //matLabDataCollect();

	  }
}
