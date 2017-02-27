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

/*
 * Timer 0 ISR triggered on overflow
 */
ISR(TIMER0_OVF_vect)
{
	timerCounter++; //counts to make 1ms timer
	if (timerCounter >= timerCountVal)
	{
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
	switch(inits(__POT)){

	case __POT:
		printf("calibrate potentiometers\n\r");
		while(1){
			printf("low = %d  | high = %d\n\r", lowerPot(), upperPot());
		}
	break;

	case __OTHER:
		switch(s){
		case 0:
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
				updatePIDLink('L', angleToADCLow(45));
				printf("current = %f\n\r", (double) readCurrent(0));
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
		case 4: // 90 degrees
			b = buttonToInt(readButtons());
			if(b == 0){
				updatePIDLink('L', angleToADCLow(90));
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

