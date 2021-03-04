
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
// DESCRIPCI�N: ARCHIVO DE CABECERA CON LA CONFIGURACI�N DEL PUERTO SERIAL    //
//              PARA COMUNICACI�N AS�NCRONA CON UN BAUDAJE DE 9600 Y CON      //
//              INTERRUPCI�N POR RECEPCI�N                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

// FUNCIONES
void usart_init(void);                         // INCLUIR EN 'MAIN'
void usart_write_c(char);                     // <- SOLO UN CARACTER (8 BITS)
void usart_write_s(const unsigned char *);    // <- CADENA DE CARACTERES
char usart_read(void);                        // -> SOLO UN CARACTER (8 BITS)
int UART_Data_Ready(void);
// CUERPO DE FUNCIONES

void usart_init(void){                   // FUNCI�N DE INICIALIZACI�N
    
    SPBRG=32;                           // BAUDAJE -> 9600 PAG 299 tabla 26-5 
    SYNC=0;                             // COMUNICACI�N AS�NCRONA
    TXEN=1;                             // TRANSMISI�N ACTIVADA
    SPEN=1;                             // PUERTO SERAIAL ACTIVADO
    CREN=1;                             // RECEPCI�N ACTIVADA
}

void usart_write_c(char ch){            // FUNCI�N DE ESCRITURA DE CARACTER
    while(!TRMT);
    TXREG=ch;
    
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

int UART_Data_Ready(void){
  return RCIF;
}