/*
 * main.c
 *
 * Created: 2/3/2022 2:04:18 PM
 *  Author: Lenovo
 */ 
#define F_CPU 1000000UL

#include <stdio.h>
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void ExternalIT_Config(void);
/************************************************************************/
/*			VARIABLES                                                   */
/************************************************************************/


int main(void)
{
	cli();					//Deshabilita las interrupciones
	//configura INT0
	ExternalIT_Config();
	//PINES DE CONTROL DE MOTOR
	DDRC |= 1U<<1 | 1<<0;	//PC0-PC1 ->salida digital
	//interruptor
	DDRD &=~ (1U<<7);		//PD7 INPUT;
	PORTD |= 1U<<7;			//PULL UP
	//INDICADORES
	DDRB |= 1U<<6 | 1U<<5 | 1U<<4 | 1U<<4 | 1U<<3 | 1U<<2 | 1U<<1;
	
	/************************************************************************/
	/*					START                                               */
	/************************************************************************/
	while(1){
		if(!(PIND & 1U<<7)){
			_delay_ms(100);
			break;
		}
		_delay_ms(50);
	}
	/************************************************************************/
	sei();					//habilita las interrupciones
    while(1)
    {
        //TODO:: Please write your application code 
		//GIRTO IZQUIERDO
		PORTC |= 1U<<1;
		PORTC &=~ (1U);
		//GIRO DERECHA
		_delay_ms(4000);
		PORTC |= 1U;
		PORTC &=~ (1U<<1);
		_delay_ms(4000);
    }
}

/************************************************************************/
/*			DEFINICION DE FUNCIONES                                     */
/************************************************************************/
void ExternalIT_Config(void){
	// Configure PD2 as an input using the Data Direction Register D (DDRD)
	DDRD &= ~_BV(DDD2);
	// Enable the pull-up resistor on PD2 using the Port D
	PORTD |= _BV(PORTD2);
	EICRA |= 1U<<ISC01;			//falling edge sensitivity (INT0)
	EIMSK |= 1U<<INT0;			//mask INT0
	return;
}


/************************************************************************/
/*              ISR                                                     */
/************************************************************************/

ISR(INT0_vect){
	//ilimina los leds
	PORTB |= 0x3F<<1;
	_delay_ms(1000);
	PORTB &=~(0x3F<<1);
	
	return;
}