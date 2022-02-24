/*
 * main.c
 *
 * Created: 2/23/2022 11:06:21 PM
 *  Author: Lenovo
 */ 
#define F_CPU 8E+6			//8MHz

#include <xc.h>
#include <util/delay.h>
#include <stdio.h>

#define ADC_CH0			0
#define ADC_CH1			1

uint8_t txBuffer[50];
uint16_t len;
/**
  * @brief configura el UART0 en modo de baja velocidad
  * @note :
  * - baud = 9600
  * - paridad: Sin paridad
  * - SP = 1 bit stop
  */
void UART0_Init(void);

/**
  * @brief envio de datos por pin TX USART0
  */
void UART0_SendData(uint8_t *pTxData,uint16_t Len);
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
	uint16_t ch0;
	uint16_t ch1;
	//uat init
	UART0_Init();
	//adc init
	ADC_Init();
	/*send data*/
	len = sprintf((char*)txBuffer,"LECTURA ADC DE DOS CANALES\r\n");
	UART0_SendData(txBuffer,len);
	
    while(1)
    {
        //TODO:: Please write your application code 
		ch0 = ADC_Read(ADC_CH0);
		ch1 = ADC_Read(ADC_CH1);
		len = sprintf((char*)txBuffer,"ADC0 ->%u , ADC1->%u\r\n",ch0,ch1);
		UART0_SendData(txBuffer,len);
		_delay_ms(500);				//retardo
    }
}

void UART0_Init(void){
	/************************************************************************
	* tasa buadios
	* Fos = 8MHz
	* BUAD = 96000
	* UBRRn = 8MHz/(16*9600) - 1
	* UBRRn = 51
	************************************************************************/
	uint16_t ubrrn = 51;
	/*establecer la taza de baudios*/
	UBRR0H = (uint8_t)(ubrrn>>8);
	UBRR0L = (uint8_t)(ubrrn & 0xFF);
	/*configurar la trama de datos*/
	//bit de tx/rx
	UCSR0C &=~ (1U<<UCSZ02);
	UCSR0C |= 1U<<UCSZ01 | 1U<<UCSZ00;		//8-bit de datos
	//paridad
	UCSR0C &=~ (1U<<UPM01 | 1U<<UPM00);		//Sin paridad
	//bit stop
	UCSR0C &=~ (1U<<USBS0);					//1-bit de stop
	/*3. habilitar la Tx/Rx de acuerdo al uso*/
	UCSR0B |= 1U<<RXEN0 | 1U<<TXEN0;		//Se habilita la tx/rx
	return;
}

/**
  * @brief envio de datos por pin TX USART0
  */
void UART0_SendData(uint8_t *pTxData,uint16_t Len){
	while(Len>0){
		//esperamos que buffer de transmision este libre
		while ( !( UCSR0A & (1<<UDRE0)));
		//Escribimos el dato dentro del buffer
		UDR0 = *pTxData;
		pTxData++;
		Len--;
	}
	return;
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