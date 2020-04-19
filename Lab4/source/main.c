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

enum States{Start, OFF_R, ON_P, ON_R, OFF_P} state;

void Tick() {
	switch(state) {
		case(Start):
			state = OFF_R;
			break;
		case(OFF_R):
			state = PINA ? ON_P:OFF_R;
			break;
		case(ON_P):
			state = PINA ? ON_P:ON_R;
			break;
		case(ON_R):
			state = PINA ? OFF_P:ON_R;
			break;
		case(OFF_P):
			state = PINA ? OFF_P:OFF_R;
			break;
		default:
			state = Start;
			break;
	}
	switch(state) {
		case(OFF_R):
			PORTB = 0x01;
			break;
		case(ON_P):
			PORTB = 0x02;
			break;
		case(ON_R):
			PORTB = 0x02;
			break;
		case(OFF_P):
			PORTB = 0x01;
		default:
			break;
	}
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF;
	DDRB = 0xFF;	PORTB = 0x00;
    /* Insert your solution below */
	PORTB = 0x00;
	state = Start;
    while (1) {
	Tick();
    }
    return 1;
}
