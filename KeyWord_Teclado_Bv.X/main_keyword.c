
////////////////////////////////////////////////////////////////////////////////
//+                                                                          +//
// +                         PLANTILLA PIC16F887                            + //
//+                                                                          +//
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// AUTOR: HECTOR AMADOR                                                       //
//                                                                            //
// FECHA: 05/05/18                                                            //
//                                                                            //
// PIC UTILIZADO: PIC16F887                                                   //
//                                                                            //
// DESCRIPCIÓN: TECLADO MATRICIAL CON COMUNICACIÓN SERIAL                     //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

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

// FUNCIÓN AUXILIAR
void setup(void);               // CONFIGURACIÓN DE PUERTOS
void key(void);

// INTERRUPCIÓN
static void interrupt isr(void){

    // USO OPCIONAL
}


// FUNCIÓN PRINCIPAL
void main(void){
    
    setup();
    usart_ini();
    while(1){
    
        key();
        delay_ms(250);
        // ESCRIBE TU CÓDIGO AQUÍ
    }
    return;
}


// FUNCIÓN AUXILIAR
void setup(void){

    OSCCON=0B01111000;          // FOSC 8-MHz
    
    // CONFIGURACIÓN DE PUERTOS
    PORTB=0;
    PORTC=0;
    ANSELH=0;
    TRISB=0B00001111;
    TRISC=255;
}

void key(void)
{
 PORTB=128;
 if(RB3==1)
     usart_write_c('1');
 if(RB2==1)
     usart_write_c('2');
 if(RB1==1)
     usart_write_c('3');
 if(RB0==1)
     usart_write_c('A');

 PORTB=64;
 if(RB3==1)
     usart_write_c('4');
 if(RB2==1)
     usart_write_c('5');
 if(RB1==1)
     usart_write_c('6');
 if(RB0==1)
     usart_write_c('B');

  PORTB=32;
 if(RB3==1)
     usart_write_c('7');
 if(RB2==1)
     usart_write_c('8');
 if(RB1==1)
     usart_write_c('9');
 if(RB0==1)
     usart_write_c('C');

   PORTB=16;
 if(RB3==1)
     usart_write_c('*');
 if(RB2==1)
     usart_write_c('0');
 if(RB1==1)
     usart_write_c('#');
 if(RB0==1)
     usart_write_c('D');

}

////////////////////////////////////////////////////////////////////////////////