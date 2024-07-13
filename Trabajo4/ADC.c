/*
 * ADC.c
 *
 * Created: 26/03/2019 06:43:35 p.m.
 *  Author: ...
 */ 
#include "ADC.h"

void ADC_init()
{
	    
	    
	    ADMUX |= (1<<REFS0)  | (1<<MUX1) | (1<<MUX0); // Vref = AVcc, seleccionar ADC3
		ADCSRA |= (1<<ADPS0) | (1<<ADPS1)| (1<<ADEN); // Habilitar ADC
		//ADCSRA |= (1<<ADSC);
		DIDR0 = (1<<ADC3D);
	
	 
}

uint16_t ADC_GetData()
{
	
		// Iniciar conversión
		ADCSRA |= (1 << ADSC);
		// Esperar a que termine la conversión
		while (ADCSRA & (1 << ADSC));
		ADCSRA |= (1 << ADIF); // Reiniciar el flag

		// Leer ambos bytes
		//uint16_t adcValue = (ADCH << 8) | ADCL; // Combina ADCH y ADCL
		return ADC; // Retornar el valor combinado
	

   }
