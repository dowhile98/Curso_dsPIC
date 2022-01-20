/*
 * main.c
 *
 * Created: 1/20/2022 1:35:56 PM
 *  Author: Lenovo
 */ 
#define  F_CPU 1000000UL
#include <xc.h>
#include "avr/interrupt.h"
#include "util/delay.h"

/*GLOBAL VARIABLES*/

uint8_t count = 0;

int main(void)
{
	cli();						//disable interrupts
	/*PD2, PD3 -> ENTRADA DIGITAL CON PULL UP*/
	DDRD &=~ (1U<<3 | 1U<<2);
	PORTD |= 1U<<3 | 1U<<2;		//PULL UP ENABLE
	//INT0
	EICRA |= 1U<<ISC01;			//falling edge sensitivity (INT0)
	EIMSK |= 1U<<INT0;			//mask INT0
	//INT1
	EICRA |= 1U<<ISC11;			//falling edge sensitivity (INT0)
	EIMSK |= 1U<<INT1;			//mask INT0
	/*PB0-PB7 -> DIGITAL OUTPUT*/
	DDRB = 0xFFU;				//SALIDA DIGITAL
	sei();						//habilita las interrupciones
    while(1)
    {
        //TODO:: Please write your application code 
		
    }
}

/************************************************************************/
/*								ISR                                     */
/************************************************************************/
/*ISR INT0*/
ISR(INT0_vect){
	count = count +1;
	PORTB = count;
}
/*ISR INT1*/
ISR(INT1_vect){
	count = count - 1;
	PORTB = count;
}