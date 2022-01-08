/*
 * File:   main.c
 * Author: Lenovo
 *
 * Created on 8 de enero de 2022, 01:24 PM
 */


#include "configuracion.h"
#include "reloj.h"

void main(void) {
    TRISA &=~ 1U<<0;            //Configuracion como salida
    while(1){
        LATA ^= 1u<<0;          //toggle led
        delay_ms(100);          //delay 10ms
    }
}
