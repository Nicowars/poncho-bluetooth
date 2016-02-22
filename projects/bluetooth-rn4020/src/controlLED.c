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
#include "rn4020.h"

/*==================[internal data definition]===============================*/
static char com[20];  /* buffer for store command */

static int8_t com_i = 0;    /* index for buffer com */

static int8_t Connect = 0;

static int8_t MLDP = 0;

const char * ON_LED = "ON,LED";

const char * OFF_LED = "OFF,LED";

const char * Connected = "CONNECTED";

const char * EndConnection = "CONNECTION END";

const char * mldp = "MLDP";

const char * cmd = "CMD";

const char * end = "END";

extern int32_t fd_out;

uint8_t outputs;

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
		if (com[com_i-1] == '\n' || com[com_i-1] == '\r') {
			com_i = 0;

			if (!ciaaPOSIX_strncmp(com, Connected, ciaaPOSIX_strlen(Connected))){
				Connect=1;
				MLDP=1;
				ciaaPOSIX_read(fd_out, &outputs, 1);
				outputs |= RN4020_CMD_MASK;
				ciaaPOSIX_write(fd_out, &outputs, 1);
			}

			else

				if (!ciaaPOSIX_strncmp(com, EndConnection, ciaaPOSIX_strlen(EndConnection))){
					Connect=0;
					MLDP=0;
					ciaaPOSIX_read(fd_out, &outputs, 1);
					outputs &= ~RN4020_CMD_MASK;
					ciaaPOSIX_write(fd_out, &outputs, 1);
				}

				else

					if (!ciaaPOSIX_strncmp(com, mldp, ciaaPOSIX_strlen(mldp)) && Connect && !MLDP){
						MLDP=1;
						ciaaPOSIX_read(fd_out, &outputs, 1);
						outputs |= RN4020_CMD_MASK;
						ciaaPOSIX_write(fd_out, &outputs, 1);
					}

					else

						if ((!ciaaPOSIX_strncmp(com, cmd, ciaaPOSIX_strlen(cmd)) || !ciaaPOSIX_strncmp(com, end, ciaaPOSIX_strlen(end))) && Connect && MLDP){
							MLDP=0;
							ciaaPOSIX_read(fd_out, &outputs, 1);
							outputs &= ~RN4020_CMD_MASK;
							ciaaPOSIX_write(fd_out, &outputs, 1);
						}

						else

							/* ¿se recibio el comando ON_LED? */
							if (!ciaaPOSIX_strncmp(com, ON_LED, ciaaPOSIX_strlen(ON_LED)) && Connect && MLDP)
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
							else
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
	}
	else
		com_i = 0;
}
