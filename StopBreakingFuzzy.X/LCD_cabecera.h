
////////////////////////////////////////////////////////////////////////////////
//+                                                                          +//
// +                           LCD16X2 HEADER                               + //
//+                                                                          +//
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// AUTOR: Jesus Lara                                                          //
//                                                                            //
// FECHA: 24/04/2018                                                          //
//                                                                            //
// DESCRIPTION: LCD16X2 COMANDS LIBRARY					      //
//                                                                            //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

// ASIGNACIONES
#define DATA PORTD                      // PUERTO PERSONALIZABLE
#define RS RD2                          // BIT PERSONALIZABLE
#define E RD3                           // BIT PERSONALIZABLE
//      RW -> GND

#define ENABLE() ((E=1),(E=0))          // EJECUTA LECTURA O ECRITURA

// COMANDOS
#define CLEAR 0B00000001
#define HOME 0B00000010

#define DISPLAY_ON 0B00001100
#define DISPLAY_OFF 0B00001000
#define CURSOR_ON 0B00001110
#define CURSOR_OFF 0B00001100
#define BLINK_ON 0B00001101
#define BLINK_OFF 0B00001100

#define DISPLAY_RIG 0B00011100
#define DISPLAY_LEF 0B00011000
#define CURSOR_RIG 0B00010100
#define CURSOR_LEF 0B00010000

#define CG1 0
#define CG2 1

//LA CONFIGURACIÓN UTILIZA UNA FUNCIÓN DE RETARDO
//#define delay_ms(x) _delay((unsigned long)((x)*(8000000/4000)))     // 8-MHz


// FUNCIONES
void lcd_ini(void);                        // INCLUIR EN 'MAIN'

void lcd_cmd(int);                         // <- COMANDOS MENCIONADOS ARRIBA
void lcd_write_c(char);                    // <- SOLO UN CARACTER (8 BITS)
void lcd_write_s(const unsigned char *);   // <- CADENA DE CARACTERES
void lcd_pos(int,int);                     // <- (FILA: 0-1,COLUMNA: 0-39)


// CUERPO DE FUNCIONES
void lcd_ini(void){                     // FUNCIÓN DE INICIALIZACIÓN
    
    delay_ms(20);
    lcd_cmd(0B00110000);
    delay_ms(5);
    lcd_cmd(0B00110000);
    delay_ms(1);
    lcd_cmd(0B00110000);
    
    // FUNCTION SET
    lcd_cmd(0B00101000);                // 4 BITS, 2 FILAS, CARACTER 5x7 PIX
    lcd_cmd(0B00001100);                // DISPLAY ON, CURSOR OFF, BLINK OFF
    lcd_cmd(0B00000001);                // DISPLAY CLEAR
    // ENTRY MODE SET
    lcd_cmd(0B00000100);                // CURSOR ASCENDENTE, DISPLAY NO INV
}

void lcd_cmd(int cmd){                     // FUNCIÓN DE COMANDO
    
    RS=0;                                  // ENTRA EN MODO COMANDO
    delay_ms(1);
    DATA=(DATA&0X0F)|(cmd&0XF0);           // BITS 4-7
    ENABLE();
    DATA=(DATA&0X0F)|((cmd<<4)&0XF0);      // BITS 0-3
    ENABLE();
}

void lcd_write_c(char ch){                  // FUNCIÓN DE ESCRITURA DE CARACTER
    
    RS=1;                                   // ENTRA EN MODO ESCRITURA
    delay_ms(1);
    DATA=(DATA&0X0F)|(ch&0XF0);             // BITS 4-7
    ENABLE();
    DATA=(DATA&0X0F)|((ch<<4)&0XF0);        // BITS 0-3
    ENABLE();
}

void lcd_write_s(const unsigned char *st){  // FUNCIÓN DE ESCRITURA DE CADENA
    
    for(;*st!='\0';st++){
        lcd_write_c(*st);
    }
}

void lcd_pos(int fila, int columna){        // FUNCIÓN DE POSICIÓN DEL CURSOR
    
    if(fila==0){
        lcd_cmd(columna+0B10000000);
    }
    else if(fila==1){
        lcd_cmd(columna+0B11000000);
    }
    else{}
}


////////////////////////////////////////////////////////////////////////////////