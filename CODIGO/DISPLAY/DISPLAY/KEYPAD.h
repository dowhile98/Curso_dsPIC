/*
 * KEYPAD.h
 *
 * Created: 2/02/2022 10:09:47
 *  Author: Lenovo
 */ 

#ifndef KEYPAD_H_
#define KEYPAD_H_


#define F_CPU	16000000UL
#include <xc.h>
#include <util/delay.h>

/*DEFINIR LOS PINES QUE SE VAN USAR*/
//filas
#define R1   D , 2
#define R2   D , 3
#define R3   D , 4
#define R4	 D , 5
//columnas
#define C1	 D , 6
#define C2   D , 7
#define C3   B , 0
#define C4   B , 1

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define OUTPUT_PIN_(a,b)	DDR ## a |= 1U<<DD ## a ## b
#define OUTPUT_PIN(a)		OUTPUT_PIN_(a)
#define INPUT_PIN_(a,b){	DDR ## a &=~ (1U<<DD ## a ## b); \
							PORT ## a |= 1U<< PORT ## a ## b;}
#define INPUT_PIN(a)		INPUT_PIN_(a)

#define PIN_SET_(a,b)		PORT ## a |= 1U<< PORT ## a ## b
#define PIN_SET(a)			PIN_SET_(a)

#define PIN_RESET_(a,b)		PORT ## a &=~ ( 1U<< PORT ## a ## b	)
#define PIN_RESET(a)			PIN_RESET_(a)

#define R1_SET				PIN_SET(R1)
#define R2_SET				PIN_SET(R2)
#define R3_SET				PIN_SET(R3)
#define R4_SET				PIN_SET(R4)

#define R1_RESET			PIN_RESET(R1)
#define R2_RESET			PIN_RESET(R2)
#define R3_RESET			PIN_RESET(R3)
#define R4_RESET			PIN_RESET(R4)

#define PIN_READ_(a,b)		((PIN ## a >> PIN ## a ## b) & 0x1)
#define PIN_READ(a)			PIN_READ_(a) 

#define KEYPAD_EMPTY		-1
#define C1_BIT				PIN_READ(C1)
#define C2_BIT				PIN_READ(C2)
#define C3_BIT				PIN_READ(C3)
#define C4_BIT				PIN_READ(C4)

/**
  * @brief configura los pines usados
  */

void Keypad_Init(void);

/**
  * @brief configura los pines usados
  */

uint8_t Keypad_Read(void);



#endif /* KEYPAD_H_ */