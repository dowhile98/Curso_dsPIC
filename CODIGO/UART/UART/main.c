/*
 * main.c
 *
 * Created: 1/27/2022 10:00:11 AM
 *  Author: Lenovo
 */
#include <xc.h>
#include "UART.h"
#include <stdio.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LED1  B , 5
#define LED2  B , 4

/*Macro para pin como salida*/
#define PIN_OUTPUT(P,b)	DDR ## P |= 1U<<DD ## P ## b
/*macro para pin como entrada pull up*/
#define PIN_INPUT(P,b){	DDR ## P &=~ (1U<<DD ## P ## b);\
						PORT ## P |= 1U<<PORT ## P ## b);}

#define PIN_SET_(P,b)	PORT ## P |= 1U<< PORT ## P ## b;
#define PIN_SET(a)		PIN_SET_(a)
#define PIN_RESET(P,b)	PORT ## P &=~ (1U<< PORT ## P ## b);
#define PIN_READ(P,b)	(PIN ## P)>>PIN ## P ## b					
#define PIN_TOGGLE(P,b)	PIN ## P |= 1U<<PIN ## P ## b			
/*variable global*/
uint8_t bufferTx[50];
uint8_t bufferRx[50];
uint16_t RxCount;
uint8_t byte;

uint16_t bufferLen;
uint16_t numRx;

int main(void)
{
	/*UART0, CONFIG*/
	UART_Config(DOUBLE_SPEED,9600);
	sei();								//habilita las interrupciones globales
	bufferLen = sprintf((char*)bufferTx,"CONFIGURACION UART0\r\n");
	UART_SendData(bufferTx,bufferLen);
	//PIN PB5
	PIN_OUTPUT(B,5);
	PIN_OUTPUT(B,4);
	
    while(1)
    {
        //TODO:: Please write your application code 
		/*byte = UART_Receive();
		UART_Transmit(byte);*/
		/*if(UCSR0A & 1U<<RXC0){
			byte = UDR0;
			UART_Transmit(byte);
		}*/
		if(numRx>100){
			PIN_SET(LED2);
		}
		else
			PIN_RESET(B,4);
		
    }
}

ISR(USART_RX_vect){
	byte = UDR0;						//Byte recibido
	bufferRx[RxCount] = byte;			//se almacena el buffer de recepcion
	RxCount++;							//se incrementa el iterador
	if(byte == '\n' || byte == '\r'){	//caracter final de la cadena de caracteres
		
		PIN_TOGGLE(B,5);				
		bufferRx[RxCount] = '\n';		//se añade el caracter final
		UART_SendData(bufferRx,RxCount);//se muestran los bytes recibidos	
		numRx = atoi((char*)bufferRx);	//se convierte a un numero entero
		memset(bufferRx,0,RxCount);		//se limpia el buffer
		RxCount = 0;					//se reinicia el iterador
	}
	
	return;
}