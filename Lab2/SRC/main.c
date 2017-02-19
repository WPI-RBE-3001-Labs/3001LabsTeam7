/* main.c
 *
 *  Created on: August 20, 2016
 *      Author: Joe st. Germain
 */


#include "RBELib.h"
//For use of abs()
#include <stdlib.h>
#include "buttons.h"
#include "current.h"
#include "Periph.h"
#include "sensors.h"
#include "PID.h"


unsigned int lowADC;
volatile unsigned long systemTime = 0;
volatile unsigned long timerCounter;
volatile unsigned long intTime;
volatile double timerCountVal = 9; //9 for ms system time

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

int angleToADCLow(int angle);
int angleToADCHigh(int angle);
void updatePIDLink(char link,int setPoint);
int inits(int in);


#define __PID 0
#define __ENC 1
#define __ACCEL 3
#define __POT 4
#define __OTHER 5

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

//                                                      PID ISR
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
//                                       MAIN



int main(void)
{
	while(1){
	switch(inits(__ENC)){

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

	case __OTHER:
		while(1){
			printf("lowerval = %d higherval = %d\n\r", getADC(2), getADC(3));
		}
	break;

	}
	}
printf("End Main\n\r");
return 0;
}


/**************************************************************************************************************************************************************************/

int inits(int in){
	static int state = __ACCEL;
	switch(state){
	case __ACCEL:
		initRBELib();
		debugUSARTInit(115200);
		initSPI();
		initTimer(0, 0, 0);
		return __ACCEL;
	break;

	case __ENC:
		initRBELib();
		debugUSARTInit(115200);
		initSPI();
		stopMotors();
		encInit(0);
		initTimer(0, 0, 0);
		resetEncCount(0);
		return __ENC;
	break;

	case __PID:
		initRBELib();
		debugUSARTInit(115200);
		initSPI();
		stopMotors();
		initButtons();
		initTimer(0, 0, 0);
		setConst('H',20.0,0.01,0.1);
		setConst('L',20.0,0.01,0.1);
		initADC(2);
		initADC(3);
		return __PID;
	break;

	default:
		return __OTHER;
	break;


	}

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
			setDAC(2, -pidNum);
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
