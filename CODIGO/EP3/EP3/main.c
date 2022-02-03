/*
 * main.c
 *
 * Created: 2/3/2022 3:18:28 PM
 *  Author: Lenovo
 */ 

#include <xc.h>
#define FCLK					8000000
#define DUTY(_duty)				(uint16_t)(((float)511/100)*_duty)
#define N						8

/************************************************************************/
/* FreqPWM = FLCK/(N*(511 +1))                                          */
/************************************************************************/
/************************************************************************/
/* OCR1B = (TOP/100)*%DutyCicle                                                                     */
/************************************************************************/
void TIMER1_ConfiPWM(void);

int main(void)
{
	/*PB0-PB1 -> CONTROL DE GIRO*/
	DDRB |= 1U<<1 | 1U;
	PORTB |= 1U;
	TIMER1_ConfiPWM();
	OCR1B = DUTY(50);		//50%
    while(1)
    {
        //TODO:: Please write your application code 
    }
}

void TIMER1_ConfiPWM(void){
	DDRB |= ( 1U<<2);		// Configuramos el PB2 como salida.
	TCNT1 = 0;				// Reiniciamos el contador inicial (por siacaso)
	ICR1 = 511;				// PWM 9BIT
	TCCR1A	|= 1U<<COM1B1 | 0<<COM1B0;
	TCCR1A |=  (1 << WGM11) | (0 << WGM10) ;	// Fast PWM: TOP: ICR1
	TCCR1B = (1 << WGM13) | (1 << WGM12);		// // Fast PWM: TOP: ICR1
	TCCR1B |= (0 << CS12) | (1 << CS11) | ( 0 << CS10 ); // Preesc = 8
	return;
}