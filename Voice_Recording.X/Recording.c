/*
 * File:   Recording.c
 * Author: Jesus Lara
 * Descripción: Grabación de voz a  f=44100 Hz con oscilador interno de 8MHZ 
 *              con pic 16F887. Aplicación de red neuronal con retroalimentación
 *              para eliminar ruido.
 * Created on 23 de abril de 2018, 12:05 AM
 */
//                                  BIBLIOTECAS
#include <xc.h>
/*------------------------ BITS DE CONFIGURACIÓN------------------------------*/
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

/*------------------- DECLARACION FUNCIONES AUXILIARES -----------------------*/
void setup(void);
unsigned int ADC_Read(unsigned char channel);
void ADC_Init();
/*-------------------------- DECLARACION VARIABLES ---------------------------*/
//Ciclo máquina = 4 periodos
#define delay_us(x) _delay((unsigned long)((x)*(8000000/4000000))) //x--> Letra arbitraria
#define delay_ms(x) _delay((unsigned long)((x)*(8000000/4000))) //x--> Letra arbitraria
int A;
void main(void) {
    setup();
    ADC_Init();
    while(1){
        A=ADC_Read(0);
    }
}

void setup(void){
    OSCCON = 0B01111000; //Oscilador 8MHz datasheet pag 66
    TRISA=0B00000001;//0 salida 1 entrada
    ANSEL=0B00000001;// AN0-AN7 0 digital 1 analógico
    ANSELH=0B0000000; // AN8-AN13
    PORTA=0B0000000; //Limpiar estados
    ADCON0=0B10000001; // HABILITA ADC  Fosc/8  AN1  
    delay_ms(5);
}

void ADC_Init(){
  ADCON0 = 0x81;               //Turn ON ADC and Clock Selection
  ADCON1 = 0x00;               //All pins as Analog Input and setting Reference Voltages
}

unsigned int ADC_Read(unsigned char channel){
  if(channel > 7)              //Channel range is 0 ~ 7
    return 0;

  ADCON0 &= 0xC5;              //Clearing channel selection bits
  ADCON0 |= channel<<3;        //Setting channel selection bits
  delay_us(3);               //Acquisition time to charge hold capacitor
  GO = 1;                    //Initializes A/D conversion
  while(GO==1);             //Waiting for conversion to complete
  return ((ADRESH<<8)+ADRESL); //Return result
}
