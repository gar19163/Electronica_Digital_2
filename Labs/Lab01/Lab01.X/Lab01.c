/*
 * Archivo:     lab01.c
 * Dispositivo:	PIC16f887
 * Autor:		Alejandro Garcia Aguirre
 * Compilador:	XC8 (v2.31), MPLABX V5.45
 * 
 * Programa:	Interrupciones y uso de Librerias 
 * Hardware:	Push ButtoN         PB0-2
 *              Portenciometro      PE0
 *              Contador LEDs       PA0-7
 *              7semg datos         PC0-7
 *              Selector 7segm      PD0-1
 *              Alarma              PD5
 *
 * Created on 13 de julio de 2021, 07:47 PM
 * Última modificación: 
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
#include "ADC.h"
#include "multiplex.h"

//-------------------------------------------------------
//  Constantes
//-------------------------------------------------------
#define _XTAL_FREQ 8000000  //Delay

//-------------------------------------------------------
//  Variables
//-------------------------------------------------------
char    dig;    //Valor del ADC
char    val;    //Valor del ADC
char    segm;   //Selección de 7segm
char    seg1;   //Valor 7segm MSB
char    seg2;   //Valor 7segm LSB
//-------------------------------------------------------
//  Arreglos
//-------------------------------------------------------

//-------------------------------------------------------
//   Prototipo
//-------------------------------------------------------
void setup(void);
char ADC(char dig);
void display_hex(char val);
//-------------------------------------------------------
//   Interrupciones
//------------------------------------------------------
void __interrupt()isr(void){
    if (RBIF == 1){  //interrupción push button
        if (PORTBbits.RB0 == 0){    //Incremento
            PORTA++;
        }
        if (PORTBbits.RB1 == 0){    //Decrenento
            PORTA--;
        }
        INTCONbits.RBIF = 0;        //Bajo bandera de push button
    }                               //Cerramos int de push button
    
//    if (T0IF==1){                   //Multiplexeo 
//        INTCONbits.T0IF = 0;        //Bajar bandera TMR0
//        TMR0 = 247;                 //Reset TMR0        
//        TRISEbits.TRISE1 = 0;   
//        TRISEbits.TRISE2 = 0;       //Limpio puerto
//        
//        if (segm==0){               //MSB
//            display_hex(seg1);      //Despliego valor al display
//            TRISEbits.TRISE1 = 1;   //Enciendo pin 1
//            TRISEbits.TRISE2 = 0;   //Apago pin 0
//            segm = 1;               //Cambio a unidad
//        }
//        else if (segm==1){          //LSB
//            display_hex(seg1);      //Despliego valor al display
//            TRISEbits.TRISE1 = 0;   //Apago pin 1
//            TRISEbits.TRISE2 = 1;   //Enciendo pin 0
//            segm = 0;               //Cambio a decena
//        }
//    }
}
//-------------------------------------------------------
//   Main
//-------------------------------------------------------
void main(void){
    
    setup();        //Se llaman a las configuaraciones del PIC
    ADCON0bits.GO   = 1;    //Inicio ADC
    while (1) {     //Loop
        //-----------------ADC---------------------------
        if(ADCON0bits.GO == 0){         //Cambio de canal
            if(ADCON0bits.CHS == 5)    //Canal 5 
                val = ADC(dig);      //Muevo el valor a PORTA
                PORTD = ADC(dig);      //Muevo el valor a PORTA
            __delay_ms(50);             //Delay
            ADCON0bits.GO = 1;          //GO
        }
        //----------------Conversion---------------------
        if (val>=16){         //
            seg2 = val/16;
            seg1 = val-(seg1*16);
        }
        else if (val < 16){
            seg1 = val;
            seg2 = 0;       
        }
        //--------------Alarma---------------------------
        if (val==PORTA)
            TRISEbits.TRISE3 = 1;
        else
            TRISEbits.TRISE3 = 0;
    }
}
//-------------------------------------------------------
//   Conf PIC
//-------------------------------------------------------
void setup(void){ //Configuraciones del PIC
    
    //Entradas digitales y analogicas
    ANSEL  = 0b00100000;     //se utiliza canal 5
    ANSELH = 0x00; 
    
    //Entradas y Salidas
    TRISBbits.TRISB0=1;         //push Butons
    TRISBbits.TRISB1=1;         //push Butons
    TRISE   = 0x01;         //Canal para potencimietro
    
    TRISA   = 0x00;         //salidas - Contador Push Button
    TRISC   = 0x00;         //7seg
    TRISD   = 0x00;         //Contador de ADC
    
    //Limpiar puertos 
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    
    //Configuracion del oscilador
    OSCCONbits.IRCF2    = 1;     //4MHZ
    OSCCONbits.IRCF1    = 1;
    OSCCONbits.IRCF0    = 0;
    OSCCONbits.SCS      = 1;     //Oscilador interno
    
    //Configuracion del ADC
    ADCON1bits.ADFM     = 0;     //Justificación a la izquierda
    ADCON1bits.VCFG0    = 0;     //Voltaje de referencia VSS
    ADCON1bits.VCFG1    = 0;     //VDD
    ADCON0bits.ADCS     = 1;     //Fosc/8
    ADCON0bits.CHS      = 5;    //Canal 5
    __delay_us(100);
    ADCON0bits.ADON     = 1;    //Encender modulo
    
    //TMR0
//    OPTION_REGbits.T0CS = 0;     //Fosc/4
//    OPTION_REGbits.PSA  = 0;     //Prescaler assigned TMR0
//    OPTION_REGbits.PS2  = 1;     //1:128
//    OPTION_REGbits.PS1  = 1;
//    OPTION_REGbits.PS0  = 0;
//    TMR0 = 247;                  //2ms
    
    //Configuraciones de interrupciones 
    INTCONbits.GIE  = 1;    //Int generales 
    INTCONbits.PEIE = 1;
    INTCONbits.RBIE = 1;    //Push Button 
    INTCONbits.RBIF = 0;
//    INTCONbits.T0IE = 1;    //TMR 0
//    INTCONbits.T0IF = 0;
}

//-------------------------------------------------------
//   Funciones
//-------------------------------------------------------
