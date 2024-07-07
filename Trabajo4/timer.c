/*
 * timer.c
 *
 * Created: 06/7/24 6:40:15 PM
 *  Author: Frank
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

void timer0_init(){    // Configuraci�n del timer
	TCCR0A=0x02; // Modo CTC
	TCCR0B = (1 << CS01); // Prescaler de 8
	OCR0A = 2;
	TIMSK0=0x02; // Habilito Interrupci�n por comparaci�n
	sei();    // Se activan las interrupciones
	

}

// Configuramos el timer con una frecuencia de 7812.5 Hz, mayor a los 50 Hz requeridos
// Inicialmente configuaramos el comparadoer en 0, led apagado
void timer1_init(){
	OCR1A = 127;							// 
	OCR1B = 127;							// %50 de 255;
	TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10);	// Modo 5 fast no invertido
	TCCR1B =  (1<<WGM12) | (1<<CS11);		// prescaler 8
	
	// Reiniciar contador a cero 
	TCNT1 = 0;
}
