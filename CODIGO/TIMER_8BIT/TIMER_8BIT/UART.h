/*
 * UART.h
 *
 * Created: 27/01/2022 10:01:26
 *  Author: Lenovo
 */ 


#ifndef UART_H_
#define UART_H_

/*INCLUDES*/
#include <xc.h>


/************************************************************************/
/*							MACROS                                      */
/************************************************************************/
#define F_OSC				1000000UL
#define DOUBLE_SPEED		U2X0
#define SINGLE_SPEED		0

#define URBB_VALUE(BAUD,U2x,Ubrr){ if(U2x == U2X0){										\
										Ubrr = (uint16_t)(((F_OSC / (BAUD * 8UL))) - 1);\
										UCSR0A |= 1U<<U2X0;}							\
									else{												\
										Ubrr = (uint16_t)(((F_OSC/ (BAUD * 16UL))) - 1);}}	



/************************************************************************/
/*					PROTOTIPO DE FUNCIONES                              */
/************************************************************************/


/**
  * @brief configuracion del UART
  * @param [spee]:   division entre 8/16
  * @param [baudios]: Taza de baudios deseada
  */
void UART_Config(uint8_t speed,uint32_t buadios);

/**
  * @brief Transmite un byte por el pin TX
  * @param [data]: byte a transmitir
  */
void UART_Transmit(uint8_t data );
/**
  * @brief lee un byte por el pin TX
  * @return el byte recibido
  */
uint8_t UART_Receive( void );
/**
  * @brief transmite n bytes
  */
void UART_SendData(uint8_t *pData,uint16_t Size);
#endif /* UART_H_ */