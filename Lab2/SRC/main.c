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
#include "sensors.h"
#include "PID.h"

//character for receiving serial data
char inchar;
unsigned int lowADC;
volatile unsigned long systemTime = 0;
volatile unsigned long timerCounter;
volatile unsigned long intTime;
volatile double timerCountVal = 9; //9 for ms system time
float current = 0;
int encCheck = FALSE;
int accelCheck = FALSE;
int potCheck = FALSE;
volatile long highLinkErr;
volatile long lowLinkErr;

volatile int highSetP;
volatile int lowSetP;

volatile int offSetlow = 775;
volatile double adctoanglelow = 3.66;

volatile int offSethigh = 247;
volatile double adctoanglehigh = 4.16;

void triangle(int DAC1, int DAC2);
void toggleArm(int link, int time);
void currentSense(int motor);
int angleToADCLow(int angle);
int angleToADCHigh(int angle);
void updatePIDLink(char link,int setPoint);

#define __ACCEL 3
#define __ENC 1
#define __PID 0
#define __POT 4

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
	accelCheck = TRUE;
	potCheck = TRUE;
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
	//initADC(2);
	//initADC(3);
	initButtons();
	initTimer(0, 0, 0);
	resetEncCount(0);
	setConst('H',20.0,0.01,0.1);
	setConst('L',20.0,0.01,0.1);

	static int state = __ENC;
	while(1){
	switch(state){

	case __PID:
		while(1){

				  //PID run in interrupt
				  lowSetP=angleToADCLow(0);
				  highSetP=angleToADCHigh(90);

				  printf("adcL: %d\n\r",lowSetP);
				  printf("adcH: %d \n\r",highSetP);
				 // _delay_ms(2000);


				  lowSetP=angleToADCLow(90);
				  highSetP=angleToADCHigh(0);
				  printf("adcL: %d\n\r",lowSetP);
				  printf("adcH: %d\n\r",highSetP);

				 // _delay_ms(2000);

			  }
		break;

	case __ENC:

		while(1){
				setMotorVoltage();
				if(encCheck){
					printf("encCount = %d\n\r", (int) encCount(0));
					encCheck = FALSE;
					resetEncCount(0);
				}
			}
		break;

	case __ACCEL:
		while(1){
			if(accelCheck){
				printf("x = %d  y = %d  z = %d\n\r", getAccel(0), getAccel(1), getAccel(2));
				//printf("y = %d\n\r", getAccel(1));
				//printf("z = %d\n\r", getAccel(2));
				accelCheck = FALSE;
				}
		}
		break;

	case __POT:
		while(1){
			if(potCheck){
				//idk some pot stuff !!! dont forget to init ADCs
				potCheck = FALSE;
			}
		}
	break;

	}}

//while(1){
//	printf("adc2val = %d\n\r", getADC(2));
//	printf("adc3val = %d\n\r", getADC(3));
//
//}
//


printf("End Main\n\r");
return 0;
}




void updatePIDLink(char link,int setPoint)
{
switch(link){
case 'H':
	//1000 to 250
	if (FALSE){
		setDAC(2, 0);
		setDAC(3, 0);
	}
	else{
		long pidNum = calcPID('H', setPoint, getADC(3));
		//printf("H \n\r");
		printf(" ADC: %d,Set: %d",getADC(3),setPoint);
		printf(" PId: %ld, \n\r",pidNum);
		if (pidNum >= 0){
			printf("pidNum>=0");
			setDAC(2, 0);
			setDAC(3, pidNum);
		}
		else{
			printf("else");
			setDAC(2, 0 );
			setDAC(3, 0);
		}
	}
	break;
case 'L':
	//1000 to 250
	if (FALSE){
		setDAC(0, 0);
		setDAC(1, 0);
	}
	else{
		long pidNum = calcPID('L', setPoint, getADC(2));
		//printf("L \n\r");
		//printf(" ADC: %d,Set: %d",getADC(2),setPoint);
		//printf(" PId: %ld, \n\r",pidNum);
		if (pidNum >= 0)		{
			setDAC(0, pidNum);
			setDAC(1, 0);
		}
		else{
			setDAC(0, 0);
			setDAC(1, -pidNum);
		}
	}
	break;
	}
}

int angleToADCLow(int angle)
{
	//double offsetadclow = angle + offSetlow ;
	double adclow =  ( angle * adctoanglelow)+ offSetlow;

	return adclow;
}

// Takes in angle and returns adc value for higher link 0-180
int angleToADCHigh(int angle)
{
	//double offsetadclow = angle + offSetlow ;
	double adchigh =  ( angle * adctoanglehigh)+ offSethigh;

	return adchigh;
}


//ISR(TIMER0_OVF_vect)
//{
//	timerCounter++;
//	//counts to make 1ms timer
//	if (timerCounter >=timerCountVal)
//	{
//	//Port C pin 0 flip for prelab part 8
//	//PORTC ^= (1 << 0);
//	timerCounter=0;
//	systemTime++;
//	intTime++;
//	// Sets PID at 100hz
//	if (intTime>=10)
//	{
//		updatePIDLink('H',calcPID('H',90,getADC(2)));
//		updatePIDLink('L',calcPID('L',90,getADC(3)));
//		updatePIDLink('H',highSetP);
//		updatePIDLink('L',lowSetP);
//
//	}
//	}
//
//}





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
