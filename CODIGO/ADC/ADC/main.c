/*
 * main.c
 *
 * Created: 2/11/2022 10:27:41 AM
 *  Author: Lenovo
 */ 
#define F_CPU		16E+6
#include <xc.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#include "UART.h"


#define ADC_CH0			0
#define ADC_CH1			1
#define ADC_CH2			2
#define ADC_CH3			3
#define ADC_CH4			4
#define ADC_CH5			5
//Single conversion
void ADC_SingleConversion(void);
//lectura del ADC
uint16_t ADC_Read(uint8_t CHx);

uint16_t data;					//conversion ADC
uint8_t txBuffer[50];			//buffer de transmision
uint16_t len;					//numero de bytes a transmitir
float volt;
float temp;


int main(void)
{
	/*pin init*/
	DDRB |= 1U;					//SALIDA PB0
	/*uart init*/
	UART_Config(DOUBLE_SPEED,9600);
	/*ADC single conversion init*/
	ADC_SingleConversion();
	
    while(1)
    {
        //TODO:: Please write your application code 
		data = ADC_Read(ADC_CH0);
		len = sprintf((char*)txBuffer,"CH0 -> %d\r\n",data);
		UART_SendData(txBuffer,len);
		
		data = ADC_Read(ADC_CH2);			//lee el LM35
		/*CONVERSION DE VOLTAJE A TEMPERATURA*/
		volt = data * 5.0/1024;				//el voltaje leido
		temp = volt * 100;					//temperatura en °C
		len = sprintf((char*)txBuffer,"volt: %.2f    temperatura: %.2f\r\n",volt,temp);
		UART_SendData(txBuffer,len);
		/*realizar el control del motor*/
		if(temp>30.0){
			PORTB |= 1U;
		}else{
			PORTB &=~ 1U;
		}
		
		_delay_ms(200);
    }
}

//Single conversion
void ADC_SingleConversion(void){
	/*seleccinar el prescaler*/
	ADCSRA |= 1U<<ADPS2 | 1U<<ADPS1 | 1U<<ADPS0;	//PSC = 128 -> 16MHz/128 = 125KHZ
	/*voltaje de referencia*/
	ADMUX &=~(1U<<REFS1 | 1U<<REFS0);				//Vref = AREF, internal Vref off
	ADMUX |=  1U<<REFS0;							//Vref = AVCC
	/*encender el ADC*/
	ADCSRA |= 1U<<ADEN;								//enciende el ADC
	return;
}

//lectura del ADC
uint16_t ADC_Read(uint8_t CHx){
	ADMUX &=~(0x7U);								//clear
	ADMUX |= CHx;									//Se selecciona el canal 
	/*se inicia la conversion*/
	ADCSRA |= 1U<<ADSC;								//inicia la conversion
	//esperar hasta que la conversion inicie
	while(ADCSRA & 1U<<ADSC);						//se espera hasta que ADSC == 0
	//Lectura
	return ADC;										//(ADCH<<8 | ADCL)
}