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

enum States{Start, gameRun, stopPress, wait,startGame} state;
enum Light{firstLed, secondLed, thirdLed, fourthLed} lights;
volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

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

void Tick() {
	switch(lights) {
                case(firstLed):
                        PORTB = 0x01;
                        break;
                case(secondLed):
                        PORTB = 0x02;
                        break;
                case(thirdLed):
                        PORTB = 0x04;
                        break;
                case(fourthLed):
                        PORTB = 0x02;
                default:
                        break;
        }
        switch(lights) {
                case(firstLed):
                        lights = secondLed;
                        break;
                case(secondLed):
                        lights = thirdLed;
                        break;
                case(thirdLed):
                        lights = fourthLed;
                        break;
                case(fourthLed):
                default:
                        lights = firstLed;
                        break;
        }
}

void Tick1() {
	switch(state) {
		case(Start):
			state = gameRun;
			break;
		case(gameRun):
			state = PINA ? stopPress: gameRun;
			break;
		case(stopPress):
			state = PINA ? stopPress: wait;
			break;
		case(wait):
			state = PINA ? startGame: wait;
			break;
		case(startGame):
			if (!PINA) {
				lights = firstLed;
				state = gameRun;
			}
			else { state = startGame;}
			break;
		default:
			state = Start;
			break;
	}
	switch(state) {
		case(gameRun):
			Tick();
			while(!TimerFlag);
			TimerFlag = 0;
			break;
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF;
	PORTB = 0x00;
    /* Insert your solution below */
	TimerSet(300);
	TimerOn();
	state = Start;
	lights = firstLed;
    while (1) {
	Tick1();
    }
    return 1;
}
