/*
 * File:   newmain.c
 * Author: Jesus Lara
 *
 * Created on 12 de mayo de 2018, 11:50 PM
 */
/*--------------------------- LIBRERIAS --------------------------------------*/
#include <xc.h>
/*------------------------- BITS CONFIGURACION -------------------------------*/
// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection (HS Oscillator, High-speed crystal/resonator connected between OSC1 and OSC2 pins)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = ON    // Clock Out Enable (CLKOUT function is enabled on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

/*--------------------------- DEFINICIONES -----------------------------------*/
#include "Serial.h"
#define delay_ms(x) _delay((unsigned long)x*(20000000/20000))
char CH;
/*---------------------- INICIALIZAR FUNCIONES ------------------------------*/
void setup(void);


void main(void) {
    setup();
    usart_init();
    delay_ms(100);
    while(1){
        if(UART_Data_Ready()){
            CH=usart_read();
            usart_write_c(CH);
        }
    }
}

void setup(void){
    OSCCON = 0B01110000;
    ANSELA = 0B00000000;
    ANSELB = 0B00000000;
    TRISA  = 0B00000000;
    TRISB  = 0B00000000;
}