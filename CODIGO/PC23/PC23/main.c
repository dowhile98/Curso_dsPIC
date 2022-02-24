/*
 * main.c
 *
 * Created: 2/24/2022 12:41:50 AM
 *  Author: Lenovo
 */ 
#define F_CPU 8E+6
#include <xc.h>
#include <util/delay.h>

#define ADC_CH1			1
#define __DUTY(x)	(uint16_t)((3999.0/100)*x*100/1023)

void ADC_Init(void);
uint16_t ADC_Read(uint8_t CHx);
void TIMER1_ConfiPWM(void);
uint16_t duty;

int main(void)
{
	//configurar los pines de control de configuracion de pines
	DDRB |= 1<<3 | 1U;			//Configuracion como salida
	PORTB &=~(1U<<3 | 1U);		//reset
	//adc init
	ADC_Init();
	//pwm init
	TIMER1_ConfiPWM();
    while(1)
    {
		//GIRA EN UN SENTIDO
		PORTB &=~ 1U<<3;
		PORTB |= 1U;
		duty = ADC_Read(ADC_CH1);
		OCR1A = __DUTY(duty);		//se establece la velocidad
		_delay_ms(2000);
		//CAMBIO DE SENTIDO
		PORTB &=~ 1U;
		PORTB |= 1U<<3;
		duty = ADC_Read(1);
		OCR1A = __DUTY(duty);		//se establece la velocidad
		_delay_ms(2000);
        //TODO:: Please write your application code 
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
/***************************************************/

void TIMER1_ConfiPWM(void){
	DDRB |= ( 1<< 1);	// Configuramos el PB1 como salida.
	TCNT1 = 0;					// Reiniciamos el contador inicial (por siacaso)
	/**
	* Fpwm = 2000
	* N = 1
	* ICR1 = 8MHz/(1 * 2000) - 1
	* ICR1 = 3999*/
	ICR1 = 3999;				// Configuramos el periodo de la señal (el TOP de nuestra PWM)
	TCCR1A =  (1 << COM1A1) | (0 << COM1A0) ; // Ponemos a 'bajo' el OCR1A cuando coincida el Compare Match
	TCCR1A |=  (1 << WGM11) | (0 << WGM10) ; // Fast PWM: TOP: ICR1
	TCCR1B = (1 << WGM13) | (1 << WGM12); // // Fast PWM: TOP: ICR1
	TCCR1B |=  ( 1 << CS10 ); // Preesc = 1
	OCR1A = __DUTY(duty); // duty 0%
	return;
}
