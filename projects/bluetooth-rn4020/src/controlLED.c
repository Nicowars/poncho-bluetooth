/*
 * controlLED.c
 *
 *  Created on: 20/2/2016
 *      Author: lawliet
 */
#include "controlLED.h"
static char com[20];  /* buffer for store command */

static int8_t com_i = 0;    /* index for buffer com */

const char * ON_LED = "ON,LED";

const char * OFF_LED = "OFF,LED";

extern int32_t fd_out;

extern int32_t fd_in;

static int8_t estado[3];

void controlLED_interprete(int8_t* buf,int32_t ret){
int i;

	if (ret < 20 - com_i)
	         {
	            for (i = 0; i < ret; i++)
	            {
	                if (buf[i] > 'Z')
	                    com[com_i] = buf[i] - 'z' + 'Z';
	                else
	                    com[com_i] = buf[i];
	                com_i++;
	            }

	            /* COMANDO FINALIZADO? */
	            if (com[com_i-1] == '\n')
	            {
	                com_i = 0;

	                /* LED ON? */
	                if (!ciaaPOSIX_strncmp(com, ON_LED, ciaaPOSIX_strlen(ON_LED)))
	                    switch (com[ciaaPOSIX_strlen(ON_LED)]){
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

	                /* LED OFF? */
	                if (!ciaaPOSIX_strncmp(com, OFF_LED, ciaaPOSIX_strlen(OFF_LED)))
	                    switch (com[ciaaPOSIX_strlen(OFF_LED)]){
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

void controlLED_actualizar(){
	   uint8_t outputs;
	   uint8_t inputs;

	   ciaaPOSIX_read(fd_in, &inputs, 1);

	   if (((inputs&SWITCH1_MASK)==0)&& (estado[0]==0)){
		   	 ciaaPOSIX_read(fd_out, &outputs, 1);
		     outputs ^= /*LED1_MASK|*/RN4020_CMD_MASK;
		     ciaaPOSIX_write(fd_out, &outputs, 1);
		     estado[0]=1;
	   }
	   else
		   estado[0]=!(inputs&SWITCH1_MASK);


	   if (((inputs&SWITCH2_MASK)==0)&& (estado[1]==0)){
		   	 ciaaPOSIX_read(fd_out, &outputs, 1);
		     outputs ^= (RN4020_WAKE_SW_MASK/*|LED2_MASK*/);
		     ciaaPOSIX_write(fd_out, &outputs, 1);
		     estado[1]=1;
	   }
	   else
		   estado[1]=!(inputs&SWITCH2_MASK);


	   if (((inputs&SWITCH3_MASK)==0)&& (estado[2]==0)){
		   	 ciaaPOSIX_read(fd_out, &outputs, 1);
		     outputs ^= (RN4020_WAKE_HW_MASK|LED0R_MASK);
		     ciaaPOSIX_write(fd_out, &outputs, 1);
		     estado[2]=1;
	   }
	   else
		   estado[2]=!(inputs&SWITCH3_MASK);
}

void controlLED_init(){
		uint8_t outputs;
	   outputs = RN4020_WAKE_SW_MASK+RN4020_WAKE_HW_MASK;
	   ciaaPOSIX_write(fd_out, &outputs, 1);
}



