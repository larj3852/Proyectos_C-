;INSTITUTO POLITECNICO NACIONAL
;UPIITA
;DP
;14 FEB 2019
;DAGB
;NOMBRE DEL TRABAJO
;ESCRITO PARA PIC16F887 EN ENSAMBLADOR (MPLAB)
;DESCRIPCION DEL PROGRAMA:  Lea el nibble bajo del PC y saque ese valor como el 
;							nibble alto del PD. Lea el nibble alto del PB y saque 
;							ese valor como el nibble bajo del PD
			PROCESSOR   16F887
            __CONFIG    0X2007,0X2FE4
			__CONFIG	0X2008,0X3FFF
            INCLUDE     <P16F887.INC>
			ORG			0X0000
			CLRF		PORTD
			BSF			STATUS,RP0		;B1.
			MOVLW		0X61			;OSCINT=OK, 4MHz.
			MOVWF		OSCCON
			BSF			STATUS,RP1		;B3.
			CLRF		ANSEL
			CLRF		ANSELH			;TODOS LOS PINES DIGITALES.
			BCF			STATUS,RP1		;B1.
			CLRF		TRISD			;
			BCF			STATUS,RP0		;B0.
;------------------------------------------------------------------
DENUEVO		MOVF		PORTB,W			
			ANDLW		0XF0			;PORTB AND 0XF0 
			MOVWF		0X20			;Guardar W en 0x20
			MOVF		PORTC,W			;Leer C -> W
			ANDLW		0X0F			;W AND 0X0F
			ADDWF		0X20,F			;reg 0x20 = cont(reg0X20) + W
			SWAPF		0X20,W			;Voltear nibles
			MOVWF		PORTD			;Sacar por PORTD
			GOTO		DENUEVO
			END				


