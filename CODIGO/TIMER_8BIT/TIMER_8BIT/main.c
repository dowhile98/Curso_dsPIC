/*
 * main.c
 *
 * Created: 2/3/2022 9:55:21 AM
 *  Author: Lenovo
 */ 

#include <xc.h>
#include "LCD.h"
#include <avr/interrupt.h>
#include "UART.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char txt[21];
uint8_t bufferRx[20];
uint16_t RxCount;
uint8_t byte;
uint8_t duty;

#define DUTY(ARR,_duty)       (uint8_t)(((float)ARR/100)*_duty)

/************************************************************************/
/*                                                                      */
/************************************************************************/
void TIMER0_CTC_Mode(void);
void Timer0Config_FastPWM7(void);
int main(void)
{
	/*lcd init*/
	LCD_Init();
	LCD_clear();
	sprintf(txt,"**ATMEGA32P**");
	LCD_printStr(txt);
	LCD_Set_Cursor(1, 0);
	sprintf(txt,"------>TIMER<------");
	LCD_printStr(txt);
	
	/*timer config*/
	/*TIMER0_CTC_Mode();
	//PD6 
	DDRD |= 1U<<6;
	sei();*/
	Timer0Config_FastPWM7();
	/*UART INIT*/
	UART_Config(DOUBLE_SPEED,9600);
	sei();
    while(1)
    {
        //TODO:: Please write your application code 
		LCD_Set_Cursor(2, 0);
		sprintf(txt,"Duty->             ");
		LCD_printStr(txt);
		LCD_Set_Cursor(2, 0);
		sprintf(txt,"Duty->%d",duty);
		LCD_printStr(txt);
		_delay_ms(100);
    }
}

void TIMER0_CTC_Mode(void){
	/*seleccionar el prescaler*/
	//8MHZ
	TCCR0B |= 1U<<CS02 | 1U<<CS00;		//N = 1024
	/*Selecionar el modo de operacion*/
	TCCR0A &=~ (1U<<WGM00);
	TCCR0A |= 1U<<WGM01;
	TCCR0B &=~ (1U<<WGM02);				//MODO CTC
	/*ESTABLECER OCR0A*/
	OCR0A = 97-1;					//50ms overflog
	/*configurar la interrupcion*/
	TIMSK0 |= 1U<<OCIE0A;				//genera una interrupcino cuando OCR0A == TCNT
	TIFR0 |= 1U<<OCF0A;					//CLEAR
	
}

void Timer0Config_FastPWM7(void){
	DDRD |= _BV(DDD5);
	/*se clock sources*/
	TCCR0B |= 1U<<CS01 ;	//N = 8
	/*select mode*/
	TCCR0A |= 1U<<WGM01 | 1U<<WGM00;		//fast PWM (mode 7)
	TCCR0B |= 1U<<WGM02;
	TCCR0A |= 1U<<COM0B1;					//Clear OC0A on Compare Match, set OC0A at BOTTOM
	OCR0A = 62;								//2khz PWM
	/*set duty*/
	OCR0B = DUTY(62,duty);
}

ISR(TIMER0_COMPA_vect){
	TIFR0 |= 1U<<OCF0A;	
	PORTD ^= 1U<<6;
}

ISR(USART_RX_vect){
	byte = UDR0;						//Byte recibido
	if(byte == 'X'){	//caracter final de la cadena de caracteres
		
		
		bufferRx[RxCount] = '\n';		//se añade el caracter final
		duty = atoi((char*)bufferRx);	//se convierte a un numero entero
		memset(bufferRx,0,RxCount);		//se limpia el buffer
		RxCount = 0;					//se reinicia el iterador
		OCR0B = DUTY(62,duty);			//se cambia el duty
	}
	else{
		bufferRx[RxCount] = byte;			//se almacena el buffer de recepcion
		RxCount++;							//se incrementa el iterador
	}
	
	return;
}