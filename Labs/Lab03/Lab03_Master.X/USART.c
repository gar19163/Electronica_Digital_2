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
#include <stdint.h>
#include <pic16f887.h>
#include <xc.h>
#include <string.h>
#include <stdlib.h>
#include<stdbool.h>
#include <stdio.h>
//-------------------------------------------------------
//  Constantes
//-------------------------------------------------------
#define _XTAL_FREQ 8000000
//-------------------------------------------------------
//   Funciones
//-------------------------------------------------------
void send_char (unsigned char dato){
    TXREG = dato;       //Muestro caracter
    while(!TXIF);           //Transmisión
}

void send_str(char st[]){
    int i = 0;              
    while (st[i] != 0){
        send_char(st[i]);
        i++; 
        __delay_us(30);
    }
}
    