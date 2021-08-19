/*
 * Archivo:     lab00.c
 * Dispositivo:	PIC16f887
 * Autor:		Alejandro Garcia Aguirre
 * Compilador:	XC8 (v2.31), MPLABX V5.45
 * 
 * Programa:	Juego de carreras 
 * Hardware:	Push Button PB0-2
 *              
 *              
 *
 * Created on 9 de julio de 2021, 05:31 PM
 * Última modificación:  09 de mayo de 2021
 */

//-------------------------------------------------------
//   Palabras de configuración
//-------------------------------------------------------

// PIC16F887 Configuration Bit Settings
// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
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

//-------------------------------------------------------
//  Constantes
//-------------------------------------------------------
#define _XTAL_FREQ 8000000  //Delay

//-------------------------------------------------------
//  Variables
//-------------------------------------------------------
int j1;
int j2;
int ini;
//-------------------------------------------------------
//  Arreglos
//-------------------------------------------------------
const char tabla[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,  //0,1,2,3,4 
                        0x6D, 0x7D, 0x07, 0x7F, 0x6F}; //5,6,7,8,9
                        
//-------------------------------------------------------
//   Prototipo
//------------------------------------------------------
void setup(void);

//-------------------------------------------------------
//   Interrupciones
//------------------------------------------------------
void __interrupt()isr(void){
    if (RBIF == 1){  //interrupción push button
        if (PORTBbits.RB1 == 0){    //Inicio de Juego
            PORTE = 0x07;           
            if (PORTE != 1)         //Contador de decada
                PORTE--;
        }
        if (PORTBbits.RB1 == 0){    //Contador 1
            PORTD++;
        }
        if (PORTBbits.RB2 == 0){    //Contador 2
            PORTA++;
        }
        INTCONbits.RBIF = 0;        //Bajo bandera de push button
    } 
}
//-------------------------------------------------------
//   Main
//-------------------------------------------------------
void main(void){
    
    setup();       //Se llaman a las configuaraciones del PIC
    while (1) {     //Loop
    j1 = PORTD;
    j2 = PORTA;
    
    }
}
//-------------------------------------------------------
//   Conf PIC
//-------------------------------------------------------
void setup(void){ //Configuraciones del PIC
    
    //Entradas digitales y analogicas
    ANSEL  = 0x00;
    ANSELH = 0x00;
    
    //Entradas y Salidas
    TRISB   = 0x07;         //Entradas-Push Butons
    TRISA   = 0x00;         //salidas - Contador 2
    TRISC   = 0x00;         //7seg
    TRISD   = 0x00;         //Contador 1
    TRISE   = 0x00;         //Semaforo
    
    //Limpiar puertos 
    PORTA = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;
    
    //Configuracion del oscilador
    OSCCONbits.IRCF2    = 1;     //4MHZ
    OSCCONbits.IRCF1    = 1;
    OSCCONbits.IRCF0    = 0;
    OSCCONbits.SCS      = 1;     //Oscilador interno    
    
    //TMR0  
    OPTION_REGbits.T0CS = 0;     //Fosc/4
    OPTION_REGbits.PSA  = 0;     //Prescaler assigned TMR0
    OPTION_REGbits.PS2  = 1;     //1:128
    OPTION_REGbits.PS1  = 1;
    OPTION_REGbits.PS0  = 0;
    TMR0 = 247;

    //Pull-up internos
    OPTION_REGbits.nRBPU = 0;
    WPUBbits.WPUB0 = 1;
    WPUBbits.WPUB1 = 1;
    WPUBbits.WPUB2 = 1;
    IOCBbits.IOCB0 = 1;
    IOCBbits.IOCB1 = 1;
    IOCBbits.IOCB2 = 1;
    
    //Configuraciones de interrupciones 
    INTCONbits.GIE  = 1;    //Int generales 
    INTCONbits.T0IE = 1;    //TMR 0
    INTCONbits.T0IF = 0;
    INTCONbits.RBIE = 1;    //Push Button 
    INTCONbits.RBIF = 0;
}   