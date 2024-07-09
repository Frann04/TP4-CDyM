/*
 * timer.c
 *
 * Created: 06/7/24 6:40:15 PM
 *  Author: Frank
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

// Frecuencia de 100Hz
void timer0_init(){    // Configuración del timer
	TCCR0A=0x02; // Modo CTC
	TCCR0B = (1 << CS01) | (1 << CS00); // Prescaler de 64
	OCR0A = 25;
	TIMSK0=0x02; // Habilito Interrupción por comparación
	sei();    // Se activan las interrupciones
}

// Configuramos el timer con una frecuencia de 7812.5 Hz, mayor a los 50 Hz requeridos
// Inicialmente configuaramos el comparadoer en 0, led apagado
void timer1_init(){
	OCR1A = 255;							// Blue
	OCR1B = 255;							// Verde
	TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10);	// Modo 5 fast no invertido
	TCCR1B =  (1<<WGM12) | (1<<CS10);		// prescaler 8
	
	// Reiniciar contador a cero 
	TCNT1 = 0;
}

void setBlue (uint16_t intensidad){
	OCR1A = intensidad;
}
void setGreen (uint16_t intensidad){
	OCR1B = intensidad;
}
