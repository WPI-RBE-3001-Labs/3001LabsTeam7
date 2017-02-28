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
volatile double timerCountVal = 9; //9 for ms system time

static int s = 0;
int b;
int angle;

volatile long highLinkErr;
volatile long lowLinkErr;

volatile int highSetP;
volatile int lowSetP;

volatile int offSetlow = 380;
volatile double adctoanglelow = .257142857;

volatile int offSethigh = 380;
volatile double adctoanglehigh = .225;

int upperAngle = 0;
int lowerAngle = 0;

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
	updatePIDLink('L', angleToADCLow(lowerAngle));
	updatePIDLink('H', angleToADCHigh(upperAngle));
	timerCounter=0;
	systemTime++;
	intTime++;
	}
}

//*************************************************************************************************************************//
//                                       MAIN



int main(void)
{
	while(1){
	switch(inits(__OTHER)){

	case __POT:
		while(1){
			updatePIDLink('L', angleToADCLow(90));
			printf("low = %d  | high = %d\n\r", lowerPot(), upperPot());
		}
	break;

	case __OTHER:
		switch(s){
		case 0: //WAIT FOR START
			b = buttonToInt(readButtons());
			if(b == 0){
				printf("waiting for button press\n\r");
			}
			else{
				s = b;
				break;
			}
			break;
		case 1://homePos
			b = buttonToInt(readButtons());
			if(b == 0){
				updatePIDLink('L', angleToADCLow(80));
				updatePIDLink('H', 740);
			    printf("current = %d\n\r", readCurrent(0));
			    _delay_ms(300);
			}
			else{
				s = b;
				break;
			}
			break;
		case 2: //open gripper
			b = buttonToInt(readButtons());
			if(b == 0){
				open(0);
			}
			else{
				s = b;
				break;
			}
			break;
		case 3: //close gripper
			b = buttonToInt(readButtons());
			if(b == 0){
				close(0);
			}
			else{
				s = b;
				break;
			}
			break;
		case 4: // other side
			b = buttonToInt(readButtons());
			if(b == 0){
				updatePIDLink('H', angleToADCHigh(90));
				updatePIDLink('L', angleToADCLow(0));
			}
			else{
				s = b;
				break;
			}
			break;
		}
		b = 0;
	break;
	}
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
		initADC(3);
		stopMotors();
		setConst('H',20.0,0.01,0.1);
		setConst('L',20.0,0.01,0.1);
		//initTimer(0,0,0);
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
		setConst('H',30.0,0.01,0.1);
		setConst('L',30.0,0.01,0.1);
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
//		printf("H ");
//		printf(" HighADC: %d,Set: %d",getADC(3),setPoint);
//		printf(" PID: %ld, \n\r",pidNum);
		if (pidNum >= 0){
			setDAC(2, 0);
			setDAC(3, pidNum);
		}
		else{
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
//		printf("L ");
//		printf(" LowADC: %d,Set: %d",getADC(2),setPoint);
//		printf(" PID: %ld, \n\r",pidNum);
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

