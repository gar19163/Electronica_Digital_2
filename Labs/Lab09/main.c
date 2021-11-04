//**************************************************************************************************************
/*
   File:          Lab09.c
   Dispositivo:   Tiva C TM4123G
   Autor:         Alejandro García Aguirre - 19163
   Compilador:    CCS V10.4

   Programa:      Tiva C en TivaWare
   Hardware:      Push1 - Activa el semáforo
                  RGB como salida
   Creación:      28 de Octubre de 2021
   Entrega:       2 de Noviembre de 2021
*/
//**************************************************************************************************************
// Librerías
//**************************************************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/systick.h"

//**************************************************************************************************************
// Variables Globales
//**************************************************************************************************************
uint32_t i = 0;
uint32_t ui32Period;
//**************************************************************************************************************
// Prototipos de Funciones
//**************************************************************************************************************
void delay(uint32_t msec);
void delay1ms(void);
void Timer0IntHandler(void);
void semaforo(void);
//**************************************************************************************************************
// Función Principal
//**************************************************************************************************************
int main(void){
    // Configuración del oscilador externo, usando PLL y teniendo una frecuencia de 40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
    // Se asigna reloj a puerto F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    // Se establecen como Entradas pin 4 del puerto F como pull-up
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4 , GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    // Se establecen como salidas los pines 1, 2 y 3 del puerto F
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    // Se habilita el reloj para el temporizador
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    // Configuración del Timer 0 como temporizador períodico
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    //Se calcula el período para el temporizador (1 seg)
    ui32Period = (SysCtlClockGet()) / 2;
    // Establecer el periodo del temporizador
    TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period - 1);
    // Se habilita la interrupción por el TIMER0A
    IntEnable(INT_TIMER0A);
    // Se establece que exista la interrupción por Timeout
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    // Se habilitan las interrupciones Globales
    IntMasterEnable();
    // Se habilita el Timer
    TimerEnable(TIMER0_BASE, TIMER_A);
//**********************************************************************************************************
// Loop Principal
//**********************************************************************************************************
   while (1){
        uint8_t valor = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);
        if (valor == 0){
            semaforo();
        }
    }
}
//**************************************************************************************************************
// Función para hacer delay en milisegundos
//**************************************************************************************************************
void delay(uint32_t msec){
    for (i = 0; i < msec; i++){
        delay1ms();
    }
}
//**************************************************************************************************************
// Función para hacer delay de 1 milisegundos
//**************************************************************************************************************
void delay1ms(void){
    SysTickDisable();
    SysTickPeriodSet(16000);
    SysTickEnable();
    while ((NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT) == 0); //Pg. 138
}
//**************************************************************************************************************
// Handler de la interrupción del TIMER 0 - Recordar modificar el archivo tm4c123ght6pm_startup_css.c
//**************************************************************************************************************
void Timer0IntHandler(void){
    // Clear the timer interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    // Read the current state of the GPIO pin and
    // write back the opposite state
    if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1)){
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
    }
    else{
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 2);
    }
}
//**************************************************************************************************************
// Función para semaforo
//**************************************************************************************************************
void semaforo(void){
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
    delay(500);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x08);
    delay(1000);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
    delay(500);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x08);
    delay(500);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
    delay(500);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x08);
    delay(500);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
    delay(500);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x0A);
    delay(1000);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
    delay(500);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x02);
    delay(1000);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
}
