/*
 * LCD.h
 *
 * Created: 20/01/2022 09:32:11
 *  Author: Lenovo
 */ 


#ifndef LCD_H_
#define LCD_H_
/*inclusiones*/
#include <xc.h>
#include <stdio.h>
/*****************USER CONFIGURATION************************/
#define 	F_CPU   1000000UL
#include <util/delay.h>

/*RS PIN*/
#define LCD_RS_PIN				2
#define	LCD_RS_DDR				DDRD
#define LCD_RS_PORT				PORTD
/*EN PIN*/
#define LCD_EN_PIN				4
#define LCD_EN_DDR				DDRD
#define LCD_EN_PORT				PORTD
/*D4 PIN*/
#define LCD_D4_PIN				7
#define LCD_D4_DDR				DDRD
#define LCD_D4_PORT				PORTD
/*D5 PIN*/
#define LCD_D5_PIN				0
#define LCD_D5_DDR				DDRB
#define LCD_D5_PORT				PORTB
/*D6 PIN*/
#define LCD_D6_PIN				4
#define LCD_D6_DDR				DDRB
#define LCD_D6_PORT				PORTB
/*D7 PIN*/
#define LCD_D7_PIN				5
#define LCD_D7_DDR				DDRB
#define LCD_D7_PORT				PORTB
/**********************************************************/

#define lcd_delay_us		_delay_us
#define lcd_delay_ms		_delay_ms
/* Commands*/
#define LCD_CLEARDISPLAY        0x01
#define LCD_RETURNHOME          0x02
#define LCD_ENTRYMODESET        0x04
#define LCD_DISPLAYCONTROL      0x08
#define LCD_CURSORSHIFT         0x10
#define LCD_FUNCTIONSET         0x20
#define LCD_SETCGRAMADDR        0x40
#define LCD_SETDDRAMADDR        0x80

/* Flags for display entry mode */
#define LCD_ENTRYRIGHT          0x00
#define LCD_ENTRYLEFT           0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

/* Flags for display on/off control */
#define LCD_DISPLAYON           0x04
#define LCD_CURSORON            0x02
#define LCD_BLINKON             0x01


/* Flags for display/cursor shift */
#define LCD_DISPLAYMOVE         0x08
#define LCD_CURSORMOVE          0x00
#define LCD_MOVERIGHT           0x04
#define LCD_MOVELEFT            0x00

/* Flags for function set */
#define LCD_8BITMODE            0x10
#define LCD_4BITMODE            0x00
#define LCD_2LINE               0x08
#define LCD_1LINE               0x00
#define LCD_5x10DOTS            0x04
#define LCD_5x8DOTS             0x00

// Definimos que nombres para activar los pines a nivel 'High' y 'Low'
#define LCD_EN_HI()			LCD_EN_PORT |=1<<LCD_EN_PIN
#define LCD_EN_LO()			LCD_EN_PORT &=~(1U<<LCD_EN_PIN)
#define LCD_RS_HI() 		LCD_RS_PORT |=1<<LCD_RS_PIN
#define LCD_RS_LO() 		LCD_RS_PORT &=~(1U<<LCD_RS_PIN)

#define LCD_D4_HI() 		LCD_D4_PORT |=1<<LCD_D4_PIN
#define LCD_D4_LO() 		LCD_D4_PORT &=~(1U<<LCD_D4_PIN)
#define LCD_D5_HI() 		LCD_D5_PORT |=1<<LCD_D5_PIN
#define LCD_D5_LO() 		LCD_D5_PORT &=~(1U<<LCD_D5_PIN)
#define LCD_D6_HI() 		LCD_D6_PORT |=1<<LCD_D6_PIN
#define LCD_D6_LO() 		LCD_D6_PORT &=~(1U<<LCD_D6_PIN)
#define LCD_D7_HI() 		LCD_D7_PORT |=1<<LCD_D7_PIN
#define LCD_D7_LO()			LCD_D7_PORT &=~(1U<<LCD_D7_PIN)

/*   Definimos los nombres de los comandos para el LCD                  */
/* LINES*/
#define DDRAM_LINE1   0b10000000  /* 4-bit Interface               */
#define DDRAM_LINE2   0b11000000  /* 4-bit Interface               */
#define CGRAM_ADDRESS 0b01000000  /* 4-bit Interface               */


#define LCD_cursor_home() 		LCD_Write_Cmd(0x02)		// Establecer el cursor a 'Home'
#define LCD_clear()				LCD_Write_Cmd(0x01)		//clear LCD
#define LCD_display_on() 		LCD_Write_Cmd(0x0E)		// Pantalla LCD Activa
#define LCD_display_off() 		LCD_Write_Cmd(0x08)		// Pantalla LCD Inactiva
#define LCD_cursor_blink() 		LCD_Write_Cmd(0x0F)		// Cursor intermitente
#define LCD_cursor_on() 		LCD_Write_Cmd(0x0E)	  	// Cursor visible activo
#define LCD_cursor_off() 		LCD_Write_Cmd(0x0C)		// Cursor inactivo
#define LCD_cursor_left() 		LCD_Write_Cmd(0x10)		// Movimiento hacia la izquierda del cursor
#define LCD_cursor_right() 		LCD_Write_Cmd(0x14)		// Movimiento hacia la derecha del cursor
#define LCD_display_sleft() 	LCD_Write_Cmd(0x18)		// Movimiento a la izquierda de la pantalla
#define LCD_display_sright() 	LCD_Write_Cmd(0x1C)		// Movimiento a la derecha de la pantalla

/***********************************************************************************
 * 				PROTOTIPO DE FUNCIOENS PARA EL MANEJO LA LCD
 **********************************************************************************/

/**
 * @brief INICIALIZA LA PANTALLA LCD
 * @param :none
 * @return : none
 */
void LCD_Init(void);
/**
 * @brief ESTA FUNCION ENVIA UN BYTE DE DATOS A LA LCD
 */
void LCD_Write_Byte(unsigned char val);
/**
 * @brief ESTA FUNCION ENVIA UN COMANDO A LA LCD
 */
void LCD_Write_Cmd(unsigned char val);
/**
 * @brief ESTA FUNCION ENVIA UN CARACTER A LA LCD
 */
void LCD_printChar(unsigned char c);
/**
 * @brief ESTABLECE LA POSICION DEL CURSOR
 */
void LCD_Set_Cursor(uint8_t x, uint8_t y);
/**
 * @brief ENVIA UNA CADENA A LA PANTALLA
 */
void LCD_printStr(char *buffer);
/**
 * /@briefENVIA UN NUMERO A LA LCD
 */
void LCD_printInt(int number);

void LCD_printFloat(double number);

//ESTA FUNCIONES ESTAN EN DESARROLO
void LCD_BarGraphic (int value, int size);
void LCD_BarGraphicXY (int pos_x, int pos_y, int value);


#endif /* LCD_H_ */