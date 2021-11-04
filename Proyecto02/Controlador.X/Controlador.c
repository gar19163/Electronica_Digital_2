/*
 * Archivo:     lab02.c
 * Dispositivo:	PIC16f887
 * Autor:		Alejandro García Aguirre
 * Compilador:	XC8 (v2.31), MPLABX V5.45
 * 
 * Programa:	LCD y USART 
 * Hardware:    
 *              
 *
 * Created on 20 de agosto de 2021, 07:47 PM
 * Última modificación: 25 de agosto
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
#include "USART.h"
//-------------------------------------------------------
//  Constantes
//-------------------------------------------------------
#define _XTAL_FREQ 8000000  //Delay
//-------------------------------------------------------
//  Variables
//-------------------------------------------------------
char  dig1,dig2; //digito canal
char    op;                 //valor enviado del teclado 
//-------------------------------------------------------
//  Arreglos
//-------------------------------------------------------
char s[30];
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
void main(void){
    
    setup();        //Se llaman a las configuaraciones del PIC
    while (1) {     //Loop
//-------------------USART Menu--------------------------
        dig1 = RB0 + 48;
        dig2 = RB1 + 48;
        op = RCREG;
        __delay_us(100);
        if (op =='h'){
            send_char(dig1);
        }
        if (op =='j'){
            send_char(dig2);
        }
        op = 0;
    }
}
//-------------------------------------------------------
//   Conf PIC
//-------------------------------------------------------
void setup(void){               //Configuraciones del PIC
    //Entradas digitales y analogicas
    ANSEL  = 0x00;                //se utiliza canal 5 y 6
    ANSELH = 0x00;          
    
    //Entradas y Salidas
    TRISB   = 0b00001111;
    TRISCbits.TRISC0= 0;                //Rs
    TRISCbits.TRISC1= 0;                //EN
    TRISCbits.TRISC7= 1;                //RX
    
    //Configuracion del oscilador
    OSCCONbits.IRCF2    = 1;     //8MHZ
    OSCCONbits.IRCF1    = 1;
    OSCCONbits.IRCF0    = 1;
    OSCCONbits.SCS      = 1;     //Oscilador interno
 
    //Config TX y RX
    TXSTAbits.SYNC      = 0;    //Asincrono
    TXSTAbits.BRGH      = 0;    //High Speed 
    BAUDCTLbits.BRG16   = 1;    //usamos 16 bits
    SPBRG              = 51;    //Baud rate
    SPBRGH              = 0;    //9600
    RCSTAbits.SPEN      = 1;    //Enciendo modulo 
    RCSTAbits.RX9       = 0;    //8bits de recepción
    RCSTAbits.CREN      = 1;    //Recepción  
    TXSTAbits.TXEN      = 1;    //Transmisión   
    
    //Configuraciones de interrupciones 
    INTCONbits.GIE      = 1;
    INTCONbits.PEIE     = 1;
    INTCONbits.RBIE     = 1;    //Push Button 
    INTCONbits.RBIF     = 0;
}