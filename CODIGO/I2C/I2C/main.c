/*
 * main.c
 *
 * Created: 2/24/2022 11:35:03 AM
 *  Author: Lenovo
 */ 

#include <xc.h>
#include "MPU6050.h"
#include "ssd1306.h"
#include <stdio.h>
#define MPU_ADDRESS			0x68
#define I2C_SPEED			400E+3
/* VARIABLES GLOBALES*/
uint8_t data[] = "HOLA MUNDO DESDE I2C ATMEGA328P";
RawData_Def myAccelRaw, myGyroRaw;
ScaledData_Def myAccelScaled, myGyroScaled;
char buffer[100];
/**
  * @brief configuracion del TWI (I2C)
  */
void I2C_Init(uint32_t speed);
/** 
  * @transmitir datos del maestro
  */
void I2C_MasterSendData(uint8_t SlaveAddr, uint8_t *pTxBuffer,uint32_t Len);

/**
  * @brief recibir datos del esclavo
  */
void I2C_MasterReceiveData(uint8_t SlaveAddr, uint8_t *pRxBuffer,uint32_t Len);
/**
  * @brief configura el MPU6050
	*/
void MPU6050_Init_Config(void);
int main(void)
{
	DDRB |= 1U<<5 | 1;
	PORTB &=~ 1U<<5;
	PORTB |= 1;
	/*INICIALIMAMOS EL I2C*/
	I2C_Init(I2C_SPEED);
	//Enviar dato
	
	//I2C_MasterSendData(MPU_ADDRESS,data,31);
	//MPU6050_Init_Config();
	PORTB &=~ 1;
	_delay_ms(10);
	PORTB |= 1U;
	
	SSD1306_Init();

	SSD1306_GotoXY (0,0);
	sprintf((char*)buffer,"MPU650");
	SSD1306_Puts (buffer, &Font_16x26, 1);
	SSD1306_GotoXY (10, 30);
	sprintf((char*)buffer,"JQB");
	SSD1306_Puts (buffer, &Font_11x18, 1);
	SSD1306_UpdateScreen(); //display
    while(1)
    {
        //TODO:: Please write your application code 
		/*MPU6050_Get_Accel_Scale(&myAccelScaled);
		MPU6050_Get_Gyro_Scale(&myGyroScaled);
		
		
		
		SSD1306_Clear();
		SSD1306_GotoXY (0,0);
		sprintf(buffer,"ACELEROMTRO");
		SSD1306_Puts(buffer, &Font_11x18, 1);
		SSD1306_GotoXY(0,20);
		sprintf(buffer,"x:%.1f y:%.1f",myAccelScaled.x,myAccelScaled.y);
		SSD1306_Puts(buffer, &Font_7x10, 1);
		SSD1306_UpdateScreen();


		SSD1306_GotoXY (0,33);
		sprintf((char*)buffer,"GIROSCOPIO");
		SSD1306_Puts(buffer, &Font_11x18, 1);
		sprintf((char*)buffer,"x:%.1f y:%.1f",myGyroScaled.x,myGyroScaled.y);
		SSD1306_GotoXY (0, 50);
		SSD1306_Puts((char*)buffer, &Font_7x10, 1);
		SSD1306_UpdateScreen();
		_delay_ms(500);*/
		
		PINB |= 1U<<5;
		_delay_ms(100);
    }
}

/**
  * @brief configuracion del TWI (I2C)
  */
void I2C_Init(uint32_t speed){
	uint8_t br;
	/*configurar el bit rate*/
	br = ((F_CPU / speed) - 16) / 2;
	TWBR = br;
	/*habilitar el i2c*/
	TWCR |= 1U<<TWEN;
	return;
}

/** 
  * @transmitir datos del maestro
  */
void I2C_MasterSendData(uint8_t SlaveAddr, uint8_t *pTxBuffer,uint32_t Len){
	//1. generar la condición de inicio
	TWCR |= 1U<<TWINT | 1U<<TWEN | 1U<<TWSTA;
	//2. Esperar que se genera la condición de start
	while (!(TWCR & (1<<TWINT))) ;
	//3. enviar la direccion del esclavo + w(0)
	SlaveAddr = SlaveAddr<<1;
	SlaveAddr &=~ (1U);			//enviar datos al esclavo
	TWDR = SlaveAddr;
	TWCR = (1<<TWINT) | (1<<TWEN);
	//4. esperar la confirmacion del esclavo
	while (!(TWCR & (1<<TWINT)));
	
	while(Len>0){
		TWDR = *pTxBuffer;
		TWCR = (1<<TWINT) | (1<<TWEN);
		/*Esperamos que se transmita el dato*/
		while (!(TWCR & (1<<TWINT)));
		//incrementar el puntero y disminuir Len
		pTxBuffer++;
		Len--;
	}
	/*generar la condición de stop*/
	TWCR = (1<<TWINT)| (1<<TWEN) | (1<<TWSTO);
	
	return;
}
/**
  * @brief recibir datos del esclavo
  */
void I2C_MasterReceiveData(uint8_t SlaveAddr, uint8_t *pRxBuffer,uint32_t Len){
	//1. generar la condicion de estart
	TWCR |= 1U<<TWINT | 1U<<TWEN | 1U<<TWSTA;
	//2. Esperar que se genera la condición de start
	while (!(TWCR &(1<<TWINT)));
	//3. enviar la direccion del esclavo + r(1)
	SlaveAddr = SlaveAddr<<1;
	SlaveAddr |= (1U);			//recibir datos del esclavo
	TWDR = SlaveAddr;
	TWCR = (1<<TWINT) | (1<<TWEN);
	//4. esperar la confirmacion del esclavo
	while (!(TWCR & (1<<TWINT)));
	
	
	while(Len>0){
		if(Len == 1){
			TWCR &=~ (1U<<TWEA);			//ya no se quiere genera el ack
			TWCR = (1U<<TWINT) |( 1U<<TWEN);
			while (!(TWCR & (1<<TWINT)));
			*pRxBuffer = TWDR;
			Len--;
		}else{
			TWCR = (1U<<(TWINT) | 1U<<(TWEN) | 1U<<(TWEA));
			while (!(TWCR & (1<<TWINT)));
			*pRxBuffer = TWDR;
			pRxBuffer++;
			Len--;
		}
	}
	/*generar la condición de stop*/
	TWCR = (1<<TWINT)| (1<<TWEN) | (1<<TWSTO);
	
	return;
}

void MPU6050_Init_Config(void){
	MPU_ConfigTypeDef MPU_init = {0};
	MPU_init.ClockSource = Internal_8MHz;
	MPU_init.Gyro_Full_Scale = AFS_SEL_2g;
	MPU_init.CONFIG_DLPF = DLPF_184A_188G_Hz;
	MPU_init.Gyro_Full_Scale =  FS_SEL_500;
	MPU_init.Sleep_Mode_Bit = 0;

	//se inicializan los parametros del MPU
	MPU6050_Config(&MPU_init);
}