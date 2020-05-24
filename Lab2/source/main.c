/*   Author: deman001
     Partner(s) Name: 
     Lab Section:
     Assignment: Lab #  Exercise #
     Exercise Description: [optional - include for your own benefit]
     I acknowledge all content contained herein, excluding template or example
     code, is my own original work.
*/
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0x00;
	PORTB = 0xFF;
	DDRC = 0x00;	
	PORTC = 0xFF;
	DDRD = 0xFF;
	PORTD = 0x00;

	unsigned char tempA, tempC, tempD;
	tempA = 0x00;
	tempC = 0x00;
    /* Insert your solution below */
    while (1) {
	tempD = 0x00;
	tempA = PINA + PINB + PINC;
	if (tempA > 0x8C) {
		tempD = PORTD | 0x01;
	}
	tempA = tempA & 0xFC;
	tempD = tempD | tempA;
	if (PINA > PINC) {
		tempA = PINA - PINC;
	}
	else {
		tempA = PINC - PINA;
	}
	if (tempA > 0x50) {
		tempD = tempD | 0x02;
	}
	PORTD = tempD;
    }
    return 1;
}
