/*	Author: deman001
 *  Partner(s) Name: 
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
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00; 
    /* Insert your solution below */
	unsigned char tmp, fuel;
    while (1) {
	fuel = 0x40;
	tmp = ~PINA & 0x0F;
	if (tmp >= 0x01) {
		fuel = fuel | 0x20;
	}
	if (tmp >= 0x03) {
		fuel = fuel | 0x10;
	}
	if (tmp >= 0x05) {
		fuel = fuel | 0x08;
		fuel = fuel & 0xBF;
	}
	if (tmp >= 0x07) {
		fuel = fuel | 0x04;
	}
	if (tmp >= 0x0A) {
		fuel = fuel | 0x02;
	}
	if (tmp >= 0x0D) {
		fuel = fuel | 0x01;
	}
	PORTC = fuel;		
    }
    return 1;
}
