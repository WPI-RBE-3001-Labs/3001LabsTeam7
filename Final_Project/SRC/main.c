/* main.c
 *
 *  Created on: August 20, 2016
 *      Author: Joe st. Germain
 */
#include "main.h"

volatile unsigned long systemTime = 0;
volatile unsigned long timerCounter = 0;
volatile unsigned long intTime = 0;
volatile double timerCountVal = 90; //90 for 10ms system time or 100Hz

static int s = 0;
int b;

int upperADC = 0;
int lowerADC = 0;

void initMain();

void sortMove(int in);

void drop();

void dropOtherSide();

void home();

void other();

int sort();

void sorting();

void set1();

void set2();

void set3();

/*
 * Timer 0 ISR triggered on overflow
 */
ISR(TIMER0_OVF_vect)
{
	timerCounter++; //counts to make 1ms timer
	if (timerCounter >= timerCountVal)
	{
	updatePIDLink('L', lowerADC);
	updatePIDLink('H', upperADC);   //PID runs in interrupt
	timerCounter=0;
	systemTime++;
	intTime++;
	}
}

//*************************************************************************************************************************//
//                                       MAIN



int main()
{
	initMain();
	while(1){
		switch(s){
		case 0: //WAIT FOR START
			b = buttonToInt(readButtons());
			if(b == 0){
				printf("waiting for button press\n\r");
			}
			else{
				s = b;
				initTimer(0,0,0);  // INITS TIMER
				break;
			}
			break;
		case 1://homePos
			b = buttonToInt(readButtons());
			if(b == 0){
				set1();
			}
			else{
				s = b;
				break;
			}
			break;
		case 2: //open gripper
			b = buttonToInt(readButtons());
			if(b == 0){
				set2();
			}
			else{
				s = b;
				break;
			}
			break;
		case 3: //close gripper
			b = buttonToInt(readButtons());
			if(b == 0){
				set3();
			}
			else{
				s = b;
				break;
			}
			break;
		case 4: // other side
			b = buttonToInt(readButtons());
			if(b == 0){
				home();
			}
			else{
				s = b;
				break;
			}
			break;
		}
	}
printf("End Main\n\r");
return 0;
}


/**************************************************************************************************************************************************************************/

void initMain(){
		initRBELib();
		debugUSARTInit(115200);
		initSPI();
		initADC(2);
		initADC(3);
		initButtons();
		stopMotors();
		setConst('H',20.0,0.01,0.1);
		setConst('L',20.0,0.01,0.1);
}

void sorting(){
	while(buttonToInt(readButtons())  == 0){}//WAITS for button press
	close(0);
	for(int i = 0; i < 3000; i++){
	other(); //bring to weighting position
	}
	int x = sort();
	printf("x = %d\n\r", x);
	_delay_ms(500);
	sortMove(x);
}

int sort(){
	int adc = getADC(2);
	for(int i = 0; i < 3000; i++){
	setDAC(1, 400); //values for determining weight
	setDAC(0, 1024);
	}
	int diff = getADC(2) - adc;
	if(diff > 10){
		printf("light\n\r");
		return 1; //light
	}
	printf("heavy\n\r");
	return 0; // heavy
}

void sortMove(int in){
	printf("%d\n\r", in);
	if(in) dropOtherSide();
	else open(0);
}

void drop(){
	for(int i = 0; i < 5000; i++){
		other();
	}
	open(0);
}

void dropOtherSide(){
	for(int i = 0; i < 10000; i++){
		home();
	}
	open(0);
}

void home(){
//	updatePIDLink('H', 740);
//	updatePIDLink('L', angleToADCLow(80));
	upperADC = 740;
	lowerADC = angleToADCLow(80);
}

void other(){
//	updatePIDLink('H', 780);
//	updatePIDLink('L', 470);
	upperADC = 780;
	lowerADC = 470;
}

void set1(){ //
//	updatePIDLink('H', 710);
//	updatePIDLink('L', 355);
	upperADC = 720;
	lowerADC = 355;
}

void set2(){
//	updatePIDLink('H', 400);
//	updatePIDLink('L', 680);
	upperADC = 480;
	lowerADC = 680;
}

void set3(){ //
//	updatePIDLink('H', 385);
//	updatePIDLink('L', 723);
	upperADC = 385;
	lowerADC = 723;
}

