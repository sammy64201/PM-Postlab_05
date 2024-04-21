/*
 * Post_Lab_05.c
 *
 * Created: 4/18/2024 8:51:21 AM
 * Author : samue
 */ 


#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "PWM0/PWM0.h"
//#include "ADC/ADC.h"
//#include "PWM1/PWM1.h"
#include <avr/interrupt.h>

#define ADC_MAX 255
#define DUTY_MIN 0
#define DUTY_MAX 40

uint8_t dutyCycle = 0;
uint8_t dutyCycle1 = 0;

void initADC(void);


void setup(void){
	cli();
	UCSR0B = 0;
	initADC();
	sei();
	
}

uint8_t mapADCtoDC(uint8_t adcValue){
	return(uint8_t)(((float)adcValue / ADC_MAX) * (DUTY_MAX - DUTY_MIN) + DUTY_MIN);
}

int main(void)
{
	setup();
	
	//initPWM0FastA(no_invertido, 1024);
	//initPWM1Fast_16bit(no_invertido, 8);
	initPWM1FastA(no_invertido, 8);
	//initPWM2FastA(no_invertido, 32);
    while (1) 
    {
		//dutyCycle1 = A; //(7.84*ADCH)+2000;
		//dutyCycle = mapADCtoDC(ADCH);
		ADCSRA |= (1<<ADSC);
		
		//updateDutyCicleA(dutyCycle);
		//updateDutyCicleA2(dutyCycle);
		//updateDutyCycle1A(dutyCycle1);
		dutyCycle = ADCH;
		updateDutyCicleA1(dutyCycle);
    }
}

void initADC(void){

	ADMUX = 0; // INICIO EN 0
	// REFERENCIA AVCC = 5V
	ADMUX |= (1 << REFS0);
	ADMUX &= ~(1 << REFS1);
	// SELECCIONO EL ADC[5] = 0101
	ADMUX |= (1<<MUX2)|(1<<MUX0);
	
	// JUSTIFICACION A LA IZQUIERDA
	ADMUX |= (1 << ADLAR);
	
	ADCSRA = 0;
	
	// HABILITAR LA INTERRUPCION DEL ADC
	ADCSRA |= (1 << ADIE);
	
	// HABILITAMOS EL PRESCALER 128  FADC = 125 KHz
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	
	// HABILITAMOS EL ADC
	ADCSRA |= (1 << ADEN);
}

ISR(ADC_vect){
	//dutyCycle = ADCH;
	dutyCycle = ADCH;
	//valorADC2 = ADCH;
	
	//ADCSRA |=(1<<ADIF);
}

