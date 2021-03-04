

//                                  BIBLIOTECAS
#include <xc.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
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
#include "LCD_cabecera.h"
#include "Fuzzy_Lib.h"
//#include "Fuzzy_Lib.h"
#define ECHO RD0
#define TRIG RD1

int cm=0, us=0;  

double tiempo=0;
float cmf=0, d1=0,d2=0;
int V=0;//tiempo us
char centi[3];
char velo[5];
int DUTY=0;


//                DECLARACION FUNCIONES AUXILIARES
void setup(void);
void distancia(void);

void main(void) {
    setup();
    lcd_ini();
    lcd_cmd(0B00000001);
    lcd_pos(0,0);
        lcd_write_s("Pos[cm]:         ");
    
    while(1){
        tiempo=0; //REINICIAR TIEMPO   
        distancia();
        d1=cmf;
        delay_ms(50);
        distancia();
        d2=cmf;
        cm=cm-6;
        V=round((d1-d2)/((tiempo/200000)+0.05)); //Tiempo de medición distancia + tiempo delay
        V=abs(V); // <--- PARA ESTO SE OCUPA STDLIB :v
        
        DUTY=Fuz(cm,V);
         //Duty Cycle Ratio = (CCPRxL:CCPxCON<5:4>)/(4*(PR2+1))
        P=DUTY*4*(PR2+1);
        P=P/(4*100);
        P=round(P);
        CCPR2L= (int) P;
        //DUTY=Fuz (d2,velocidad);
        
        /*ESCRIBIENDO LA DISTANCIA*/
        itoa(centi,cm,10);
        lcd_pos(0,0);
        lcd_write_s("Pos[cm]:         ");
        lcd_pos(0,8);
        lcd_write_s(centi);
        /*ESCRIBIENDO LA VELOCIDAD*/
        itoa(velo,P,10);
        lcd_pos(1,0);
        lcd_write_s("Vel[cm/s]:      "); 
        lcd_pos(1,10);
        lcd_write_s(velo);
       
    }
}

void setup(void){
    OSCCON=0B01111000;
    TRISC=0;
    PORTC=0;
    PORTD=0;
    TRISD=  0B00000001;   //Pin eco entrada
    T1CON=  0B00010000;   //Prescala 1:2 -1 us
    T2CON=  0B00000110;   //<1:0> Preescala 1:16 - Cada cuenta da 1 us
    CCP2CON=0B00001100;   // <3-0> --> 11XX PWM mode      CCP2CON<5:4>=LMB duty Cycle
    PR2=124;              //PWM Period = [PR2 + 1]*4*Tosc*(TMR2 Prescale Value)
                          //125--> periodo = 1 [ms]     
    CCPR2L=124;               //Duty Cycle Ratio = (CCPRxL:CCPxCON<5:4>)/(4*(PR2+1))
    //ESCALA 1:1, cada cuenta dara 500 us 1/2'000'000 (ciclo maquina)
    delay_ms(1000);
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
        cmf=us/58;
    }
    tiempo=us+tiempo;
}

