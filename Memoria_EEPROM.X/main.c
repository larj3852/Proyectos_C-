/*
 * File:   main.c
 * Author: Jesus Lara
 * Descripcion: Manejo de memoria EEPROM en Pic. Corrimiento de LEDs.
 * Created on 21 de abril de 2018, 09:27 AM
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

//                 DECLARACION VARIABLES
int contador=0;
//                DECLARACION FUNCIONES AUXILIARES
void setup(void);

void main(void) {
    setup();
    PORTA = eeprom_read(0);
    contador = eeprom_read(1); //contador es igual al valor que tenga la memoria en 1
    if(contador>3){
        PORTA=1;  //La eeprom tiene 255 como valor por default por lo cual es importante reiniciar el cont
        contador=0;
    }
    while(1){
        if (RA7==1){
            while (RA7==1){}
            PORTA=PORTA<<1; //corrimiento a la izquierda
            contador++;
            eeprom_write(0,PORTA);
            eeprom_write(1,contador);
            if(contador>3){
                PORTA=1;
                contador=0;
            }
        }   
    }
    
}

void setup(void) {
    
    OSCCON = 0B01111000; //Oscilador 8MHz datasheet pag 66
    PORTA=0;//Limpiar estados
    ANSEL=0;
    TRISA=0B11110000; 
    
}