/*
 * KEYPAD.c
 *
 * Created: 2/02/2022 10:10:04
 *  Author: Lenovo
 */ 

#include "KEYPAD.h"

/**************DFININICION DE VARIABLES GLOBLALES*******************************/
static const uint8_t key_table [4][4]= {
										{'7','8','9','/'},
										{'4','5','6','X'},
										{'1','2','3','-'},
										{'c','0','=','+'}
														};

/**
  * @brief configura los pines usados
  */

void Keypad_Init(void){
	//configuramos los pines de salida
	OUTPUT_PIN(R1);
	OUTPUT_PIN(R2);
	OUTPUT_PIN(R3);
	OUTPUT_PIN(R4);
	//configuramos los pines como entrada
	INPUT_PIN(C1);
	INPUT_PIN(C2);
	INPUT_PIN(C3);
	INPUT_PIN(C4);
}

/**
  * @brief configura los pines usados
  */

uint8_t Keypad_Read(void){
	uint8_t row;
	int8_t col = 0;
	uint8_t data;
	for(row = 0; row<4; row++){
		R1_SET;
		R2_SET;
		R3_SET;
		R4_SET;
		switch(row){
			case 0: R1_RESET; break;
			case 1: R2_RESET; break;
			case 2: R3_RESET; break;
			case 3: R4_RESET; break;
		}
		_delay_us(500);
		data = (uint8_t)(C4_BIT<<3 | C3_BIT<<2 | C2_BIT<<1 | C1_BIT<<0);
		col = KEYPAD_EMPTY;
		switch(data){
			case 0xE: col = 0; break;
			case 0xD: col = 1; break;
			case 0xB: col = 2; break;
			case 0x7: col = 3; break;
		}
		if(col != KEYPAD_EMPTY)
		break;      //salida del for
	}
	if(col == KEYPAD_EMPTY)
		return KEYPAD_EMPTY;
	else
		return(key_table[row][col]);
}