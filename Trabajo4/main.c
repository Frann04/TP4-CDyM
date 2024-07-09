/*
 * Trabajo4.c
 *
 * Created: 05/7/24 11:05:49 PM
 * Author : Frank
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define PWM_PERIOD 255	
#define PWM_OFF PORTB &=~(1<<PORTB5)
#define PWM_ON PORTB |=(1<<PORTB5)
#define PWM_DELTA 0		// Rojo
#include "timer.h"
#define F_CPU 16000000UL
#include "serialPort.h"
#define BR9600 (0x67)	// 0x67=103 configura BAUDRATE=9600@16MHz

volatile uint8_t flag_Blue = 1;
volatile uint8_t flag_Red = 1;
volatile uint8_t flag_Green = 1;
uint16_t intensidadRojo=0;

//comunicación con la ISR
volatile char RX_Buffer=0;
void PWM_soft_update(void);                                                                                                                                                                                                                                                                                                                                     


int main(void)
{
	DDRB |= (1<<PORTB1) | (1<<PORTB2) | (1<<PORTB5);	// Configuramos como salida.
	 SerialPort_Init(BR9600); 			// Inicializo formato 8N1 y BAUDRATE = 9600bps
	 SerialPort_TX_Enable();				// Activo el Transmisor del Puerto Serie
	 SerialPort_RX_Enable();				// Activo el Receptor del Puerto Serie
	 SerialPort_RX_Interrupt_Enable();	// Activo Interrupción de recepcion.

	cli();
    timer0_init();
	timer1_init();
	sei();
    while (1) 
    {
		if(flag_Green){
			// Mandar medida del potenciometro al color verde
			setGreen(0);
			setBlue(255);
			intensidadRojo=255;
		}
		
		if(flag_Blue){
			// Mandar medida del potenciometro al color azul
			setBlue(0);
			setGreen(255);
			intensidadRojo=255;
		}
		
		if(flag_Red){
			// Mandar medida del potenciometro al color rojo
			setBlue(255);
			setGreen(255);	
			intensidadRojo=0;
		}
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
	if(PWM_position<intensidadRojo){
		PWM_ON;
	}
	else{
		PWM_OFF;
	}
}


// Rutina de Servicio de Interrupción de Byte Recibido
ISR(USART_RX_vect) {
	RX_Buffer = UDR0; // La lectura de UDR0 borra el flag RXC

	if (RX_Buffer == 'B') { // Comprobar si el carácter recibido es 's' o 'S'
		SerialPort_Send_String("blueee"); // Pausar la transmisión si ya se había iniciado
			flag_Blue=1;
			flag_Red=0;
			flag_Green=0;
		}
	if (RX_Buffer == 'R') { // Comprobar si el carácter recibido es 's' o 'S'
				SerialPort_Send_String("red"); // Pausar la transmisión si ya se había iniciado

		flag_Blue=0;
		flag_Red=1;
		flag_Green=0;
	}
	if (RX_Buffer == 'G') { // Comprobar si el carácter recibido es 's' o 'S'
				SerialPort_Send_String("green"); // Pausar la transmisión si ya se había iniciado

		flag_Blue=0;
		flag_Red=0;
		flag_Green=1;
	}

}