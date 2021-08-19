/*
 * File:   LCD.c
 * Author: Ale
 *
 * Created on 23 de julio de 2021, 01:47 PM
 */

//-------------------------------------------------------
//   Librerias incluidas
//-------------------------------------------------------
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "LCD.h"

//-------------------------------------------------------
//  Constantes
//-------------------------------------------------------
#define _XTAL_FREQ 8000000
#define RS PORTCbits.RC0
#define EN PORTCbits.RC1

//-------------------------------------------------------
//   Funciones
//-------------------------------------------------------
void Lcd_Port(char a) { //Puerto de datos
    PORTA = a;
}

void Lcd_Cmd(char a) {
    RS = 0;
    Lcd_Port(a);
    EN = 1; 
    __delay_ms(4);
    EN = 0; 
}

void Lcd_Clear(void) { //Clear LCD
    Lcd_Cmd(0);
    Lcd_Cmd(1);
}

void Lcd_Set_Cursor(char a, char b) { 
    char temp;
    if (a == 1) {
        temp = 0x80 + b - 1;
        Lcd_Cmd(temp);
    } else if (a == 2) {
        temp = 0xC0 + b - 1;
        Lcd_Cmd(temp);
    }
}

void Lcd_Init(void) { //Inicio
    Lcd_Port(0x00);
    __delay_ms(20);
    Lcd_Cmd(0x3F);
    __delay_ms(10);
    Lcd_Cmd(0x3F);
    __delay_us(200);
    Lcd_Cmd(0x3F);
    Lcd_Cmd(0x38);
    Lcd_Cmd(0x0C);
    Lcd_Cmd(0x06);
}

void Lcd_Write_Char(char a) {
    RS = 1;
    Lcd_Port(a); 
    EN = 1;
    __delay_us(40);
    EN = 0;
    __delay_us(40);
}

void Lcd_Write_String(char *a) {
    int i;
    for (i = 0; a[i] != '\0'; i++)
        Lcd_Write_Char(a[i]);
}