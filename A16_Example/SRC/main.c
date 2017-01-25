/* main.c
 *
 *  Created on: August 20, 2016
 *      Author: Joest
 */


#include "RBELib/RBELib.h"
//For use of abs()
#include <stdlib.h>

//character for receiving serial data
char inchar;
int lowADC = 0;
int highADC=1023;


int main(void) {
	initRBELib(); //Setup printf() and setServo()
	debugUSARTInit(115200); //Initialize UART
	DDRB = 0xFF; //Set Port as output
	while (1) {
		PORTB = 0xFF; //Turn port on
		_delay_ms(500); //Delay .5 sec
		PORTB = 0x00; //Turn port off
		_delay_ms(500); //Delay .5 sec
		printf("Hello\n\r"); //Print “Hello”
	}
	return 0;
}

