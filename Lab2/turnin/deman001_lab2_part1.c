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
	PORTA = 0x00;
	DDRB = 0x00;
	PORTB = 0x00;
	
	unsigned char tempA, tempB;

    /* Insert your solution below */
    while (1) {
	tempA = 0x03 & PINA;
	if (tempA == 0x01) {
		tempB = 0x01;
	}
	else { tempB = 0x00; }
	PORTB = tempB;
    }
    return 1;
}
