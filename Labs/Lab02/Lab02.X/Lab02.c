/*
 * Archivo:     lab02.c
 * Dispositivo:	PIC16f887
 * Autor:		Alejandro García Aguirre
 * Compilador:	XC8 (v2.31), MPLABX V5.45
 * 
 * Programa:	LCD y USART 
 * Hardware:    Envio de datos a LCD    A0-7
 *              Lectura LCD             C0-1
 *              USART                   C6-7
 *              Potenciometros ADC      E0-1
 *              
 *
 * Created on 22 de julio de 2021, 07:47 PM
 * Última modificación: 25 de julio
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
#include "LCD.h"
#include "USART.h"

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
char s[30];
//-------------------------------------------------------
//   Prototipo
//------------------------------------------------------
void setup(void);
void send_char (char dato);
void send_str(char st[]);
char ADC(char dig);
void Lcd_Cmd(char a);
void Lcd_Set_Cursor(char a, char b);
void Lcd_Init(void);
void Lcd_Write_String(char *a);
void Lcd_Clear(void);
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
    setup();                            //Llamo las configuraciones
    Lcd_Init();                         //Inicio el LCD
    Lcd_Clear();                        //Limpio el LCD   
    while(1){
        if (op=='+'){
            dig3++;
            op = 0;
        }
        else if (op=='-'){
            dig3--;
            op = 0;
        }
//-----------------Canal ADC-----------------------------
        if(ADCON0bits.GO == 0){         //Cambio de canal
            if(ADCON0bits.CHS == 5){    //Canal 5
                ADCON0bits.CHS = 6;     //Cambio a canal 6  
                val1 = ADC(dig);        //Muevo el valor a otra variable
            }
            else{                        //Canal 6
                ADCON0bits.CHS = 5;      //Cambio a canal 5  
                val2 = ADC(dig);         //Muevo el valor a otra variable
            }
            __delay_ms(50);             //Delay
            ADCON0bits.GO = 1;          //GO
        }
//-----------------LCD-----------------------------------        
        Lcd_Set_Cursor(1,1);            //Columna 1 fila 1
        Lcd_Write_String("S1:   S2:   S3:");//Imprimo texto
        
        //--------Pot1-----------------------------------
        dig1 = val1*0.0196;             //Convieto valor
        Lcd_Set_Cursor(2,1);            //Columna 7 fila 2
        sprintf(s,"%3.2fV",dig1);       //Selección de texto 
        Lcd_Write_String(s);            //Envio texto 
        //--------Pot2-----------------------------------
        dig2 = val2*0.0196;             //Convieto valor
        Lcd_Set_Cursor(2,7);            //Columna 1 fila 2
        sprintf(s,"%3.2fV",dig2);       //Selección de texto 
        Lcd_Write_String(s);            //Envio texto 
        //--------Contador-------------------------------
        sprintf(s,"%3.0f",dig3);       //Selección de texto 
        Lcd_Write_String(s);            //Envio texto 
//-------------------USART Menu--------------------------
        sprintf(s, "S1: %3.2fV\r",dig1);//Selecciono texto
        send_str(s);                    //Imprimo Texto
        sprintf(s, "S2: %3.2fV\r",dig2);
        send_str(s);
        send_str("Incrmentar(+) para decrementar(-)\r");
        sprintf(s, "S3: %3.0f",dig3);
        send_str(s);
        __delay_ms(500);
        TXREG = '\f';             //Limpio terminal        
    }
}
//-------------------------------------------------------
//   Conf PIC
//-------------------------------------------------------
void setup(void){               //Configuraciones del PIC
    //Entradas digitales y analogicas
    ANSEL  = 0b01100000;                //se utiliza canal 5 y 6
    ANSELH = 0x00;          
    
    //Entradas y Salidas
    TRISE   = 0b111;                    //Canales de potenciometros
    TRISA   = 0x00;                     //salidas D0-7 del LCD
    TRISCbits.TRISC0= 0;                //Rs
    TRISCbits.TRISC1= 0;                //EN
    TRISCbits.TRISC7= 1;                //RX
    
    //Configuracion del oscilador
    OSCCONbits.IRCF2    = 1;     //8MHZ
    OSCCONbits.IRCF1    = 1;
    OSCCONbits.IRCF0    = 1;
    OSCCONbits.SCS      = 1;     //Oscilador interno
    
    //Configuracion del ADC
    ADCON1bits.ADFM     = 0;            //Justificación a la izquierda
    ADCON1bits.VCFG0    = 0;            //Voltaje de referencia VSS
    ADCON1bits.VCFG1    = 0;            //VDD
    ADCON0bits.ADCS     = 1;            //Fosc/8
    ADCON0bits.CHS      = 5;            //Canal 5
    __delay_us(100);
    ADCON0bits.ADCS     = 1;            // Clock selection
    ADCON0bits.ADON     = 1;            //Encender modulo
    
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
}