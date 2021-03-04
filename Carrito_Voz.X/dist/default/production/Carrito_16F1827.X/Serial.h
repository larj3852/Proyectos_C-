
////////////////////////////////////////////////////////////////////////////////
//+                                                                          +//
// +                           USART HEADER                                 + //
//+                                                                          +//
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// AUTOR: Jesus Lara                                                          //
//                                                                            //
// FECHA:06/05/18                                                             //
//                                                                            //
// DESCRIPCIÓN: ARCHIVO DE CABECERA CON LA CONFIGURACIÓN DEL PUERTO SERIAL    //
//              PARA COMUNICACIÓN ASÍNCRONA CON UN BAUDAJE DE 9600 Y CON      //
//              INTERRUPCIÓN POR RECEPCIÓN                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

// FUNCIONES
void usart_init(void);                         // INCLUIR EN 'MAIN'
void usart_write_c(char);                     // <- SOLO UN CARACTER (8 BITS)
void usart_write_s(const unsigned char *);    // <- CADENA DE CARACTERES
char usart_read(void);                        // -> SOLO UN CARACTER (8 BITS)
int UART_Data_Ready(void);
// CUERPO DE FUNCIONES

void usart_init(void){                   // FUNCIÓN DE INICIALIZACIÓN
    
    SPBRG=32;                           // BAUDAJE -> 9600 PAG 299 tabla 26-5 
    SYNC=0;                             // COMUNICACIÓN ASÍNCRONA
    TXEN=1;                             // TRANSMISIÓN ACTIVADA
    SPEN=1;                             // PUERTO SERAIAL ACTIVADO
    CREN=1;                             // RECEPCIÓN ACTIVADA
}

void usart_write_c(char ch){            // FUNCIÓN DE ESCRITURA DE CARACTER
    while(!TRMT);
    TXREG=ch;
    
}

void usart_write_s(const unsigned char *st){  // FUNCIÓN DE ESCRITURA DE CADENA
    
    for(;*st!='\0';st++){
        usart_write_c(*st);
    }
}

char usart_read(void){                  // FUNCIÓN DE LECTURA DE CARACTER
    
    if(RCREG)
        return RCREG;
}

int UART_Data_Ready(void){
  return RCIF;
}