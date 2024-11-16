/* 
 * File:   LCD.h
 * Author: usuario
 *
 * Created on 11 de octubre de 2024, 13:42
 */
#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

// Definiciones de pines para el control del LCD
#define RS PORTCbits.RC0  /* PIN 0 de PORTC asignado para el pin RS del LCD */
#define EN PORTCbits.RC1  /* PIN 1 de PORTC asignado para el pin EN del LCD */
#define ldata PORTC       /* PORTC (PC4-PC7) asignado para la salida de datos del LCD */
#define LCD_Port TRISC   /* Define macros para el registro de dirección de PORTC */

// Prototipos de funciones para el manejo del LCD
void LCD_Init(void);                   /* Inicializa el LCD */
void LCD_Command(unsigned char);       /* Envía un comando al LCD */
void LCD_Char(unsigned char x);        /* Envía un carácter al LCD */
void LCD_String(const char*);          /* Muestra una cadena de texto en el LCD */
void LCD_String_xy(char, char, const char*); /* Muestra una cadena en la posición especificada */
void LCD_Clear(void);                  /* Limpia la pantalla del LCD */

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */
