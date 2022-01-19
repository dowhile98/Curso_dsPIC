/*
 * main.c
 *
 * Created: 1/19/2022 10:23:00 AM
 *  Author: Lenovo
 */ 

#define 	F_CPU	16000000UL //16MHZ

#include <xc.h>		//Solo cuando trabajas con el compilador XC8
#include <avr/io.h>	//para manejo de puertos
#include <util/delay.h>

int main(void)
{
	/*PB5 -> SALIDA DIGITAL*/
	DDRB &=~ (1U<<0);
	DDRB |= 1U<<DDB5;
	/*PD0 -> ENTRADA DIGITAL*/
	DDRD &=~ (1U);
    while(1)
    {
        //TODO:: Please write your application code 
		/*if(PIND & 1U<<0){
			PORTB |= 1U<<5;
		}else{
			PORTB &=~ 1U<<5;
		}*/
		/*toggle led*/
		/*
		PORTB ^= 1U<<5;
		_delay_ms(50);*/
		PINB |= 1u<<5;
		_delay_ms(50);
    }
}