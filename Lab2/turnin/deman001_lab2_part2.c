/*	Author: deman001
 *	Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;
	PORTA = 0x00;
	DDRB = 0x00;
	PORTB = 0x00;
	DDRC = 0x00;
	PORTC = 0x00;
		
	unsigned char tempA, cntavail;

    /* Insert your solution below */
    while (1) {
	tempA = PINA;
	tempA = tempA & 0x01;
	cntavail = 0x00;
	if (tempA == 0x01) {
		cntavail++;
	}
	tempA = 0x02 & PINA;
	if (tempA == 0x02) {
		cntavail++;
	}
	tempA = 0x04 & PINA;
	if (tempA == 0x04) {
		cntavail++;
	}
	tempA = 0x08 & PINA;
	if (tempA == 0x08) {
		cntavail++;
	}
	PORTC = 0x04 - cntavail;

    }
    return 1;
}
