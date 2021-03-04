/*
 * File:   main_Carrito.c
 * Author: Jesus Lara
 *
 * Created on 6 de mayo de 2018, 03:42 PM
 */

// BIBLIOTECAS
#include <xc.h>


// BITS DE CONFIGURACIÓN
// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
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

/*                     DECLARAR/ DEFINIR VARIABLES                            */
#define delay_ms(x) _delay((unsigned long)((x)*(8000000/4000)))     // 8-MHz
#include "Serial.h"
char CH=' ';

/*                      DECLARAR FUNCIONES AUXILIARES                         */
void setup(void);

void main(void) {
    setup();
    usart_ini();
    delay_ms(100);
    while(1){
        
            if(UART_Data_Ready()){
                CH=usart_read();
                usart_write_c(CH);
                switch(CH){
                    case '1':  //PA DELANTE
                        PORTD=0B00000001;
                        delay_ms(8000);
                        PORTD=0B00000000;
                        break;
                    case '2':  //PA TRAS
                        PORTD=0B00000010;
                        delay_ms(8000);
                        PORTD=0B00000000;
                        break;
                    case '3':  //PA LA DERECHA
                        PORTD=0B00000100;
                        while( RD4==0);    //Espera hasta que de la vuelta
                        delay_ms(2000);//Vuelta hasta el tope
                        PORTD=0B00000001; //Activa tracción                              
                        delay_ms(8000);   //Dar la vuelta
                        PORTD=0B00001000;
                        delay_ms(200);      //Regresar llantas en frente
                        PORTD=0B00000000; //Apagar
                        break;
                    case '4': //PA LA IZQUIERDA
                        PORTD=0B00001000;
                        while(RD5==0 );     //Espera hasta que de la vuelta
                        delay_ms(3000);     //Vuelta hasta el tope
                        PORTD=0B00000001;   //Activa tracción                         
                        delay_ms(8000);      //Dar la vuelta
                        PORTD=0B00000100;   //Regresar llantas en frente
                        delay_ms(200);  
                        PORTD=0B00000000;   //Apagar
                        break;
                    }
            }
            
        }
    
}

void setup(void){
    OSCCON=0B01111000;          // FOSC 8-MHz
    // CONFIGURACIÓN DE PUERTOS
    PORTD=0;
    ANSELH=0;
    ANSEL=0;
    TRISD=0B00110000;   
}