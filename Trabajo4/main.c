/*
 * Trabajo4.c
 *
 * Created: 05/7/24 11:05:49 PM
 * Author : Frank
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#define PWM_PERIOD 255
#define PWM_OFF PORTB &=~(1<<PORTB5)
#define PWM_ON PORTB |=(1<<PORTB5)
#define PWM_DELTA 0		// Rojo
#include "timer.h"
#define F_CPU 16000000UL
#include "serialPort.h"
#define BR9600 (0x67)	// 0x67=103 configura BAUDRATE=9600@16MHz
#include "ADC.h"

volatile uint8_t flag_Blue = 0;
volatile uint8_t flag_Red = 0;
volatile uint8_t flag_Green = 0;
uint16_t intensidadRojo=0;
 uint16_t ext_adc;
  uint16_t intensidad;

//comunicación con la ISR
volatile char RX_Buffer=0;
void PWM_soft_update(void);   
void print_adc_value(uint16_t value);                                                                                                                                                                                                                                                                                                                              


int main(void)
{
    // Configuramos como salida.
    DDRB |= (1<<PORTB1) | (1<<PORTB2) | (1<<PORTB5);	
    SerialPort_Init(BR9600);  // Inicializo formato 8N1 y BAUDRATE = 9600bps
    SerialPort_TX_Enable();     // Activo el Transmisor del Puerto Serie
    SerialPort_RX_Enable();     // Activo el Receptor del Puerto Serie
    SerialPort_RX_Interrupt_Enable(); // Activo Interrupción de recepcion.

    cli();
    timer0_init();
    timer1_init();
    ADC_init();
    sei();
	
    while (1) 
    {
		if(flag_Green){
			// Mandar medida del potenciometro al color verde
			ext_adc = ADC_GetData(); // Leer del potenciómetro
			intensidad = ext_adc * (0.2490234) ;
			// print_adc_value(intensidad); Imprimir valor
			setGreen(intensidad);
		}
		
		if(flag_Blue){
			// Mandar medida del potenciometro al color azul
			ext_adc = ADC_GetData(); // Leer del potenciómetro
			intensidad = ext_adc * (0.2490234) ;
			// print_adc_value(intensidad); Imprimir valor
			setBlue(intensidad);
		}
		
		if(flag_Red){
			// Mandar medida del potenciometro al color rojo
			ext_adc = ADC_GetData(); // Leer del potenciómetro
			intensidad = ext_adc * (0.2490234) ;
			// print_adc_value(intensidad); Imprimir valor
			intensidadRojo=intensidad;
		}
    }
}

ISR (TIMER0_COMPA_vect)
{
    PWM_soft_update();
}

void PWM_soft_update(void) {
    static uint16_t PWM_position = 0;
    if (++PWM_position >= PWM_PERIOD) {
        PWM_position = 0;
    }
    if (PWM_position < intensidadRojo) {
        PWM_ON; // Encender el LED
    } else {
        PWM_OFF; // Apagar el LED
    }
}


void print_adc_value(uint16_t value) {
	char buffer[10]; // Buffer para almacenar la cadena
	sprintf(buffer, "ADC: %u\n\r", value); // Convertir a cadena
	SerialPort_Send_String(buffer); // Enviar la cadena al puerto serie
}

// Rutina de Servicio de Interrupción de Byte Recibido
ISR(USART_RX_vect) {
	RX_Buffer = UDR0; // La lectura de UDR0 borra el flag RXC

	if (RX_Buffer == 'B') { // Comprobar si el carácter recibido es 'B' para modificar el color azul
		flag_Blue=1;
		flag_Red=0;
		flag_Green=0;
	}
	if (RX_Buffer == 'R') { // Comprobar si el carácter recibido es 'R' para modificar el color rojo
		flag_Blue=0;
		flag_Red=1;
		flag_Green=0;
	}
	if (RX_Buffer == 'G') { // Comprobar si el carácter recibido es 'G' para modificar el color verde
		flag_Blue=0;
		flag_Red=0;
		flag_Green=1;
	}

}