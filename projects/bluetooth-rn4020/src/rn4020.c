/*
 * rn4020.c
 *
 * Autores
 * ---------------------------
 * Gabriel Morgillo
 * Nicolás Laurella
 * Alex Muriel
 * Jaime Zubieta Battista
 * Manuel Solito
 */

/*==================[inclusions]==========================*/

#include "ciaaPOSIX_stdio.h"
#include "ciaaPOSIX_string.h"
#include "ciaaPOSIX_stdlib.h"
#include "ciaaPOSIX_assert.h"
#include "rn4020.h"

/*==================[internal data definition]===============================*/

static int32_t fd_uart2;
extern int32_t fd_out;

/**
 * Inicializa el módulo
 * Abre una comunicacion por UART.
 */
void rn4020_Init(){
	uint8_t outputs;
	fd_uart2 = ciaaPOSIX_open("/dev/serial/uart/2", ciaaPOSIX_O_RDWR);
	   outputs = RN4020_WAKE_SW_MASK+RN4020_WAKE_HW_MASK;
	   ciaaPOSIX_write(fd_out, &outputs, 1);
}

void rn4020_ToggleEcho(){
	ciaaPOSIX_write(fd_uart2, "+\n", 2);
}

void rn4020_PartialFactory(){
	ciaaPOSIX_write(fd_uart2, "SF,1\n", 5); // Set factory default config.

}

void rn4020_Reboot(){
	   ciaaPOSIX_write(fd_uart2, "R,1\n", 4); // Reset module
}

ssize_t rn4020_Read(void * buf, size_t nbyte){
	return ciaaPOSIX_read(fd_uart2, buf, 20);
}

void rn4020_Write(void const * buf, size_t nbyte){
	 ciaaPOSIX_write(fd_uart2, buf, nbyte);
}





