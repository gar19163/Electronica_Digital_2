/*
 * Archivo:     lab04_Master.c
 * Dispositivo:	PIC16f887
 * Autor:		Alejandro García Aguirre
 * Compilador:	XC8 (v2.31), MPLABX V5.50
 * 
 * Programa:	I2C 
 * Hardware:
 *
 * Created on 6 de agosto de 2021, 12:45 AM
 */


//-------------------------------------------------------
//   Palabras de configuración
//-------------------------------------------------------

// PIC16F887 Configuration Bit Settings
// 'C' source line config statements

// CONFIG1
#pragma config FOSC = EXTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

//-------------------------------------------------------
//   Librerias incluidas
//-------------------------------------------------------
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "I2C.h"

//-------------------------------------------------------
//  Constantes
//-------------------------------------------------------
#define _XTAL_FREQ 8000000  //Delay

//-------------------------------------------------------
//  Variables
//-------------------------------------------------------
char    dig;
double  dig1,dig2, dig3; //digito canal
char    val1, val2;         //Valor del ADC
char    op;                 //valor enviado del teclado 
//-------------------------------------------------------
//  Arreglos
//-------------------------------------------------------

//-------------------------------------------------------
//   Prototipo
//------------------------------------------------------
void setup(void);

//-------------------------------------------------------
//   Interrupciones
//------------------------------------------------------
void __interrupt()isr(void){   

}
//-------------------------------------------------------
//   Main
//-------------------------------------------------------
void main(void) {
    setup();                            //Llamo las configuraciones  
    while(1){

//-----------------I2C-----------------------------
        I2C_Master_Start();
        I2C_Master_Write(0x50);
        I2C_Master_Write(PORTB);
        I2C_Master_Stop();
        __delay_ms(200);
       
        I2C_Master_Start();
        I2C_Master_Write(0x51);
        PORTD = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(200);
    }
}
//-------------------------------------------------------
//   Conf PIC
//-------------------------------------------------------
void setup(void){               //Configuraciones del PIC
    //Entradas digitales y analogicas
    ANSEL  = 0b00;                
    ANSELH = 0x00;          
    
    //Entradas y Salidas
    TRISB   = 0x00;                     //Contador de ADC
    PORTB   = 0x00;                     //Limpio puerto    
    TRISD   = 0x00;                     //Recepción de Slave1
    PORTD   = 0x00;                     //Limpio puerto
    
    I2C_Master_Init(100000);        // Inicializar Comuncación I2C
}