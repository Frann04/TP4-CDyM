/*
 * ADC.h
 *
 * Created: 12/7/2024 17:17:15
 *  Author: Barcala
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <util/delay.h>



void ADC_init();
uint16_t ADC_GetData(void);

#endif /* ADC_H_ */