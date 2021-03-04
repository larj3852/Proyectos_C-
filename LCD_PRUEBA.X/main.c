
////////////////////////////////////////////////////////////////////////////////
//+                                                                          +//
// +                         PLANTILLA PIC16F887                            + //
//+                                                                          +//
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// AUTOR:                                                                     //
//                                                                            //
// FECHA:                                                                     //
//                                                                            //
// PIC UTILIZADO: PIC16F887                                                   //
//                                                                            //
// DESCRIPCIÓN:                                                               //
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
#include "LCD_header.h"
int i;
// FUNCIÓN AUXILIAR
void setup(void);               // CONFIGURACIÓN DE PUERTOS



// FUNCIÓN PRINCIPAL
void main(void){

    setup();
    lcd_ini();
    lcd_custom(); //reconocimiento caracteres
    lcd_pos(1,0);  //39 espacios  lcd_pos(x,y) xE(1,2) & yE(0,39)  
    //lcd_write_s("Hola");
    lcd_pos(1,5);
    lcd_write_s("Hola mundo");
    lcd_pos(1,0);
    while (1) {
        lcd_pos(1,0);
        for(i=0;i<=15;i++){
            
        lcd_write_c(CG1);
        lcd_cmd(CURSOR_LEF);
        delay_ms(200);
        lcd_write_c(CG2);
        lcd_cmd(CURSOR_LEF);
        delay_ms(200);
        lcd_write_c(' ');
        }
    lcd_pos(1,5);
    lcd_write_s("Hola mundo");
    }
    
    return;
}


// FUNCIÓN AUXILIAR
void setup(void){
    OSCCON=0B01110000;          // FOSC 8-MHz
    
    // CONFIGURACIÓN DE PUERTOS
    TRISD=0;
    PORTD=0;
    ANSELH=0;
   
}

////////////////////////////////////////////////////////////////////////////////