
/*
 * Archivo:     lab05.c
 * Dispositivo:	PIC16f887
 * Autor:		Alejandro García Aguirre
 * Compilador:	XC8 (v2.31), MPLABX V5.50
 * 
 * Programa:	PIC & ADAFRUIT IO
 * Hardware:    PUSH BUTTON             B0-1              
 *              USART                   C6-7
 *              LEDs Contador           D0-7
 *              
 *
 * Created on 13 de agosto de 2021, 12:20 AM
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
#include "USART.h"

//-------------------------------------------------------
//  Constantes
//-------------------------------------------------------
#define _XTAL_FREQ 8000000  //Delay

//-------------------------------------------------------
//  Variables
//-------------------------------------------------------
char  dig1,dig2; //digito de contadores
float val1, val2;
//-------------------------------------------------------
//  Arreglos
//-------------------------------------------------------
char s[30];
//-------------------------------------------------------
//   Prototipo
//------------------------------------------------------
void setup(void);
void send_str(char st[]);
//-------------------------------------------------------
//   Interrupciones
//------------------------------------------------------
void __interrupt()isr(void){   
    if (RBIF == 1){                 //interrupción push button
        if (PORTBbits.RB0 == 0){    //Incremento
            dig1++;
        }
        if (PORTBbits.RB1 == 0){    //Decrenento
           dig1--;
        }
        INTCONbits.RBIF = 0;        //Bajo bandera de push button
    }                               //Cerramos int de push button
    if(PIR1bits.RCIF){              //Interrupción de recepción
        dig2 = RCREG;
    }
}
//-------------------------------------------------------
//   Main
//-------------------------------------------------------
void main(void) {
    setup();                            //Llamo las configuraciones 
    while(1){
//-------------------USART Contador----------------------
        PORTD = dig2;                     //Muestro el valor USART en PUERTOD
        PORTA = dig1;                     //Muestro el valor USART en PUERTOA
        val1 = dig1;                     //
        val2 = dig2;                     //
//-------------------USART Menu--------------------------
        sprintf(s, "%0.0f",val1);//Selecciono texto
        send_str(s);                    //Imprimo Texto
        
        __delay_ms(500);
        TXREG = ',';             //Limpio terminal  
    }
}
//-------------------------------------------------------
//   Conf PIC
//-------------------------------------------------------
void setup(void){               //Configuraciones del PIC
    //Entradas digitales y analogicas
    ANSEL  = 0x00;               //
    ANSELH = 0x00;          
    
    //Entradas y Salidas
    TRISB   = 0x03;             //Canales de potenciometros
    TRISD   = 0x00;             //salidas D0-7 del LCD
    TRISA   = 0x00;             //salidas D0-7 del LCD
    TRISCbits.TRISC7= 1;        //RX 
    
        //Configuracion del oscilador
    OSCCONbits.IRCF2    = 1;     //8MHZ
    OSCCONbits.IRCF1    = 1;
    OSCCONbits.IRCF0    = 1;
    OSCCONbits.SCS      = 1;     //Oscilador interno

    //Pull-up internos
    OPTION_REGbits.nRBPU = 0;
    WPUBbits.WPUB0 = 1;
    WPUBbits.WPUB1 = 1;
    IOCBbits.IOCB0 = 1;
    IOCBbits.IOCB1 = 1;    
    
    //Config TX y RX
    TXSTAbits.SYNC      = 0;    //Asincrono
    TXSTAbits.BRGH      = 0;    //High Speed 
    BAUDCTLbits.BRG16   = 1;    //usamos 16 bits
    SPBRG              = 51;    //Baud rate
    SPBRGH              = 0;    //9600
    RCSTAbits.SPEN      = 1;    //Enciendo modulo 
    RCSTAbits.RX9       = 0;    //8bits de recepción
    RCSTAbits.CREN      = 1;    //Recepción  
    TXSTAbits.TXEN      = 1;    //TRansmisión   
    
    //Configuraciones de interrupciones 
    INTCONbits.GIE      = 1;
    INTCONbits.PEIE     = 1;
    INTCONbits.RBIE     = 1;    //Push Button 
    INTCONbits.RBIF     = 0;
    PIR1bits.RCIF       = 0;    //UART     
    PIE1bits.RCIE       = 1;
}
//-------------------------------------------------------
//   Funciones
//-------------------------------------------------------