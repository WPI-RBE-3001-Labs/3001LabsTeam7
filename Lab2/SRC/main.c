/* main.c
 *
 *  Created on: August 20, 2016
 *      Author: Joe st. Germain
 */
#include "main.h"

static int state = 0;
unsigned int lowADC;
volatile unsigned long systemTime = 0;
volatile unsigned long timerCounter = 0;
volatile unsigned long intTime = 0;
volatile double timerCountVal = 1; //9 for ms system time

static int s = 0;
int b;
int angle;

volatile long highLinkErr;
volatile long lowLinkErr;

volatile int highSetP;
volatile int lowSetP;

volatile int offSetlow = 342;
volatile double adctoanglelow = .2107728337;

volatile int offSethigh = 140;
volatile double adctoanglehigh = .2189781022;

int angleToADCLow(int angle);

int angleToADCHigh(int angle);

void updatePIDLink(char link,int setPoint);
/*
 * Timer 0 ISR triggered on overflow
 */
ISR(TIMER0_OVF_vect)
{
	timerCounter++; //counts to make 1ms timer
	if (timerCounter >= timerCountVal)
	{
	updatePIDLink('L', angle);
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
	initADC(2);
	initADC(3);
	//stopMotors();
	setConst('H',20.0,0.01,0.1);
	setConst('L',20.0,0.01,0.1);
	angle = angleToADCHigh(90);
	//initTimer(0,0,0);
	while(1){
	updatePIDLink('H', angle);
//	switch(inits(__POT)){
//
//	case __POT:
//		//printf("PID\n\r");
//		//while(1){
//			//updatePIDLink('L', angleToADCLow(90));
//			//printf("low = %d  | high = %d\n\r", lowerPot(), upperPot());
//		//}
//	break;
//
//	case __OTHER:
//		switch(s){
//		case 0:
//			b = buttonToInt(readButtons());
//			if(b == 0){
//				printf("waiting for button press\n\r");
//			}
//			else{
//				s = b;
//				break;
//			}
//			break;
//		case 1://homePos
//			b = buttonToInt(readButtons());
//			if(b == 0){
//				updatePIDLink('L', angleToADCLow(45));
//				printf("current = %f\n\r", (double) readCurrent(0));
//			}
//			else{
//				s = b;
//				break;
//			}
//			break;
//		case 2: //open gripper
//			b = buttonToInt(readButtons());
//			if(b == 0){
//				open(0);
//			}
//			else{
//				s = b;
//				break;
//			}
//			break;
//		case 3: //close gripper
//			b = buttonToInt(readButtons());
//			if(b == 0){
//				close(0);
//			}
//			else{
//				s = b;
//				break;
//			}
//			break;
//		case 4: // 90 degrees
//			b = buttonToInt(readButtons());
//			if(b == 0){
//				updatePIDLink('L', angleToADCLow(90));
//			}
//			else{
//				s = b;
//				break;
//			}
//			break;
//		}
//		b = 0;
//	break;
//	}
	}
printf("End Main\n\r");
return 0;
}


/**************************************************************************************************************************************************************************/

int inits(int in){
	state = in;
	switch(state){
	case __POT:
		initRBELib();
		debugUSARTInit(115200);
		initSPI();
		initADC(2);
		//initADC(3);
		//stopMotors();
		//setConst('H',20.0,0.01,0.1);
		setConst('L',20.0,0.01,0.1);
		initTimer(0,0,0);
		return in;
		break;

	default:
		initRBELib();
		debugUSARTInit(115200);
		initSPI();
		initADC(2);
		initADC(3);
		initButtons();
		initCurrentSense(0);
		stopMotors();
		setConst('H',20.0,0.01,0.1);
		setConst('L',20.0,0.01,0.1);
		return in;
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
		volatile long pidNum = calcPID('H', setPoint, getADC(3));
		//printf("H \n\r");
		printf(" ADC: %d,Set: %d",getADC(3),setPoint);
		printf(" PID: %ld, \n\r",pidNum);
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
		volatile long pidNum = calcPID('L', setPoint, getADC(2));
		printf(" ADC: %d,Set: %d",getADC(2),setPoint);
		printf(" PID: %ld, \n\r",pidNum);
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
	double adclow =  ( angle / adctoanglelow) + offSetlow;

	return adclow;
}


// Takes in angle and returns adc value for higher link 0-180
int angleToADCHigh(int angle)
{
	//double offsetadclow = angle + offSetlow ;
	double adchigh =  ( angle / adctoanglehigh)+ offSethigh;

	return adchigh;
}

