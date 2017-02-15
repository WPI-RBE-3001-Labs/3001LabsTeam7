/* main.c
 *
 *  Created on: August 20, 2016
 *      Author: Joe st. Germain
 */


#include "RBELib.h"
#include "buttons.h"
#include "current.h"
//For use of abs()
#include <stdlib.h>
#include "Periph.h"

//character for receiving serial data
char inchar;
unsigned int lowADC;
volatile unsigned long systemTime = 0;
volatile unsigned long timerCounter;
volatile unsigned long intTime;
volatile double timerCountVal = 9; //9 for ms system time
float current = 0;
int encCheck = FALSE;

void triangle(int DAC1, int DAC2);
void toggleArm(int link, int time);
void currentSense(int motor);



/*
 * Timer 0 ISR triggered on overflow
 */
ISR(TIMER0_OVF_vect)
{
	timerCounter++;
	//counts to make 10ms timer
	if (timerCounter >= timerCountVal)
	{
	encCheck = TRUE;
	//Port C pin 0 flip for prelab part 8
	//PORTC ^= (1 << 0);
	timerCounter=0;
	systemTime++;
	intTime++;
	}
}


//*************************************************************************************************************************//
//                                       MAIN



int main(void)
{
initRBELib();
debugUSARTInit(115200);
initSPI();
stopMotors();
encInit(0);
initButtons();
initTimer(0, 0, 0);
resetEncCount(0);

while(1){
	setMotorVoltage();
	if(encCheck){
		encCount(0);
		encCheck = FALSE;
		//resetEncCount(0);
	}
}



printf("End Main\n\r");
return 0;
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
//                         LAB2
void lab2(int x){
	switch(x){

	case 0: //triangle wave
		while(1){
		triangle(0,1);
		}
	break;

	case 1: //current sense
		while(1){
			toggleArm(0, 250);
			lab2(1);
		}
	break;

	case 2: //PID
		initSPI();

	break;

	case 3: //armAngle
		initSPI();

	break;
	}
}

//outputs two triangle waveforms (offset by 1/2 their period) based upon specified DAC channels
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

void toggleArm(int link, int time){
		driveLink(link, 1);
		_delay_ms(time);
		driveLink(link, 0);
		_delay_ms(time);
}

void currentSense(int motor){
	//while(1){
		current = readCurrent(motor);
		printf("Current(mA) = %f \n\r", (double) current);
		//_delay_ms(100);
	//}
}
