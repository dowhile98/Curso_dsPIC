/*
 * main.c
 *
 * Created: 1/20/2022 9:30:00 AM
 *  Author: Lenovo
 */ 

#include <xc.h>
#include "LCD.h"
#include <avr/interrupt.h>
char txt[21];

uint8_t stateIt;
uint8_t count = 1;

int main(void)
{
	//PD3-> ENTRADA CON PULL UP
	DDRD &=~ (1U<<3);
	PORTD |= 1U<<3;		//PULL UP
	
	/*INT0 INIT*/
	cli();				//clear interrupt
	 // Configure PD2 as an input using the Data Direction Register D (DDRD)
	 DDRD &= ~(1U<<2);
	 // Enable the pull-up resistor on PD2 using the Port D
	 PORTD |= _BV(PORTD2);
	 EICRA |= 1U<<ISC01;			//falling edge sensitivity (INT0)
	 EIMSK |= 1U<<INT0;				//mask INT0
	 sei();							//set enable interrupt
	 //PB3 -> SALIDA
	 DDRB |= 1U<<3;
	 //PC2 -> SALIDA
	 DDRC |= 1U<<2;
	/*LCD Init*/
	LCD_Init();
	LCD_clear();
	sprintf(txt,"**QUINO B. JEFFRY**");
	LCD_printStr(txt);
	LCD_Set_Cursor(1, 0);
	sprintf(txt,"-------->AVR<--------");
	LCD_printStr(txt);
	LCD_Set_Cursor(2, 0);
	sprintf(txt,"ENERO - ");
	LCD_printStr(txt);
	LCD_printInt(2022);
	LCD_Set_Cursor(3, 0);
	LCD_cursor_on();
	LCD_cursor_blink();
	sprintf(txt,"ATMEGA328P");
	LCD_printStr(txt);
    while(1)
    {
        //TODO:: Please write your application code 
		if(stateIt){
			stateIt = 0;
			LCD_Set_Cursor(3, 0);
			sprintf(txt,"                     ");
			LCD_printStr(txt);
			LCD_Set_Cursor(3, 0);
			sprintf(txt,"INT0->%d",count);
			LCD_printStr(txt);
		}
		/*EFECTO LED*/
		if(!(PIND & 1U<<3)){
			_delay_ms(500);
			while(!(PIND & 1U<<3))  //hasta que se suelte el pulsador
			PINC |= 1u<<2;
		}
    }
}

/************************************************************************/
/*		Interrupt service routine			                            */
/************************************************************************/
ISR(INT0_vect){
	PINB = 1U<<3;
	stateIt = 1;
	count = count +1;
}

