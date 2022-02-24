/*
 * LCD.c
 *
 * Created: 20/01/2022 09:32:26
 *  Author: Lenovo
 */ 
#include "LCD.h"
/********************PRIVATE VARIABLES**************/


static const char UserFont[8][8] =
{
	{ 0x11,0x0A,0x04,0x1B,0x11,0x11,0x11,0x0E },
	{ 0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10 },
	{ 0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18 },
	{ 0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C },
	{ 0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E },
	{ 0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F },
	{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 }
};

/************************************************************************/
/*							PRIVATE FUNCTION                            */
/************************************************************************/
/**
@brief CONFIGURA LOS FINES DE LCD
@param :none
@returns: none
@verbatim
 * esta funcion inicializa los pines elegidos para la conexion con la lcd
 */
static void LCD_InitPinout(void){
	LCD_RS_DDR |= 1U<<LCD_RS_PIN;
	LCD_EN_DDR |= 1U<<LCD_EN_PIN;
	LCD_D4_DDR |= 1U<<LCD_D4_PIN;
	LCD_D5_DDR |= 1U<<LCD_D5_PIN;
	LCD_D6_DDR |= 1U<<LCD_D6_PIN;
	LCD_D7_DDR |= 1U<<LCD_D7_PIN;
	/*CLEAR PIN VALUES*/
	LCD_RS_PORT &=~ (1U<<LCD_RS_PIN);
	LCD_EN_PORT &=~ (1U<<LCD_EN_PIN);
	LCD_D4_PORT &=~ (1U<<LCD_D4_PIN);
	LCD_D5_PORT &=~ (1U<<LCD_D5_PIN);
	LCD_D6_PORT &=~ (1U<<LCD_D6_PIN);
	LCD_D7_PORT &=~ (1U<<LCD_D7_PIN);
	return;
}

/**
  * @genera un pulso para enviar los datos                                                                 
  */
static void LCD_pulse_EN(void){
	LCD_EN_HI(); // Habilita pin EN ON
	lcd_delay_us(500);
	LCD_EN_LO(); // Habilita pin EN Off
}

/**
 * @brief EST FUNCION NOS SIRVE PARA ENVIAR UN NIBLE A LA PANTALLA
 */
static void LCD_Out_Data4(unsigned char val);
/**
 * @brief INICIALIZA LA PANTALLA LCD
 * @param :none
 * @return : none
 */

/************************************************************************/
/*						USER FUNCTION                                   */
/************************************************************************/
void LCD_Init(void){
	uint8_t i;
	char const *p;
	LCD_InitPinout();
	//se espera por 45ms
	lcd_delay_ms(45);

	LCD_D4_HI();
	LCD_D5_HI();
	LCD_D6_LO();
	LCD_D7_LO();
	lcd_delay_ms(15);  // Delay de 15 ms

	LCD_D4_HI();
	LCD_D5_HI();
	LCD_D6_LO();
	LCD_D7_LO();
	LCD_pulse_EN();
	lcd_delay_ms(6); // Delay de 4.1 ms

	LCD_D4_HI();
	LCD_D5_HI();
	LCD_D6_LO();
	LCD_D7_LO();
	LCD_pulse_EN();
	lcd_delay_ms(1); // Delay de 100 us

	LCD_D4_HI();
	LCD_D5_HI();
	LCD_D6_LO();
	LCD_D7_LO();
	LCD_pulse_EN();
	lcd_delay_ms(1);
	LCD_D4_LO();
	LCD_D5_HI();
	LCD_D6_LO();
	LCD_D7_LO();
	LCD_pulse_EN();
	lcd_delay_ms(1);
	LCD_Write_Cmd(0x28); // Establecemos LCD como (Datos 4-Bit, N_lineas=2, Font=0 5X7)
	LCD_Write_Cmd(0x0C); // Enciende el LCD sin cursor.
	LCD_Write_Cmd(0x06); // Inicializa cursor

	  /* Cargamos el caracter definidos por usuario en la CGRRAM */
	LCD_Write_Cmd(0x40); /* Establece la direccion CGRAM desde 0 */
	p = &UserFont[0][0];
	for (i = 0; i < sizeof(UserFont); i++, p++)
	LCD_printChar(*p);
	LCD_Write_Cmd(0x80);
}
/**
 * @brief EST FUNCION NOS SIRVE PARA ENVIAR UN NIBLE A LA PANTALLA
 */
static void LCD_Out_Data4(unsigned char val){
	/*BIT[0]*/
	LCD_D4_PORT &=~(1U<<LCD_D4_PIN);
	LCD_D4_PORT |= (((val>>0)&0x01U)<<LCD_D4_PIN);
	/*BIT[1]*/
	LCD_D5_PORT &=~(1U<<LCD_D5_PIN);
	LCD_D5_PORT |= (((val>>1)&0x01U)<<LCD_D5_PIN);
	/*BIT[2]*/
	LCD_D6_PORT &=~(1U<<LCD_D6_PIN);
	LCD_D6_PORT |= (((val>>2)&0x01U)<<LCD_D6_PIN);
	/*BIT[3]*/
	LCD_D7_PORT &=~(1U<<LCD_D7_PIN);
	LCD_D7_PORT |= (((val>>3)&0x01U)<<LCD_D7_PIN);
	
}
/**
 * @brief ESTA FUNCION ENVIA UN BYTE DE DATOS A LA LCD
 */
void LCD_Write_Byte(unsigned char val){
	LCD_Out_Data4((val>>4)&0x0F);
	LCD_pulse_EN();
	LCD_Out_Data4(val&0x0F);
	LCD_pulse_EN();
}
/**
 * @brief ESTA FUNCION ENVIA UN COMANDO A LA LCD
 */
void LCD_Write_Cmd(unsigned char val){
	LCD_RS_LO();         // pin RS = 0 (Seleccion comando)
	LCD_Write_Byte(val);
	lcd_delay_ms(3);
}
/**
 * @brief ESTA FUNCION ENVIA UN CARACTER A LA LCD
 */
void LCD_printChar(unsigned char c){
	LCD_RS_HI();        // pin RS = 1 (Seleccion caracteres)
	LCD_Write_Byte(c);
}
/**
 * @brief ESTABLECE LA POSICION DEL CURSOR
 */
void LCD_Set_Cursor(uint8_t x, uint8_t y){
	uint8_t addr = 0;
	switch(x){
		case 0: addr = 0x80; break; //Starting address of 1st line
    case 1: addr = 0xC0; break; //Starting address of 2nd line
    case 2: addr = 0x94; break; //Starting address of 3rd line
    case 3: addr = 0xD4; break; //Starting address of 4th line
    default: ; 
	}
	addr += y;
	LCD_Write_Cmd(addr);
	return;
}
/**
 * @brief ENVIA UNA CADENA A LA PANTALLA
 */
void LCD_printStr(char *buffer) {
    while (*buffer) // Write data to LCD up to null
    {
    	LCD_printChar(*buffer); // Write character to LCD
        buffer++; // Increment buffer
    }
    return;
}
/**
 * /@briefENVIA UN NUMERO A LA LCD
 */
void LCD_printInt(int number) {
    char numStr[16]; //para convertir en cadena
    sprintf(numStr, "%d", number); //funcion para unir en cadena de caracteries
    LCD_printStr(numStr);
}

void LCD_printFloat(double number) {
    char numStr[16];
    sprintf(numStr, "%.2f", number); //funcion para unir en cadena de caracteries
    LCD_printStr(numStr);
}




void LCD_BarGraphic (int value, int size)
{
  int i;

  value = value * size / 20; /* Matriz de 5 x 8 pixels */
  for (i = 0; i < size; i++)
  {
    if (value > 5) {
    	LCD_printChar (0x05);
      value -= 5;
    }
  else {
    LCD_printChar((uint8_t)value);

    break;
  }
  }
}

/*    Funcion que muestra un caracter grafico en la pantalla LCD
      especificando la posicion pos_x horizontal de inicio y la
      posicion pos_y vertical de la pantalla LCD                 */
//-----------------------------------------------------------------
void LCD_BarGraphicXY (int pos_x, int pos_y, int value)
{
  int i;

  LCD_Set_Cursor((uint8_t)pos_x,(uint8_t) pos_y);
  for (i = 0; i < 16; i++)
  {
    if (value > 5) {
    	LCD_printChar (0x05);
      value -= 5;
    } else {
    	LCD_printChar ((uint8_t)value);
      while (i++ < 16) LCD_printChar (0);
    }
  }
}