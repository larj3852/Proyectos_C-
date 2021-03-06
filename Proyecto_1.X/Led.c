/*
 * File:   Led.c
 * Author: Jesus Lara
 *
 * Created on 24 de marzo de 2018, 11:49 AM
 * 
 * DESCRIPICON: Encendido y Apagado de un LED
 */

//                                  BIBLIOTECAS
#include <xc.h>
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

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


//                              VARIABLES
#define delay_ms(x) _delay((unsigned long)((x)*(8000000/4000))) //x--> Letra arbitraria
#define LED RC0

void main(void) {
    
    OSCCON = 0B01111000; //Oscilador 8MHz datasheet pag 66
    PORTC=0; //Limpiar estados
    TRISC=0B11111110; //RC0 --> Salida  TRISC0=0;
    while(1){
        LED=!LED; //ESTADO CONTRARIO
        delay_ms(500);//Retardo
        /*LED=1;
        delay_ms(500);
        LED=0;
        delay_ms(500); */
    }
     
}
