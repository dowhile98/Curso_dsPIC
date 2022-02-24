/*
 * main.c
 *
 * Created: 2/23/2022 11:55:37 PM
 *  Author: Lenovo
 */ 

#include <xc.h>
#include "LCD.h"
#include <stdio.h>


#define ADC_CH1			1

/**
  * @brief configuración del ADC en modo single conversion
  */
void ADC_Init(void);

/**
  * @brief lectur de canal x ADC
  * @param [CHx]: numero de canal adc a leerse
  */
uint16_t ADC_Read(uint8_t CHx);

int main(void)
{
	uint16_t ch1;
	float volt;
	char lcdBuffer[20];
	/*LCD INIT*/
	LCD_Init();
	/*ADC INIT*/
	ADC_Init();
	/***************/
	sprintf(lcdBuffer,"***VOLTIMETRO DC***");
	LCD_Set_Cursor(0,0);
	LCD_printStr(lcdBuffer);
	sprintf(lcdBuffer,"***0-20V***");
	LCD_Set_Cursor(1,0);
	LCD_printStr(lcdBuffer);
    while(1)
    {
        //TODO:: Please write your application code 
		ch1 = ADC_Read(ADC_CH1);
		volt = ch1 * 20.0 / 1023;
/*********************************************************/
		sprintf(lcdBuffer,"                     ");
		LCD_Set_Cursor(2,0);
		LCD_printStr(lcdBuffer);
		LCD_Set_Cursor(3,0);
		LCD_printStr(lcdBuffer);
/*********************************************************/
		sprintf(lcdBuffer,"ADC1->%u",ch1);
		LCD_Set_Cursor(2,0);
		LCD_printStr(lcdBuffer);
		//mostrar el voltaje
		sprintf(lcdBuffer,"ADC1->%.4f v",volt);
		LCD_Set_Cursor(3,0);
		LCD_printStr(lcdBuffer);
/*********************************************************/
		_delay_ms(400);
    }
}

/*****************************************************************/
void ADC_Init(void){
	/*seleccionar el prescaler del adc*/
	ADCSRA |= 1U<<ADPS2 | 1U<<ADPS1;	//PSC = 64 -> 8MHz/64 = 125KHZ
	/*voltaje de referencia*/
	ADMUX &=~(1U<<REFS1 | 1U<<REFS0);				//Vref = AREF, internal Vref off
	//ADMUX |=  1U<<REFS0;							//Vref = AVCC
	/*encendemos el adc*/
	ADCSRA |= 1U<<ADEN;								//enciende el ADC
	return;
}
uint16_t ADC_Read(uint8_t CHx){
	ADMUX &=~(0x7U);								//clear
	ADMUX |= CHx;									//Se selecciona el canal
	/*se inicia la conversion*/
	ADCSRA |= 1U<<ADSC;								//inicia la conversion
	//esperar hasta que la conversion inicie
	while(ADCSRA & 1U<<ADSC);						//se espera hasta que ADSC == 04
	//Lectura
	return ADC;										//(ADCH<<8 | ADCL)
}