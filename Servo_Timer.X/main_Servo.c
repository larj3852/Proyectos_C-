/*
 * File:   main_Servo.c
 * Author: Jesus Lara
 * Descripcion: PWM con timer0 para servomotor
 * Created on 5 de mayo de 2018, 12:23 PM
 */

// BIBLIOTECAS
#include <xc.h>


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
int periodo=200, cont=0, duty=10, i;
    #define servo RD0

void setup(void);

static void interrupt isr(void){
if(T0IF==1){
    TMR0=55; //Fraccion de 100 us
    cont++;
    if(cont>periodo){
        servo=1;
        cont=0;
    }
    if(cont>duty){
        servo=0;
    }
    T0IF=0;
}
    }

void main(void) {
    setup();
    while(1){
        for(i=10;i<=15;i++){
            duty=i;
            delay_ms(50);
        }
        for(i=15;i>=10;i--){
            duty=i;
            delay_ms(50);
        }
    }
}

void setup(void){

    OSCCON=0B01111000;          // FOSC 8-MHz
    
    // CONFIGURACIÓN DE PUERTOS
    PORTD=0;
    ANSELH=0;
    TRISD=0B00000000;
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

