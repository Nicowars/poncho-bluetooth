/*
 * controlLED.c
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
#include "controlLED.h"

/*==================[internal data definition]===============================*/
static char com[20];  /* buffer for store command */

static int8_t com_i = 0;    /* index for buffer com */

const char * ON_LED = "ON,LED";

const char * OFF_LED = "OFF,LED";

extern int32_t fd_out;

/**breve descripcion de controlLED_interprete
 * analiza los caracteres recibidos en busca de comandos
 * si los encuentra los lleva a cabo
 */
void controlLED_interprete(int8_t* buf,int32_t ret){

	int i;

	if (ret < 20 - com_i){
		//to upper
		//convierte los comandos a mayusculas
		for (i = 0; i < ret; i++) {
			if (buf[i] > 'Z')
				com[com_i] = buf[i] - 'z' + 'Z';
			else
				com[com_i] = buf[i];
			com_i++;
		}
		/* si se recibe un fin de linea se procesa el comando */
		if (com[com_i-1] == '\n') {
			com_i = 0;
			/* ¿se recibio el comando ON_LED? */
	        if (!ciaaPOSIX_strncmp(com, ON_LED, ciaaPOSIX_strlen(ON_LED)))
	        	switch (com[ciaaPOSIX_strlen(ON_LED)]){
	        	//enciende el led correspondiente
	        	case '1':
	        		ciaaPOSIX_read(fd_out, &i, 1);
	        		i|= LED1_MASK;
	        		ciaaPOSIX_write(fd_out, &i, 1);
	        		break;
	        	case '2':
	        		ciaaPOSIX_read(fd_out, &i, 1);
	        		i|= LED2_MASK;
	        		ciaaPOSIX_write(fd_out, &i, 1);
	        		break;
	        	case '3':
	        		ciaaPOSIX_read(fd_out, &i, 1);
	        		i|= LED3_MASK;
	        		ciaaPOSIX_write(fd_out, &i, 1);
	        	}

	        /* ¿Se recibio el comando OFF_LED? */
	        if (!ciaaPOSIX_strncmp(com, OFF_LED, ciaaPOSIX_strlen(OFF_LED)))
	        	switch (com[ciaaPOSIX_strlen(OFF_LED)]){
	        	//apaga los leds correspondientes
	        	case '1':
	        		ciaaPOSIX_read(fd_out, &i, 1);
	        		i&= ~LED1_MASK;
	        		ciaaPOSIX_write(fd_out, &i, 1);
	        		break;
	        	case '2':
	        		ciaaPOSIX_read(fd_out, &i, 1);
	        		i&= ~LED2_MASK;
	        		ciaaPOSIX_write(fd_out, &i, 1);
	        		break;
	        	case '3':
	        		ciaaPOSIX_read(fd_out, &i, 1);
	        		i&= ~LED3_MASK;
	        		ciaaPOSIX_write(fd_out, &i, 1);
	        	}
		}
	} else {
		com_i = 0;
	}
}



