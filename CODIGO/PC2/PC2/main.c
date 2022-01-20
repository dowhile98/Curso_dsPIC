/*
 * main.c
 *
 * Created: 1/20/2022 2:48:36 PM
 *  Author: Lenovo
 */ 
#define F_CPU 1000000UL
#include <xc.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t startSem;

int main(void)
{
	cli();
	/*PD2 -> INPUT AND INTERRUPT*/
	DDRD &=~ (1U<<2);
	PORTD |=  1U<<2;		//PULL UP ENABLE
	//INT0
	EICRA |= 1U<<ISC01;			//falling edge sensitivity (INT0)
	EIMSK |= 1U<<INT0;			//mask INT0
	sei();
	/* PB0-PB7 Y PC0-PC3 DIGITAL OUTPUT*/
	DDRB = 0xFF;
	DDRC |= 0x0F;
    while(1)
    {
        //TODO:: Please write your application code 
		if(startSem){
			//secuencia 1
			//S1 -> VERDE, S2 -> ROJO, S3 -> VERDE , S4 -> ROJO
			PORTB = 0x0;
			PORTC &=~(0xF);
			PORTB |= 1U<<0; PORTB |= 1U<<5; PORTB |= 1U<<6; PORTC |= 1U<<3;
			_delay_ms(8000);
			//secuencia 2
			//S1 -> AMBAR, S2 -> ROJO, S3 -> AMBAR , S4 -> ROJO
			PORTB = 0x0;
			PORTC &=~(0xF);
			PORTB |= 1U<<1; PORTB |= 1U<<5; PORTB |= 1U<<7; PORTC |= 1U<<3;
			_delay_ms(8000);
			//secuencia 3
			//S1 -> ROJO, S2 -> VERDE, S3 -> ROJO , S4 -> VERDE
			PORTB = 0x0;
			PORTC &=~(0xF);
			PORTB |= 1U<<2; PORTB |= 1U<<3; PORTC |= 1U<<0; PORTC |= 1U<<1;
			_delay_ms(4000);
			//secuencia 4
			//S1 -> ROJO, S2 -> AMBAR, S3 -> ROJO , S4 -> AMBAR
			PORTB = 0x0;
			PORTC &=~(0xF);
			PORTB |= 1U<<2; PORTB |= 1U<<4; PORTC |= 1U<<0; PORTC |= 1U<<2;
			_delay_ms(4000);
		}
    }
}

/************************************************************************/
/*								ISR                                     */
/************************************************************************/
/*ISR INT0*/
ISR(INT0_vect){
	startSem = 1;
	EIMSK &=~ (1U<<INT0);			//mask INT0
	return;
}
	
