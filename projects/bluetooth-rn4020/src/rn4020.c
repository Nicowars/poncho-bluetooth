/*
 * rn4020.c
 *
 *  Created on: 7/2/2016
 *      Author: jaime
 */

#include "ciaak.h"            /* <= ciaa kernel header */
#include "ciaaPlatforms.h"
#include "ciaaPOSIX_stdio.h"
#include "ciaaPOSIX_string.h"
#include "ciaaPOSIX_stdlib.h"
#include "ciaaPOSIX_assert.h"
#include "os.h"

static int32_t fd_uart2;

/* Obviamente esta funcion 
 * no tiene que estar aca... */
static char * xtoa8( uint32_t hex ){
    char str[8];
    char aux;
    int8_t ind;
    for (ind = 0; ind < 8; ind++) {
        aux = hex % 16; 
        if (aux < 10)
            str[7-ind] = aux + '0';
        else
            str[7-ind] = aux + 'A' - 10;
        hex /= 16;
    }
    return str;
}
 

void rn4020_Init(){
	fd_uart2 = ciaaPOSIX_open("/dev/serial/uart/2", ciaaPOSIX_O_RDWR);
}

void RN4020_SetServices ( uint32_t op ){
    char * str = "SS";
    char * hex;
    hex = xtoa8(op);
    ciaaPOSIX_strcat( str , hex );
    ciaaPOSIX_write(fd_uart2, str, 12);
}

void RN4020_SetFeatures ( uint32_t op ){
    char * str = "SR";
    char * hex;
    hex = xtoa8(op);
    ciaaPOSIX_strcat( str , hex );
    ciaaPOSIX_write(fd_uart2, str, 12);
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
	return ciaaPOSIX_read(fd_uart2, buf, nbyte);
}

void rn4020_Write(void const * buf, size_t nbyte){
	 ciaaPOSIX_write(fd_uart2, buf, nbyte);
}





