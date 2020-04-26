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

enum States{Start, wait, inc, dec, reset} state;
unsigned char tmp;

void Tick(unsigned char temp) {
	switch(state) {
		case(Start):
			state = wait;
			break;
		case(wait):
			if (tmp == 0x00) {
				state = wait;
			}
			else if (tmp == 0x01) {
				if (temp < 0x09) {
					temp++;
				}
				state = inc;
			}
			else if (tmp == 0x02) {
				if (temp > 0x00) {
					temp--;
				}
				state = dec;
			}
			else if (tmp == 0x03) {
				state = reset;
			}
			break;
		case(inc):
			if (tmp == 0x00) {
				state = wait;
			}
			if (tmp == 0x01) {
				state = inc;
			}
			else if (tmp == 0x02) {
				if (temp > 0x00) {
					temp--;
				}
				state = dec;
			}
			else if (tmp == 0x03) {
				state = reset;
			}
			break;
		case(dec):
			if (tmp == 0x00) {
				state = wait;
			}
			else if (tmp == 0x01) {
				if (temp < 0x09) {
					temp++;
				}
				state = inc;
			}
			else if (tmp == 0x02) {
				state = dec;
			}
			else if (tmp == 0x03) {
				state = reset;
			}
			break;
		case(reset):
			if (tmp == 0x00) {
				state = wait;
			}
			else if (tmp == 0x01) {
				if (temp < 0x09) {
					temp++;
				}
				state = inc;
			}
			else if (tmp == 0x02) {
				if (temp > 0x00) {
					temp--;
				}
				state = dec;
			}
			else if (tmp == 0x03) {
				state = reset;
			}
			break;
		default:
			state = Start;
			break;
	}
	switch(state) {
		case(reset):
			temp = 0x00;
		default:
			break;
	}
	PORTC = temp;
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF;
	DDRC = 0xFF;	PORTC = 0x00;
    /* Insert your solution below */
	PORTC = 0x00;
	state = Start;
	tmp = ~PINA;
    while (1) {
	Tick(PORTC);
    }
    return 1;
}
