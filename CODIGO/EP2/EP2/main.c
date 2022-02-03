/*
 * main.c
 *
 * Created: 2/3/2022 2:51:08 PM
 *  Author: Lenovo
 */ 
#define F_CPU 1000000
#include <xc.h>
#include <util/delay.h>

#define I      !(PIND & 0x1)
#define a      !(PIND & 1<<1)
#define b      !(PIND & 1<<2)
#define c      !(PIND & 1<<3)

#define M		1
#define SR		0
#define BR		3
#define A		2
#define BL		4

int main(void)
{
	/*PD0-PD3->ENTRADA DIGITAL CON PULL UP*/
	DDRD &=~(0xF);
	PORTD |= 0xF;
	/*PB0-PB4-> SALIDA DIGITAL*/
	DDRB |= 0x1F;
	
    while(1)
    {
        //I
		if(I){
			PORTB |= 1U<<BR;
			_delay_ms(100);
			
		}
		//a
		if(a){
			PORTB &=~ (1u<<SR);		//subida rapida
			PORTB &=~ (1U<<M);		//se apaga el rele
			PORTB |= 1U<<A;			//AVISO
			_delay_ms(200);			//DURACION DEL AVISO
			PORTB &=~ (1U<<A);
		}
		//b
		if(b){
			PORTB |= 1U<<M;			//enciende el rele
			PORTB &=~ (1U<<BR);		//apaga el descenso rapido
			PORTB |= 1U<<BL;		//descenso lento
			_delay_ms(100);
		}
		//c
		if(c){
			PORTB &=~ (1U<<BL);		//se apaga descenso lento
			PORTB |= 1u<<SR;		//subida rapida
			
		}
    }
}