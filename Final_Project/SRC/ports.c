/*
 * ports.c
 *
 *  Created on: Feb 5, 2017
 *      Author: coshea
 */
#include "RBELib.h"
#include "ports.h"
#include <stdarg.h>
#include <reg_structs.h>

/**
 * @brief Sets the direction (Input/Output) of the specified pins.
 *
 * @param port Port to set (A/B/C/D).
 * @param dir The Direction of the pin (INPUT or OUTPUT)
 * @param numPins The pins you want to set to this direction
 * @param ... Pins one after another
 *
 * @todo Create a way to set a port's pins to inputs or outputs.
 */
void setPinsDir(char port, int dir, int numPins, ...){

	va_list a;
	va_start(a, numPins);
	__8bitreg_t curPort;

	switch(port){

	case 'A':
		curPort = DDRAbits;
		break;


	case 'B':
		curPort = DDRBbits;
		break;

	case 'C':
		curPort = DDRCbits;
		break;


	case 'D':
		curPort = DDRDbits;
		break;

	default:
		printf("invalid port input");
		return;
		break;
	}


	for(int i = 0; i <= numPins; i++){

		int pin = va_arg(a, int);

		switch(pin){

		case PORT0:
			curPort._P0 = dir;
			break;

		case PORT1:
			curPort._P1 = dir;
			break;

		case PORT2:
			curPort._P2= dir;
			break;

		case PORT3:
			curPort._P3= dir;
			break;

		case PORT4:
			curPort._P4= dir;
			break;

		case PORT5:
			curPort._P5= dir;
			break;

		case PORT6:
			curPort._P6= dir;
			break;

		case PORT7:
			curPort._P7= dir;
			break;

		default:
			printf("invalid port input");
			return;
			break;
		}
	}
	va_end(a);
}

/**
 * @brief Gets the value on the specified pins of a port.
 *
 * @param port Port to read (A/B/C/D).
 * @param numPins The number of pins that you are reading.
 * @param ... The pins one after another.
 *
 * @return value The value of the specified pins on the port.
 *
 * @todo Create a way to read all given pins on a port.
 */
unsigned char getPinsVal(char port, int numPins, ...){

	va_list a;
	va_start(a, numPins);
	__8bitreg_t curPort;

	switch(port){

	case 'A':
		curPort = PINAbits;
		break;


	case 'B':
		curPort = PINBbits;
		break;

	case 'C':
		curPort = PINCbits;
		break;


	case 'D':
		curPort = PINDbits;
		break;

	default:
		curPort = PINAbits;
		//printf("invalid port input");
		break;

	}

	unsigned char out = 0x00;

	for(int i = 0; i <= numPins; i++){

		int pin = va_arg(a, int);

		switch(pin){

		case PORT0:
			out |= (0>>curPort._P0);
			break;

		case PORT1:
			out |= (1>>curPort._P1);
			break;

		case PORT2:
			out |= (2>>curPort._P2);
			break;

		case PORT3:
			out |= (3>>curPort._P3);
			break;

		case PORT4:
			out |= (4>>curPort._P4);
			break;

		case PORT5:
			out |= (5>>curPort._P5);
			break;

		case PORT6:
			out |= (6>>curPort._P6);
			break;

		case PORT7:
			out |= (7>>curPort._P7);
			break;

		default:
			printf("invalid port input");
			break;
		}
	}
	va_end(a);
	return out;
}

/**
 * @brief Sets the value on the specified pins of a port.
 *
 * @param port Port to set (A/B/C/D).
 * @param numPins The number of pins that you are setting.
 * @param val The value (high/low) to set the pin to.
 * @param ... The pins one after another.
 *
 * @todo Create a way to set all given pins on a port.
 */
void setPinsVal(char port, int val, int numPins, ...){
	va_list a;
	va_start(a, numPins);
	__8bitreg_t curPort;

	switch(port){

	case 'A':
		curPort = PINAbits;
	break;


	case 'B':
		curPort = PINBbits;
	break;

	case 'C':
		curPort = PINCbits;
	break;


	case 'D':
		curPort = PINDbits;
	break;

	default:
		printf("invalid port input");
		return;
		break;
	}


	for(int i = 0; i <= numPins; i++){

		int pin = va_arg(a, int);

		switch(pin){

		case PORT0:
			curPort._P0 = val;
			break;

		case PORT1:
			curPort._P1 = val;
			break;

		case PORT2:
			curPort._P2= val;
			break;

		case PORT3:
			curPort._P3= val;
			break;

		case PORT4:
			curPort._P4= val;
			break;

		case PORT5:
			curPort._P5= val;
			break;

		case PORT6:
			curPort._P6= val;
			break;

		case PORT7:
			curPort._P7= val;
			break;

		default:
			printf("invalid port input");
			return;
			break;
		}
	}
	va_end(a);
}

