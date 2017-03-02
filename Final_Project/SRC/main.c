/* main.c
 *
 *  Created on: August 20, 2016
 *      Author: Joe st. Germain
 */
#include "main.h"

volatile unsigned long systemTime = 0;
volatile unsigned long timerCounter = 0;
volatile unsigned long intTime = 0;
volatile double timerCountVal = 9; //9 for ms system time

static int s = 0;
int b;

int upperAngle = 0;
int lowerAngle = 0;

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
	//updatePIDLink('L', angleToADCLow(lowerAngle));
	//updatePIDLink('H', angleToADCHigh(upperAngle));
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
			printf("b = %d\n\r", b);
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
		//initTimer(0,0,0);
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
	if(in) drop();
	else open(0);
}

void drop(){
	for(int i = 0; i < 5000; i++){
		home();
	}
	open(0);
}

void dropOtherSide(){
	for(int i = 0; i < 10000; i++){
		other();
	}
	open(0);
}

void home(){
	updatePIDLink('L', angleToADCLow(80));
	updatePIDLink('H', 740);
}

void other(){
	updatePIDLink('H', 780);
	updatePIDLink('L', 470);
}

void set1(){ //
	updatePIDLink('H', 710);
	updatePIDLink('L', 355);
}

void set2(){
	updatePIDLink('H', 400);
	updatePIDLink('L', 680);
}

void set3(){ //
	updatePIDLink('H', 385);
	updatePIDLink('L', 723);
}

