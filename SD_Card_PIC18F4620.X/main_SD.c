/*
 * File:   main_SD.c
 * Author: larj3
 *
 * Created on 8 de septiembre de 2019, 08:39 PM
 */

/**
  Generated Main Source File

  Company:
	Microchip Technology Inc.

  File Name:
	main.c

  Summary:
	This is the main file generated using MPLAB® Code Configurator

  Description:
	This header file provides implementations for driver APIs for all modules selected in the GUI.
	Generation Information :
		Product Revision  :  MPLAB® Code Configurator - v5.25.2
		Device            :  PIC18F4620
		Driver Version    :  2.00
	The generated drivers are tested against the following:
		Compiler          :  XC8 v1.34
		MPLAB             :  MPLAB X v5.35 */


#include "pff3a/source/pff.h"

FATFS FatFs;	/* FatFs work area needed for each volume */
FIL Fil;		/* File object needed for each open file */


void main(void) {
    UINT bw;

	// Initialize the device
    

	if (pf_mount(&FatFs, "", 1) == FR_OK) {	/* Mount SD */
    
		if (pf_open(&Fil, "test.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE) == FR_OK) {	/* Open or create a file */

			if ((Fil.fsize != 0) && (f_lseek(&Fil, Fil.fsize) != FR_OK)) goto endSD;	/* Jump to the end of the file */

			pf_write(&Fil, "Hello world! This is text message written to sd card\r\n", 54, &bw);	/* Write data to the file */
           
			endSD: pf_close(&Fil);								/* Close the file */
		}
	}

	while (1) {
		// Add your application code
	}
}
