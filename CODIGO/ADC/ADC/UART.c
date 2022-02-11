/*
 * UART.c
 *
 * Created: 27/01/2022 10:05:11
 *  Author: Lenovo
 */ 
#include "UART.h"

/**
  * @brief configuracion del UART
  * @param [baudios]: Taza de baudios deseada
  */
void UART_Config(uint8_t speed,uint32_t buadios){
	uint16_t baud;
	URBB_VALUE(9600,speed,baud);
	/*1. Establecer la taza de baudios*/
	UBRR0H = (uint8_t)(baud>>8);
	UBRR0L = (uint8_t)(baud & 0xFF);
	/*2. configurar el formtato del frame*/
	//bit de tx/rx
	UCSR0C &=~ (1U<<UCSZ02);
	UCSR0C |= 1U<<UCSZ01 | 1U<<UCSZ00;		//8-bit de datos
	//paridad
	UCSR0C &=~ (1U<<UPM01 | 1U<<UPM00);		//Sin paridad
	//bit stop
	UCSR0C &=~ (1U<<USBS0);					//1-bit de stop
	/*3. habilitar la Tx/Rx de acuerdo al uso*/
	UCSR0B |= 1U<<RXEN0 | 1U<<TXEN0;		//Se habilita la tx/rx
	/*4. configuracion de IT*/
	UCSR0B |= 1U<<RXCIE0;					//habilita la interrupcion para la recepcion
	return;
}

void UART_Transmit(uint8_t data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)));
	/* Put data into buffer, sends the data */
	UDR0 = data;
}


uint8_t UART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}

void UART_SendData(uint8_t *pData,uint16_t Size){
	while(Size-->0){
		 UART_Transmit(*pData);
		 pData++;
	}
	return;
}