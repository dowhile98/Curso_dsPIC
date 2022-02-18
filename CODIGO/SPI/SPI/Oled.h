/*
 * Oled.h
 *
 * Created: 18/02/2022 12:28:49
 *  Author: Lenovo
 */ 


#ifndef OLED_H_
#define OLED_H_
#define F_CPU	16E+6
#include <xc.h>
#include <util/delay.h>
#include "stdlib.h"
#include "string.h"


#define PAGE_SIZE		8
#define XLevelL			0x00
#define XLevelH			0x10
#define YLevel			0xB0
#define	Brightness		0xFF
#define WIDTH 			128
#define HEIGHT 			64
#define u8				uint8_t

//------------DATA/COMMAND-------------------
#define OLED_CMD     0	//Comando
#define OLED_DATA    1	//dato


//-----------------PINES USADOS PARA CONTROLAR EL OLED----------------
#define OLED_CS   B, 2		//CS OLED
#define OLED_DC   B, 1		//DC OLED
#define OLED_RST  B, 0		//RST OLED


#define PIN_SET_(a,b)		PORT ## a |= 1U<<(PORT ## a ## b)
#define PIN_SET(a)			PIN_SET_(a)
#define PIN_RST_(a,b)		PORT ## a &=~ (1U<<(PORT ## a ## b))
#define PIN_RST(a)			PIN_RST_(a)
#define PIN_OUTPUT_(a,b)	DDR ## a |= 1U<<(DD ## a ## b)
#define PIN_OUTPUT(a)		PIN_OUTPUT_(a)


#define OLED_CS_Clr()  PIN_RST(OLED_CS)
#define OLED_CS_Set()  PIN_SET(OLED_CS)
#define OLED_DC_Clr()  PIN_RST(OLED_DC)
#define OLED_DC_Set()  PIN_SET(OLED_DC)

#define OLED_RST_Clr()  PIN_RST(OLED_RST)
#define OLED_RST_Set()  PIN_SET(OLED_RST)

void OLED_WR_Byte(unsigned dat,unsigned cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_Reset(void);
void OLED_Init_GPIO(void);
void OLED_Init(void);
void OLED_Set_Pixel(unsigned char x, unsigned char y,unsigned char color);
void OLED_Display(void);
void OLED_Clear(unsigned dat);


#endif /* OLED_H_ */