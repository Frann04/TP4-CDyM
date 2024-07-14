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
	OCR0A = 19;
	TIMSK0=0x02; // Habilito Interrupci�n por comparaci�n
	sei();    // Se activan las interrupciones
	

}

// Configuramos el timer con una frecuencia de 62500 Hz, mayor a los 50 Hz requeridos
// Inicialmente configuaramos el comparadoer en 0, led apagado
void timer1_init(){
	OCR1A = 0;							// Contador color azul
	OCR1B = 0;							// Contador color Verde
	TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10);	// Modo 5 fast no invertido
	TCCR1B =  (1<<WGM12) | (1<<CS10);		// prescaler 1
	
	// Reiniciar contador a cero 
	TCNT1 = 0;
}

void setBlue (uint16_t intensidad){
	OCR1A = intensidad;
}
void setGreen (uint16_t intensidad){
	OCR1B = intensidad;
}
