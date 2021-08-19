/*
 * File:   USART.c
 * Author: Ale
 *
 * Created on 23 de julio de 2021, 05:11 PM
 */


//-------------------------------------------------------
//   Librerias incluidas
//-------------------------------------------------------
#include <xc.h>
#include "USART.h"

//-------------------------------------------------------
//  Constantes
//-------------------------------------------------------
#define _XTAL_FREQ 8000000
//-------------------------------------------------------
//   Funciones
//-------------------------------------------------------
void send_char (char dato){
    while(!TXIF);           //Transmisión
    TXREG = dato;       //Muestro caracter
}

void send_str(char st[]){
    int i = 0;              
    while (st[i] != 0){
        send_char(st[i]);
        i++; 
        __delay_us(30);
    }
}
    