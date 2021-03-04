/*
 * File:   Gluco_main.c
 * Author: larj3
 *
 * Created on 3 de febrero de 2019, 04:15 PM
 */
//                                  BIBLIOTECAS
#include <xc.h>
#include <stdlib.h>
#include <math.h>
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
#define delay_ms(x) _delay((unsigned long)((x)*(8000000/4000))) //8 MHZ
#define delay_us(x) _delay((unsigned long)((x)*(8000000/4000000))) //8 MHZ
#include "LCD_header.h"

//                DECLARACION FUNCIONES AUXILIARES
void setup(void);
void ADC_Init(void);
unsigned int ADC_Read(unsigned int);
double i;
int val;
char str[4];
char num;
//                          MAIN
void main(void) {
    setup();
    i=0; //Selector de dato
    ADC_Init();
    lcd_ini();
    lcd_cmd(0B00000001);
    lcd_pos(0,0); lcd_write_s("Procesando...");
    lcd_pos(1,0); lcd_write_s("1 Etapa: V constante");
    PORTA = 0B00000100; //Llave analogica 1 etapa --> I constante
    while (0B00011010>=ADC_Read(0));  //Voltaje deseado
    PORTA = 0B00001000; //Llave analogica 2 etapa --> V constante   
    //------------------------------------------------------------
    lcd_cmd(0B00000001);
    lcd_pos(0,0); lcd_write_s("2 Etapa: I constante");
    lcd_pos(1,0); lcd_write_s("Espere...");
    lcd_pos(1,9); lcd_write_c('4');
    delay_ms(1000); lcd_pos(1,9); lcd_write_c('3');
    delay_ms(1000); lcd_pos(1,9); lcd_write_c('2');
    delay_ms(1000); lcd_pos(1,9); lcd_write_c('1');
    delay_ms(999);
    lcd_cmd(0B00000001);
    val = ADC_Read(0)*19.608;
       itoa(str,val,10);
       lcd_pos(0,0); lcd_write_s(str);
       lcd_pos(0,5); lcd_write_s("mV");
       while (1);
}


void setup(void){
    ANSEL = 0B00000011;  // AN1 AN0 activados
    OSCCON=0B01111000;
    PORTA = 0X00;
    TRISD = 0B00000000;   //LCD Controller
    TRISA = 0B11110011;   //R2,R3 Salida ,  RA4 entrada
    //T1CON=  0B00010000;   //Prescala 1:2 - 1 us
    //ESCALA 1:1, cada cuenta dara 500 us 1/2'000'000 (ciclo maquina)
    delay_ms(100);
}

void ADC_Init(void){
  ADCON0 = 0x81;               //Turn ON ADC and Clock Selection
  ADCON1 = 0x00;               //All pins as Analog Input and setting Reference Voltages
}

unsigned int ADC_Read(unsigned int channel){
  if(channel > 7)              //Channel range is 0 ~ 7
    return 0;
  ADCON0 &= 0xC5;              //Clearing channel selection bits
  ADCON0 |= channel<<3;        //Setting channel selection bits
  delay_us(5);               //Acquisition time to charge hold capacitor
  GO = 1;                    //Initializes A/D conversion
  while(GO==1);             //Waiting for conversion to complete
  return (ADRESH); //Return result
}
