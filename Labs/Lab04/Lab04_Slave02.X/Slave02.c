/*
 * File:        Lab04_Slave02.c
 * Dispositivo:	PIC16f887
 * Autor:		Alejandro García Aguirre
 * Compilador:	XC8 (v2.31), MPLABX V5.50
 * 
 * Programa:	I2C 
 * Hardware:
 *
 * Created on 6 de agosto de 2021, 12:55 AM
 */

//-------------------------------------------------------
//   Palabras de configuración
//-------------------------------------------------------

// PIC16F887 Configuration Bit Settings
// 'C' source line config statements

// CONFIG1
#pragma config FOSC = EXTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
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
char    c;
uint8_t z;
uint8_t dato;
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
void __interrupt() isr(void){
    if(PIR1bits.SSPIF == 1){            //interrupcion del I2C

        SSPCONbits.CKP = 0;
       
        if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL)){
            z = SSPBUF;                 // Read the previous value to clear the buffer
            SSPCONbits.SSPOV = 0;       // Clear the overflow flag
            SSPCONbits.WCOL = 0;        // Clear the collision bit
            SSPCONbits.CKP = 1;         // Enables SCL (Clock)
        }

        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) {
            __delay_us(7);
            z = SSPBUF;                 // Lectura del SSBUF para limpiar el buffer y la bandera BF
            __delay_us(2);
            PIR1bits.SSPIF = 0;         // Limpia bandera de interrupción recepción/transmisión SSP
            SSPCONbits.CKP = 1;         // Habilita entrada de pulsos de reloj SCL
            while(!SSPSTATbits.BF);     // Esperar a que la recepción se complete
            c = SSPBUF;                 // Guardar en variable el valor del buffer de recepción
            __delay_us(250);
            }
        else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){
            z = SSPBUF;
            BF = 0;
            SSPBUF = PORTD;
            SSPCONbits.CKP = 1;
            __delay_us(250);
            while(SSPSTATbits.BF);
        }
       
        PIR1bits.SSPIF = 0;    
    }
    
    if (RBIF == 1){                 //interrupción push button
        if (PORTBbits.RB0 == 0){    //Incremento
            PORTD++;
        }
        if (PORTBbits.RB1 == 0){    //Decrenento
            PORTD--;
        }
        INTCONbits.RBIF = 0;        //Bajo bandera de push button
    }                               //Cerramos int de push button
}
//-------------------------------------------------------
//   Main
//-------------------------------------------------------
void main(void) {
    setup();                            //Llamo las configuracione
    while(1){
    }
}
//-------------------------------------------------------
//   Conf PIC
//-------------------------------------------------------
void setup(void){                       //Configuraciones del PIC
//    Entradas digitales y analogicas
    ANSEL  = 0x00;                      //Canal 0      
    ANSELH = 0x00;          
    
//    Entradas y Salidas
    TRISB   = 0x03;                     //Push button
    TRISD   = 0x00;                     //Contador de push
    PORTD   = 0x00;                     //Limpio puerto

//    Pull-up internos
    OPTION_REGbits.nRBPU = 0;
    WPUBbits.WPUB0 = 1;
    WPUBbits.WPUB1 = 1;
    IOCBbits.IOCB0 = 1;
    IOCBbits.IOCB1 = 1;
    
//    Configuraciones de interrupciones 
    INTCONbits.GIE  = 1;    //Int generales 
    INTCONbits.RBIE = 1;    //Push Button 
    INTCONbits.RBIF = 0;
    
    I2C_Slave_Init(0x60);
}