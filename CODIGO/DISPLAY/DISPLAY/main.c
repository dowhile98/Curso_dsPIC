/*
 * main.c
 *
 * Created: 2/2/2022 10:08:54 AM
 *  Author: Lenovo
 */ 

#include <xc.h>
#include "KEYPAD.h"
#include "UART.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define AD		B , 2
#define BD		B , 3
#define CD		B , 4
#define DD		B , 5
#define EN1		C , 0
#define EN2		C , 1
#define EN3		C , 2
#define EN4		C , 3

typedef enum{
	DISPLAY1 = 1,
	DISPLAY2 ,
	DISPLAY3 ,
	DISPLAY4
	}NumDisplay;
	
uint8_t data;
uint8_t buffer[20] = {0};
uint8_t bufferTx[50];
uint16_t len;
uint8_t i;
void DisplayInit(void);
void DisplaySet(uint8_t num, NumDisplay display);

int main(void)
{
	/*uart init*/
	UART_Config(DOUBLE_SPEED,9600);
	len = sprintf((char*)bufferTx,"CONFIGURACION UART0\r\n");
	UART_SendData(bufferTx,len);
	/*keypad init*/
	Keypad_Init();
	/*display init*/
	//DisplayInit();
	
    while(1)
    {
        //TODO:: Please write your application code 
		data = Keypad_Read();
		/*if(data != KEYPAD_EMPTY){
			if(data == '1')
				DisplaySet(1,DISPLAY1);
			if(data == '2')
				DisplaySet(2,DISPLAY2);
			if(data == '3')
				DisplaySet(3,DISPLAY3);
			if(data == '4')
				DisplaySet(4,DISPLAY4);
		}*/
		if(data != KEYPAD_EMPTY){
			_delay_ms(100);
			len = sprintf((char*)bufferTx,"presionado->%c\r\n",data);
			UART_SendData(bufferTx,len);
			if(data>=48 && data<= 57){
				buffer[i] = data;
				i++;
			}
			if(data == 'X'){
				
				len = sprintf((char*)bufferTx,"NUMERO INGRESADO->");
				UART_SendData(bufferTx,len);
				UART_SendData(buffer,i-1);
				len = sprintf((char*)bufferTx,"\r\n");
				UART_SendData(bufferTx,len);
				memset(buffer,0,i);
				i = 0;
			}
		}
		_delay_ms(10);
		
    }
}

void DisplayInit(void){
	OUTPUT_PIN(AD);
	OUTPUT_PIN(BD);
	OUTPUT_PIN(CD);
	OUTPUT_PIN(DD);
	OUTPUT_PIN(EN1);
	OUTPUT_PIN(EN2);
	OUTPUT_PIN(EN3);
	OUTPUT_PIN(EN4);
}

void DisplaySet(uint8_t num, NumDisplay display){
	PIN_RESET(AD);
	PIN_RESET(BD);
	PIN_RESET(CD);
	PIN_RESET(DD);
	PIN_RESET(EN1);
	PIN_RESET(EN2);
	PIN_RESET(EN3);
	PIN_RESET(EN4);
	//ESTABLECER EL VALOR
	if(num & 0x1)
		PIN_SET(AD);
	if(num & 0x2)
		PIN_SET(BD);
	if(num & 0x4)
		PIN_SET(CD);
	if(num & 0x8)
		PIN_SET(DD);
	//ELEJIMOS EN QUE DISPLAY MOSTRAR
	switch(display){
		case 1: PIN_SET(EN1); break;
		case 2: PIN_SET(EN2); break;
		case 3: PIN_SET(EN3); break;
		case 4: PIN_SET(EN4); break;
	}
	return;
}