/*
 * USART.c
 *
 *  Created on: Jan 26, 2015
 *      Author: joest
 */

#include "RBELib/RBELib.h"
#include <avr/io.h>

void debugUSARTInit(unsigned long baudrate) {

	//***we should check to see if the baudrate input is valid


	/*Set baud rate */
	UBRR1H = (unsigned char) (18432000 / (16 * baudrate) - 1) >> 8;
	UBRR1L = (unsigned char) (18432000 / (16 * baudrate) - 1);

	/*Enable receiver and transmitter */
	UCSR1B = (1 << RXEN1) | (1 << TXEN1);
	/* Set frame format: 8data, 2stop bit */
	UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);

}

void putCharDebug(char byteToSend) {
	/* Wait for empty transmit buffer */
	while (!( UCSR1A & (1 << UDRE1)));

	/* Put data into buffer, sends the data */
	UDR1 = byteToSend;
}

unsigned char getCharDebug(void) {
	/* Wait for data to be received */
	while (!(UCSR1A & (1 << RXC1)));
	/* Get and return received data from buffer */
	return UDR1;
}
