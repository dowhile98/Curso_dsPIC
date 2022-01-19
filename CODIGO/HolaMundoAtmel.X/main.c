/*
 * File:   main.c
 * Author: Lenovo
 *
 * Created on 11 de enero de 2022, 02:09 PM
 */

#define F_CPU 16000000UL


#include "cofiguracion.h"
#include <util/delay.h>


void main(void) {
    DDRB |= 1U<<DDB5;           //PB0 -> OUTPUT
    
    while(1){
        PORTB ^= 1U<<PORTB5;    //toggle led
        _delay_ms(20);         //retardo de 100ms
    }
}
