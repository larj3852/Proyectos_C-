
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
// DESCRIPCI�N: ARCHIVO DE CABECERA CON LA CONFIGURACI�N DEL PUERTO SERIAL    //
//              PARA COMUNICACI�N AS�NCRONA CON UN BAUDAJE DE 9600 Y CON      //
//              INTERRUPCI�N POR RECEPCI�N                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

// FUNCIONES
void usart_ini(void);                         // INCLUIR EN 'MAIN'

void usart_write_c(char);                     // <- SOLO UN CARACTER (8 BITS)
void usart_write_s(const unsigned char *);    // <- CADENA DE CARACTERES
char usart_read(void);                        // -> SOLO UN CARACTER (8 BITS)

// CUERPO DE FUNCIONES

void usart_ini(void){                   // FUNCI�N DE INICIALIZACI�N
    
    SPBRG=12;                           // BAUDAJE -> 9600  
    SYNC=0;                             // COMUNICACI�N AS�NCRONA
    SPEN=1;                             // PUERTO SERAIAL ACTIVADO
    TXEN=1;                             // TRANSMISI�N ACTIVADA
    CREN=1;                             // RECEPCI�N ACTIVADA
    
    GIE=1;                              // INTERRUPCIONES ACTIVADAS
    PEIE=1;                             // INTERRUPCI�N POR PERIFERICO ACTIVADA
    RCIE=1;                             // INTERRUPCI�N POR RECEPCI�N ACTIVADA
}

void usart_write_c(char ch){            // FUNCI�N DE ESCRITURA DE CARACTER
    
    TXREG=ch;
    while(TRMT==0);
}

void usart_write_s(const unsigned char *st){  // FUNCI�N DE ESCRITURA DE CADENA
    
    for(;*st!='\0';st++){
        
        usart_write_c(*st);
    }
}

char usart_read(void){                  // FUNCI�N DE LECTURA DE CARACTER
    
    if(RCREG)
        return RCREG;
}

////////////////////////////////////////////////////////////////////////////////