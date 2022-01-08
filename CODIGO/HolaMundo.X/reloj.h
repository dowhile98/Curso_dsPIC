/* 
 * File:   reloj.h
 * Author: Lenovo
 *
 * Created on 8 de enero de 2022, 01:27 PM
 */

#ifndef RELOJ_H
#define	RELOJ_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <libpic30.h>
#define FCY                 (7370000UL/2)                  // esto es igual a: Fcy = Fosc/2
#define delay_ms(x)         __delay32((FCY/1000)*x)         //macro para generar retardos en milisegundos
#define BAUDRATE 9600
#define BRGVAL    ((FCY/BAUDRATE)/16)-1


#ifdef	__cplusplus
}
#endif

#endif	/* RELOJ_H */

