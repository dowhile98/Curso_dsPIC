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

/** 
  * @brief establer los valores de los pines
  */
void SET_Value(uint8_t value){
	/*borras el estado anterior*/
	PORTB &=~ (1U<<4 | 1U<<2  | 1U);
	PORTC &=~ (1U);
	/*estableces el nuevo valor*/
	//BIT0
	PORTB |= (value & 0x1)<<0;
	//BIT1
	PORTB |= (value>>1 & 1U)<<2;
	//BIT2
	PORTB |= (value>>2 & 1U)<<4;
	//BIT3
	PORTC |= (value>>3 & 1U)<<0;
}


int main(void)
{
	/*PB0,PD2,PB4 -> SALIDA*/
	DDRB |= 1U<<4  | 1U<<2 | 1U;
	/*PC0 -> SALIDA*/
	DDRC |= 1U<<0;
	/*PD0,PD2, PD4,PD6-> ENTRADA CON PULL UP*/
	DDRD &=~ (1U<<6 | 1U<<4 | 1U<<2 | 1U);
	PORTD |= 1U<<6 | 1U<<4 | 1U<<2 | 1U; //RESISTENCIAS PULL UP
	
    while(1)
    {
        //TODO:: Please write your application code 
		num = (PIND>>6 & 0x1)<<3 | (PIND>>4 & 0x1U)<<2 | (PIND>>2)<<1 | (PIND & 0x1U);  // PID & 0b00001111
		_delay_ms(200);
		switch(num){
			case 0:
				SET_Value(0x2);
				break;
			case 1:
				SET_Value(0xA);
				break;
			case 2:
				SET_Value(0xB);				//0b0011
				break;
			case 3:
				SET_Value(0x7);
				break;
			case 4:
				SET_Value(0x5);				//0b1100
				break;
			default:
				SET_Value(0);
		}
    }
}