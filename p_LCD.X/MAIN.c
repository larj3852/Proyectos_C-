/*
 * File:   Main_Cuna.c
 * Author: Jesús Lara, Berenice Tacuba, Alam Monroy Jesus Banda
 * Description: Codigo Principal de Cuna de Calor Radiante
 * Controller: PIC18F4620
 * Created on 2 de octubre de 2019, 08:42 PM
 */ //Descripcion


/******************************************************************************/
/*                  PIC18F4620 Configuration Bit Settings                     */
/******************************************************************************/


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
#define delay_us(x) _delay((unsigned long)((x)*(8000000/4000000))) //8 MHZ
#include "cabecera_lcd.h"
int i;
unsigned char ADC1;
// FUNCIÓN AUXILIAR
void setup(void);               // CONFIGURACIÓN DE PUERTOS
void ADC_Init(void);
unsigned char ADC_Read(unsigned char channel);
void LCD_MostrarPorcentaje(unsigned char A);

// FUNCIÓN PRINCIPAL
void main(void){
    setup();
    lcd_ini();
    ADC_Init();
    lcd_custom(); //reconocimiento caracteres
    lcd_pos(1,0);  //39 espacios  lcd_pos(x,y) xE(1,2) & yE(0,39)  
    lcd_write_s("Porcentaje: ");
    
    while(1){
        ADC1 = ADC_Read(1);
        lcd_pos(2,0);
        
    }
}


// Inicio de Puertos
void setup(void){

    OSCCON=0B01111000;          // FOSC 8-MHz
    
    // CONFIGURACIÓN DE PUERTOS
    PORTB=0;
    PORTD=0;
    ANSEL=0;
    ANSELH=0;
    TRISB=0;
    TRISD=0;
}

c
}

void LCD_MostrarPorcentaje(unsigned char A){
    int Aux=A/2.5;
    unsigned char C=' ',D=0x30,U=0x30;
    //Centenas
    if(Aux>=100){
        C=Aux/100+48;
        Aux=Aux-Aux/100*100;
        }
    //Decenas
    if(Aux>=10){
        D=Aux/10+48;
        Aux=Aux-Aux/10*10;
    }
    //Unidades
    U=Aux+48;
    
    lcd_pos(2,0); lcd_write_c(C);
    lcd_pos(2,1); lcd_write_c(D);
    lcd_pos(2,2); lcd_write_c(U);
    lcd_pos(1,4);lcd_write_c('%');
    return;
}

////////////////////////////////////////////////////////////////////////////////