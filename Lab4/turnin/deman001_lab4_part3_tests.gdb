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

enum States{Start, wait, num, num_r, unlocked, lock} state;

void Tick() {
	switch(state) {
		case(Start):
			state = wait;
			break;
		case(wait):
			state = wait;
			if (PINA == 0x04) {
				state = num;
			}
			break;
		case(num):
			state = wait;
			if (PINA == 0x04) {
				state = num;
			}
			if (PINA == 0x00) {
				state = num_r;
			}
			break;
		case(num_r):
			state = wait;
			if (PINA == 0x00) {
				state = num_r;
			}
			if (PINA == 0x02) {
				state = unlocked;
			}
			break;
		case(unlocked):
			state = unlocked;
			if (PINA = 0x80) {
				state = lock;
			}
			break;
		case(lock):
			state = lock;
			if (PINA = 0x00) {
				state = wait;
			}
			break;
		default:
			state = Start;
			break;
	}
	switch(state) {
		case(wait):
			PORTB = 0x00;
			break;
		case(num):
			PORTB = 0x00;
			break;
		case(num_r):
			PORTB = 0x00;
			break;
		case(unlocked):
			PORTB = 0x01;
			break;
		case(lock):
			PORTB = 0x00;
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
