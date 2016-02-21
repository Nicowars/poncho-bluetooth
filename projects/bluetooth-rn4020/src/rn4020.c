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

void rn4020_init(){
	fd_uart2 = ciaaPOSIX_open("/dev/serial/uart/2", ciaaPOSIX_O_RDWR);
}

void rn4020_echo(){
	ciaaPOSIX_write(fd_uart2, "+\n", 2);
}

void rn4020_factory(){
	ciaaPOSIX_write(fd_uart2, "SF,1\n", 5); // Set factory default config.

}

void rn4020_reset(){
	   ciaaPOSIX_write(fd_uart2, "R,1\n", 4); // Reset module
}

ssize_t rn4020_read(void * buf, size_t nbyte){
	return ciaaPOSIX_read(fd_uart2, buf, 20);
}

void rn4020_write(void const * buf, size_t nbyte){
	 ciaaPOSIX_write(fd_uart2, buf, nbyte);
}





