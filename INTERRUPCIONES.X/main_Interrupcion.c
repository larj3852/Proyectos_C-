/*
 * File:   main_Interrupcion.c
 * Author: Jesus Lara
 * Descriocion: Interrupciones Serial y PORTB
 * Created on 5 de mayo de 2018, 10:33 AM
 */
// BIBLIOTECAS
#include <xc.h>
#include <pic16f887.h>

// BITS DE CONFIGURACIÓN
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits
#pragma config WDTE = OFF       // Watchdog Timer Enable bit
#pragma config PWRTE = ON       // Power-up Timer Enable bit
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit
#pragma config CP = OFF         // Code Protection bit
#pragma config CPD = OFF        // Data Code Protection bit
#pragma config BOREN = ON       // Brown Out Reset Selection bits
#pragma config IESO = ON        // Internal External Switchover bit
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit
#pragma config LVP = OFF        // Low Voltage Programming Enable bit

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits


// VARIABLES
#define delay_ms(x) _delay((unsigned long)((x)*(8000000/4000)))     // 8-MHz
#include "Serial.h"
#define LED RB7
#define BOTON RB3
void setup(void);
//                      INTERRUPCION
static void interrupt isr(void){
    if(RCIF==1){  //Bandera de Interrupcion Activa
        if(usart_read()=='1')
            LED=1;
        if(usart_read()=='0')
            LED=0;
        RCIF=0; //Si no se apaga, se queda ahi
    }
    if(RBIF==1){  //Bandera de Interrupcion POR RB3 Activa
        if(BOTON==1){
            while(BOTON==1);
            LED=!LED;
            RBIF==0;
        }
    }
}

void main(void) {
    setup();
    usart_ini();
    while(1){
        
        PORTC=0B001;
        delay_ms(1000);
        PORTC=0B010;
        delay_ms(1000);
        PORTC=0B100;
        delay_ms(1000);
    }
}

void setup(void){

    OSCCON=0B01111000;          // FOSC 8-MHz
    
    // CONFIGURACIÓN DE PUERTOS
    PORTB=0;
    PORTC=0;
    ANSELH=0;
    TRISB=0B01111111;
    //PAGINA 79
    T0CS=0;     //Tipo de reloj que se va utilizar RELOJ INTERNO
    T0SE=0;     //Como se va realizar el conteo FLANCO ASCENDENTE
    PSA=1;      //Preescala APAGADA
    PS2=0;      
    PS1=0;  
    PS0=0;
    GIE=01;
    T0IE=01;
    TMR0=80;
}