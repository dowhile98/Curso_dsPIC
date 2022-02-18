/*
 * main.c
 *
 * Created: 2/18/2022 11:10:50 AM
 *  Author: Lenovo
 */ 
#define F_CPU 16E+6
#include <xc.h>
#include <util/delay.h>
#include <stdio.h>
#include "Oled.h"
#include "gui.h"
#include "test.h"
#define CS		DDB2
#define MOSI	DDB3
#define MISO	DDB4
#define SKC		DDB5

#define CS_ON	PORTB &=~ (1U<<CS)
#define CS_OFF	PORTB |= 1U<<CS
/*variables globales*/
uint8_t rxBuffer[100];
uint8_t txBuffer[100];
uint16_t Size;
/*prototipo de funciones*/
void SPI_Init(void);

void SPI_SendData(uint8_t *pTxBuffer,uint16_t Len);
void SPI_ReceiveData(uint8_t *pRxBuffer,uint16_t Len);
void SPI_SendReceiveData(uint8_t *pTxBuffer,uint8_t *pRxBuffer,uint16_t Len);

int main(void)
{
	/*Se INICIALIZA EL SPI*/
	SPI_Init();
	/*Se inicializa la oled*/
	OLED_Init();
	_delay_ms(100);
	//Test_Rectangular();
	/*Size = sprintf((char*)txBuffer,"Hola mundo desde SPI atmega328P");
	CS_ON;
	SPI_SendData(txBuffer,Size);
	CS_OFF;*/
    while(1)
    {
        //TODO:: Please write your application code 
		Test_Circle();
		_delay_ms(1000);
		Test_Rectangular();
		_delay_ms(1000);
		Test_Color();
		_delay_ms(1000);
		Test_Triangle();
		_delay_ms(1000);
    }
}

void SPI_Init(void){
	/*CONFIGURAR LO PINES DE ACUERDO AL MODO SELECCIONADO (MAESTRO/ESCLAVO)*/
	DDRB |= 1U<<CS | 1U<<MOSI | 1U<<SKC;
	/*Configurar los parametros del SPI*/
	//Seleccionar MSB o LSB FIRST
	SPCR &=~ (1U<<DORD);
	//Seleccionar la polaridad del reloj
	SPCR &=~ (1U<<CPOL);
	//Seleccionar la fase del reloj
	SPCR &=~ (1U<<CPHA);
	//Seleccionar el clock rate
	SPSR &=~ (1U<<SPI2X);
	SPCR &=~ (1U<<SPR1 | 1U<<SPR0);		//Fosc/4 (16MHz/4 = 4MHz)
	//seleccionar el modo
	SPCR |= 1U<<MSTR;
	//Habilitar el SPI
	SPCR |= 1U<<SPE;					//habilita el SPI
	return;
}

void SPI_SendData(uint8_t *pTxBuffer,uint16_t Len){
	while(Len>0){
		SPDR = *pTxBuffer;
		pTxBuffer++;
		Len--;
		//se espera que el byte se transmita por completo
		while(!(SPSR & 1U<<SPIF));
	}
	return;
}
void SPI_ReceiveData(uint8_t *pRxBuffer,uint16_t Len){
	while(Len>0){
		//Esperar que el flag SPIF se establesca
		while(!(SPSR & 1U<<SPIF));
		*pRxBuffer = SPDR;
		pRxBuffer++;
		Len--;
	}
	return;
}
//en modo maestro
void SPI_SendReceiveData(uint8_t *pTxBuffer,uint8_t *pRxBuffer,uint16_t Len){
	while(Len>0){
		//se transmite el byte
		SPDR = *pTxBuffer;
		//Esperar que el flag SPIF se establesca
		while(!(SPSR & 1U<<SPIF));
		//se lee el byte recibido
		*pRxBuffer = SPDR;
		//incrementamos los punteros
		pTxBuffer++;
		pRxBuffer++;
		Len--;
	}
	return;
}