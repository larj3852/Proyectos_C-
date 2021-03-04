
////////////////////////////////////////////////////////////////////////////////
//+                                                                          +//
// +                           USART HEADER                                 + //
//+                                                                          +//
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// AUTOR: HECTOR AMADOR                                                       //
//                                                                            //
// FECHA: 12/04/2018                                                          //
//                                                                            //
// DESCRIPCIÓN: ARCHIVO DE CABECERA CON LA CONFIGURACIÓN DEL PUERTO SERIAL    //
//              PARA COMUNICACIÓN ASÍNCRONA CON UN BAUDAJE DE 9600 Y CON      //
//              INTERRUPCIÓN POR RECEPCIÓN                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

// FUNCIONES
void usart_ini(void);                         // INCLUIR EN 'MAIN'

void usart_write_c(char);                     // <- SOLO UN CARACTER (8 BITS)
void usart_write_s(const unsigned char *);    // <- CADENA DE CARACTERES
char usart_read(void);                        // -> SOLO UN CARACTER (8 BITS)

// CUERPO DE FUNCIONES

void usart_ini(void){                   // FUNCIÓN DE INICIALIZACIÓN
    
    SPBRG=12;                           // BAUDAJE -> 9600  
    SYNC=0;                             // COMUNICACIÓN ASÍNCRONA
    SPEN=1;                             // PUERTO SERAIAL ACTIVADO
    TXEN=1;                             // TRANSMISIÓN ACTIVADA
    CREN=1;                             // RECEPCIÓN ACTIVADA
    
    GIE=1;                              // INTERRUPCIONES ACTIVADAS
    PEIE=1;                             // INTERRUPCIÓN POR PERIFERICO ACTIVADA
    RCIE=1;                             // INTERRUPCIÓN POR RECEPCIÓN ACTIVADA
}

void usart_write_c(char ch){            // FUNCIÓN DE ESCRITURA DE CARACTER
    
    TXREG=ch;
    while(TRMT==0);
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

////////////////////////////////////////////////////////////////////////////////