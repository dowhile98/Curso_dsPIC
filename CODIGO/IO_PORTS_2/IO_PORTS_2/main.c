/*
 * main.c
 *
 * Created: 1/19/2022 11:30:20 AM
 *  Author: Lenovo
 */ 
#define 	F_CPU   16000000UL
#include <xc.h>
#include <util/delay.h>
uint8_t num;

int main(void)
{
	/*PB0,PD2,PB4 -> SALIDA*/
	DDRB |= 1U<<3  | 1U<<2 | 1U;
	/*PC0 -> SALIDA*/
	DDRC |= 1U<<0;
	/*PD0,PD2, PD4,PD6-> ENTRADA CON PULL UP*/
	DDRD &=~ (1U<<6 | 1U<<4 | 1U<<2 | 1U);
	PORTD |= 1U<<6 | 1U<<4 | 1U<<2 | 1U; //RESISTENCIAS PULL UP
	
    while(1)
    {
        //TODO:: Please write your application code 
		num = PIND  & 0x0F;  // PID & 0b00001111
		_delay_ms(200);
		switch(num){
			case 0:
				PORTB |= 0xF;
				br	eak;
			case 0xF:
				PORTB &=~ (1U<<3 | 1U<<2 | 1U<<1 | 1U);
				PORTB |= 0xA;				//0b1010
				break;
			case 2:
				PORTB &=~ (1U<<3 | 1U<<2 | 1U<<1 | 1U);
				PORTB |= 0x3;				//0b0011
				break;
			case 5:
				PORTB &=~ (1U<<3 | 1U<<2 | 1U<<1 | 1U);
				PORTB |= 0x1;
				break;
			case 6:
				PORTB &=~ (1U<<3 | 1U<<2 | 1U<<1 | 1U);
				PORTB |= 0xC;				//0b1100
				break;
			default:
				PORTB &=~ (1U<<3 | 1U<<2 | 1U<<1 | 1U);
		}
    }
}