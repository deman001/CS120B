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
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


enum ThreeLEDsSM{Start, firstLed, secondLed, thirdLed} state;
enum BlinkingLEDSM{Begin, bitThreeup, bitThreedown} lights;
enum CombineLEDsSM{First, Keep} cycle;
volatile unsigned char threeLEDs = 0x00;
volatile unsigned char blinkingLED = 0x00;
volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
unsigned char i;

void Tick() {
	//State actions for bits 0, 1, 2
	switch(state) {
		case(firstLed): //bit 0 = 1
			threeLEDs = 0x01;
			break;
		case(secondLed): //bit 1 = 1
			threeLEDs = 0x02;
			break;
		case(thirdLed): //bit 2 = 1
			threeLEDs = 0x04;
			break;
		default:
			break;
	}

	//State actions for bit 3
	switch(lights) {
		case(bitThreeup): //turning bit 3 on
			blinkingLED = 0x08;
			break;
		case(bitThreedown): //turning bit 3 off
			blinkingLED = 0x00;
			break;
	}

	//State transitions
	switch(state) {
		case(Start):
			state = firstLed;
			break;
		case(firstLed):
	}			

void TimerOn() {
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}

void TimerOff() {
	TCCR1B = 0x00;
}

void TimerISR() {
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect) {
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr == 0) {
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
	TimerSet(100);
	TimerOn();
	state = Start;
	lights = Begin;
	cycle = First;
	i = 0;
    while (1) {
	if(i % 10 == 0) {
		//FIRST SM
		Tick();

		//SECOND SM
		Tick1();

		//THIRD SM
		Tick2();
	}
	i++;
    }
    return 1;
}
