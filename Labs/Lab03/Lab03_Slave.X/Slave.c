/*
 * Archivo:     lab03.c
 * Dispositivo:	PIC16f887
 * Autor:		Alejandro Garcia Aguirre
 * Compilador:	XC8 (v2.31), MPLABX V5.45
 * 
 * Programa:	SPI Slave 
 * Hardware:	
 *              
 *              
 *              
 *              
 *
 * Created on 13 de julio de 2021, 07:47 PM
 * Última modificación: 
 */
//-------------------------------------------------------
//   Palabras de configuración
//-------------------------------------------------------
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
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//-------------------------------------------------------
//   Librerias incluidas
//-------------------------------------------------------
#include <xc.h>
#include <stdint.h>
#include "SPI.h"
#include "ADC.h"
//-------------------------------------------------------
//  Constantes
//-------------------------------------------------------
#define _XTAL_FREQ 8000000

uint8_t temporal = 0;
//-------------------------------------------------------
//  Variables
//-------------------------------------------------------
char    dig;             //Variable del ADC
char    ban;             //Bandera lectura de canal
char    val;             //Valor del ADC
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
void __interrupt() isr(void){
   if(SSPIF == 1){
        ban = spiRead();
        spiWrite(val);
        SSPIF = 0;
    }
}
//-------------------------------------------------------
//   Main
//-------------------------------------------------------
void main(void) {
    setup();
    while(1){
//-----------------Canal ADC-----------------------------
        if(ADCON0bits.GO == 0){         //Cambio de canal
            if(ADCON0bits.CHS == 5 /*& ban == 0*/){    //Canal 5
                ADCON0bits.CHS = 6;     //Cambio a canal 6  
                val = ADC(dig);        //Muevo el valor a otra variable
                PORTB = ADC(dig);        //Muevo el valor a Puerto
            }
            else if (ADCON0bits.CHS == 6 /*& ban == 1*/){       //Canal 6
                ADCON0bits.CHS = 5;     //Cambio a canal 5  
                val = ADC(dig);         //Muevo el valor a otra variable
                PORTD = ADC(dig);       //Muevo el valor a Puerto
            }
            ban = 0;                    //Bajo bandera
            __delay_ms(50);             //Delay
            ADCON0bits.GO = 1;          //GO
        }
        
       
       __delay_ms(1000);    //Delay de comunicación
    }
    return;
}
//-------------------------------------------------------
//   Conf PIC
//-------------------------------------------------------
void setup(void){
    //Entradas digitales y analogicas
    ANSEL  = 0b01100000;                //se utiliza canal 5 y 6
    ANSELH = 0x00;          
    
    //Entradas y Salidas    
    TRISB = 0x00;
    TRISD = 0x00;
    TRISE = 0x03;
    //Limpio puertos
    PORTB = 0;
    PORTD = 0;
    
    //Configuracion del ADC
    ADCON1bits.ADFM     = 0;            //Justificación a la izquierda
    ADCON1bits.VCFG0    = 0;            //Voltaje de referencia VSS
    ADCON1bits.VCFG1    = 0;            //VDD
    ADCON0bits.ADCS     = 1;            //Fosc/8
    ADCON0bits.CHS      = 5;            //Canal 5
    __delay_us(100);
    ADCON0bits.ADCS     = 1;            // Clock selection
    ADCON0bits.ADON     = 1;            //Encender modulo
    
    //Configuraciones de interrupciones 
    INTCONbits.GIE = 1;         // Habilitamos interrupciones
    INTCONbits.PEIE = 1;        // Habilitamos interrupciones PEIE
    PIR1bits.SSPIF = 0;         // Borramos bandera interrupción MSSP
    PIE1bits.SSPIE = 1;         // Habilitamos interrupción MSSP
    TRISAbits.TRISA5 = 1;       // Slave Select
    
    //Configuracion del SPI
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
   
}