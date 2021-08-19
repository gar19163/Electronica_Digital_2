/*
 * File:   multiplex.c
 * Author: Ale
 *
 */

//-------------------------------------------------------
//   Librerias incluidas
//-------------------------------------------------------
#include <xc.h>
#include <stdio.h>
#include "multiplex.h"

//-------------------------------------------------------
//   Funciones
//-------------------------------------------------------
void display_hex(char val) {
    switch (val){
        case('1'):       
            PORTC = 0x3F;//1
            break;
        case('2'):       
            PORTC = 0x06;//2
            break;
        case('3'):       
            PORTC = 0x5B;//3
            break;
        case('4'):       
            PORTC = 0x4F;//4
            break;
        case('5'):       
            PORTC = 0x66;//5
            break;
        case('6'):       
            PORTC = 0x6D;//6
            break;
        case('7'):       
            PORTC = 0x07;//7
            break;
        case('8'):       
            PORTC = 0x7F;//8
            break;
        case('9'):       
            PORTC = 0x6F;//9
            break;    
        case('10'):       
            PORTC = 0x77;//A
            break;
        case('11'):       
            PORTC = 0x7c;//B
            break; 
        case('12'):       
            PORTC = 0x39;//C
            break;
        case('13'):       
            PORTC = 0x5e;//D
            break; 
        case('14'):       
            PORTC = 0x79;//E
            break; 
        case('15'):       
            PORTC = 0x71;//F
            break; 
    }          
}