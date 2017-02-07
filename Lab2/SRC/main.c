/* main.c
 *
 *  Created on: August 20, 2016
 *      Author: Joe st. Germain
 */


#include "RBELib.h"
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

//*************************************************************************************************************************//
//                    LAB1


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
//*************************************************************************************************************************//
//                         LAB2A


//outputs two triangle waveforms based upon specified DAC channels
void triangle(int DAC1, int DAC2){

	for(int i = 0; i < 4096; i++){ //increments DAC SPIVal from 0 - 4095
		setDAC(DAC1, i);
		setDAC(DAC2, 4095 - i);
	}

	for(int j = 4095; j >= 0; j--){ //increments DAC SPIVal from 4095 - 0
		setDAC(DAC1, j);
		setDAC(DAC2, 4095 - j);
	}
}

//*************************************************************************************************************************//


int main(void)
{
initRBELib();
debugUSARTInit(115200);
initSPI();
_delay_ms(2000);
stopMotors();

_delay_ms(2000);

while(1){
	driveLink(1, 1);
	printf("fwd\n\r");
	_delay_ms(2000);
	driveLink(1, 0);
	printf("back\n\r");
	_delay_ms(2000);
}

//float current;
//while(1){
//	current = readCurrent(1);
//	printf("%f \n\r", (double) current);
//	_delay_ms(100);
//}





printf("End Main\n\r");

return 0;
}
