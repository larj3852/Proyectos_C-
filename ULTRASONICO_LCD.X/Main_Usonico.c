/*
 * File:   Main_Usonico.c
 * Author: Jesus Lara
 * DESCRIPCIÓN: Medidor distancia con sensor ultrasonico
 * Created on 28 de abril de 2018, 12:44 PM
 */


//                                  BIBLIOTECAS
#include <xc.h>
#include <stdlib.h>
//                                  BITS DE CONFIGURACIÓN
// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

//                 DECLARACION VARIABLES
#define delay_ms(x) _delay((unsigned long)((x)*(8000000/4000)))
#include "LCD_cabecera.h"
#define ECHO RD0
#define TRIG RD1

int cm=0, us=0;
char centi[3];

//                DECLARACION FUNCIONES AUXILIARES
void setup(void);
void distancia(void);

void main(void) {
    setup();
    lcd_ini();
    lcd_pos(0,3);
    lcd_write_s("DISTANCIA");
    while(1){
        distancia();
        itoa(centi,cm,10); // <--- PARA ESTO SE OCUPA STDLIB :v
        lcd_pos(1,5);
        lcd_write_s(centi);
        lcd_write_s("cm ");
        delay_ms(500);
    }
}

void setup(void){
    OSCCON=0B01111000;
    PORTD=0;
    TRISD=0B00000001;   //Pin eco entrada
    T1CON=0B00010000;   //Prescala 1:2 -1 us
}

void distancia(void){
    
    TRIG=1;            //Inicia pulso
    delay_ms(1);        //Retardo
    TRIG=0;             // Termina pulso
    TMR1ON=1;           // Enciende Timer
    while(ECHO==0);     // Espera respuesta
    TMR1=0;             // Reinicia conteo
    
    while((ECHO==1)&&(TMR1<25000));
    TMR1ON=0;           // Apaga timer
    if(TMR1<25000){
        us=(TMR1H*256)+TMR1L;
        cm=us/58;
    }
}