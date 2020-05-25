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


enum ThreeLEDsSM{firstLed, secondLed, thirdLed} state;
enum BlinkingLEDSM{bitThreeup, bitThreedown} lights;
enum CombineLEDsSM{Keep} cycle;
volatile unsigned char threeLEDs = 0x00;
volatile unsigned char blinkingLED = 0x00;
volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
unsigned int i;

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

	//State transitions
	switch(state) {
		case(firstLed):
			state = secondLed;
			break;
		case(secondLed):
			state = thirdLed;
			break;
		case(thirdLed):
			state = firstLed;
		default:
			break;
	}			
}

void Tick1() {
	//State actions for bit 3
	switch(lights) {
		case(bitThreedown):
			blinkingLED = 0x00;
			break;
		case(bitThreeup):
			blinkingLED = 0x08;
		default:
			break;
	}

	//State transitions for SM
	switch(lights) {
		case(bitThreedown):
			lights = bitThreeup;
			break;
		case(bitThreeup):
		default:
			lights = bitThreedown;
			break;
	}
}

void Tick2() {
	//State SM action combines the other two shared variables
	switch(cycle) {
		case(Keep):
			PORTB = threeLEDs + blinkingLED;
		default:
			break;
	}
	
	//State SM Transitions
	switch(cycle) {
		case(Keep):
			cycle = Keep;
		default:
			break;
	}
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
	state = firstLed;
	lights = bitThreedown;
	cycle = Keep;
    while (1) {
	//FIRST SM
	if (i % 3 == 0) {
		Tick();
	}

	//SECOND SM
	if (i % 10 == 0) {
		Tick1();
	}

	//THIRD SM
	Tick2();

	//Timer ticks every 1 second
	while(!TimerFlag);
	TimerFlag = 0;
	i++;
    }
    return 1;
}
