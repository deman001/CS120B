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
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00; 
    /* Insert your solution below */
	unsigned char tmp, cnt;
	int i;
    while (1) {
	cnt = 0x00;
	for (i = 1; i < 0x81; i = i * 2) {
		tmp = PINA & i;
		if (tmp > 0) {
			cnt++;
		}
	}
	for (i = 1; i < 0x81; i = i * 2) {
		tmp = PINB & i;
		if (tmp > 0) {
			cnt++;
		}
	}
	PORTC = cnt;
    }
    return 1;
}
