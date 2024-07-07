/*
 * Trabajo4.c
 *
 * Created: 05/7/24 11:05:49 PM
 * Author : Frank
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define PWM_PERIOD 100
#define PWM_OFF PORTB &=~(1<<PORTB5)
#define PWM_ON PORTB |=(1<<PORTB5)
#define PWM_DELTA 50
#include "timer.h"

void PWM_soft_update(void); 


int main(void)
{
	DDRB |= (1<<PORTB1) | (1<<PORTB2) | (1<<PORTB5);
	cli();
    timer0_init();
	timer1_init();
	sei();
    while (1) 
    {
    }
}

ISR (TIMER0_COMPA_vect)
{
	PWM_soft_update();
}

void PWM_soft_update(void){
	static uint16_t PWM_position=0;
	if (++PWM_position>=PWM_PERIOD){
		PWM_position=0;
	}
	if(PWM_position<PWM_DELTA){
		PWM_ON;
	}
	else{
		PWM_OFF;
	}
}
