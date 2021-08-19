/*
 * Archivo:     lab03_Master.c
 * Dispositivo:	PIC16f887
 * Autor:		Alejandro Garcia Aguirre
 * Compilador:	XC8 (v2.31), MPLABX V5.45
 * 
 * Programa:	SPI Master 
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
#include "USART.h"
//-------------------------------------------------------
//  Constantes
//-------------------------------------------------------
#define _XTAL_FREQ 8000000
//-------------------------------------------------------
//  Variables
//-------------------------------------------------------
char    ban;
double  val;                //digito canal
char    val1, val2, val3;         //Valor del ADC
char    op;                 //valor enviado del teclado 
//-------------------------------------------------------
//  Arreglos
//-------------------------------------------------------
char s[35];
//-------------------------------------------------------
//   Prototipo
//------------------------------------------------------
void setup(void);

//-------------------------------------------------------
//   Interrupciones
//------------------------------------------------------
void __interrupt()isr(void){   
    if(PIR1bits.RCIF){                  //Interrupción de recepción
        op = RCREG;
    }
}
//-------------------------------------------------------
//   Main
//-------------------------------------------------------
void main(void) {
    setup();
    while(1){
        PORTCbits.RC2 = 0;       //Slave Select
        __delay_ms(1);
//-----------------Recepción-----------------------------       
        spiWrite(ban);
        if (ban==0){
            PORTB = spiRead();
            val1 = PORTD;
            ban = 0;
        }
        else{
            PORTD = spiRead();
            val2 = PORTD;
            ban = 1;
        }                  
        __delay_ms(1);
        PORTCbits.RC2 = 1;       //Slave Deselect
        __delay_ms(1000);
//-------------------USART Recepción--------------------------
         if (op=='+'){
            val3++;
            op = 0;
        }
        else if (op=='-'){
            val3--;
            op = 0;
        }
//-------------------USART Envio--------------------------
        sprintf(s, "Potenciometro 1: %3.0fV\r",val1);//Selecciono texto
        send_str(s);                    //Imprimo Texto
        sprintf(s, "Potenciometro 2: %3.0fV\r",val2);
        send_str(s);
        send_str("Incrmentar(+) para decrementar(-)\r");
        sprintf(s, "Contador: %3.0f",val3);
        send_str(s);
        __delay_ms(500);
        TXREG = '\f';             //Limpio terminal        
    }
    return;
}
//-------------------------------------------------------
//   Conf PIC
//-------------------------------------------------------
void setup(void){
    //Entradas digitales y analogicas
    ANSEL  = 0b00;               
    ANSELH = 0x00;          
    
    //Entradas y Salidas
    TRISC = 0b10000000;
    TRISB = 0;
    TRISD = 0;
    PORTB = 0;
    PORTD = 0;
    TRISCbits.TRISC2 = 1;
    
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
    PIR1bits.RCIF       = 0;     
    PIE1bits.RCIE       = 1;
    
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);

}