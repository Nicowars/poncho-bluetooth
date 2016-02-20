/* Copyright 2014, Mariano Cerdeiro
 * Copyright 2014, Pablo Ridolfi
 * Copyright 2014, Juan Cecconi
 * Copyright 2014, Gustavo Muro
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief Blinking_echo example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Blinking Blinking_echo example source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 * PR           Pablo Ridolfi
 * JuCe         Juan Cecconi
 * GMuro        Gustavo Muro
 * ErPe         Eric Pernia
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20150603 v0.0.3   ErPe change uint8 type by uint8_t
 *                        in line 172
 * 20141019 v0.0.2   JuCe add printf in each task,
 *                        remove trailing spaces
 * 20140731 v0.0.1   PR   first functional version
 */

/*==================[inclusions]=============================================*/
#include "os.h"               /* <= operating system header */
#include "ciaaPOSIX_stdio.h"  /* <= device handler header */
#include "ciaaPOSIX_string.h" /* <= string header */
#include "ciaak.h"            /* <= ciaa kernel header */

#include "bluetooth-rn4020.h"         /* <= own header */
#include "rn4020.h"


/*==================[macros and definitions]=================================*/

const char * ON_LED = "ON,LED";

const char * OFF_LED = "OFF,LED";

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/** \brief File descriptor for digital output ports
 *
 * Device path /dev/dio/out/0
 */
static int32_t fd_out;

/** \brief File descriptor for digital output ports
 *
 * Device path /dev/dio/in/0
 */
static int32_t fd_in;

static int8_t estado[3];

static char com[20];  /* buffer for store command */

static int8_t com_i = 0;    /* index for buffer com */
   
//static int8_t com_flag = 0;
   
/** \brief File descriptor of the USB uart
 *
 * Device path /dev/serial/uart/1
 */
static int32_t fd_uart1;

/** \brief File descriptor of the RS232 uart
 *
 * Device path /dev/serial/uart/2
 */


/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */
int main(void)
{
   /* Starts the operating system in the Application Mode 1 */
   /* This example has only one Application Mode */
   StartOS(AppMode1);

   /* StartOs shall never returns, but to avoid compiler warnings or errors
    * 0 is returned */
   return 0;
}

/** \brief Error Hook function
 *
 * This fucntion is called from the os if an os interface (API) returns an
 * error. Is for debugging proposes. If called this function triggers a
 * ShutdownOs which ends in a while(1).
 *
 * The values:
 *    OSErrorGetServiceId
 *    OSErrorGetParam1
 *    OSErrorGetParam2
 *    OSErrorGetParam3
 *    OSErrorGetRet
 *
 * will provide you the interface, the input parameters and the returned value.
 * For more details see the OSEK specification:
 * http://portal.osek-vdx.org/files/pdf/specs/os223.pdf
 *
 */
void ErrorHook(void)
{
   ciaaPOSIX_printf("ErrorHook was called\n");
   ciaaPOSIX_printf("Service: %d, P1: %d, P2: %d, P3: %d, RET: %d\n", OSErrorGetServiceId(), OSErrorGetParam1(), OSErrorGetParam2(), OSErrorGetParam3(), OSErrorGetRet());
   ShutdownOS(0);
}

/** \brief Initial task
 *
 * This task is started automatically in the application mode 1.
 */
TASK(InitTask)
{
	uint8_t outputs;

	/* init CIAA kernel and devices */
	   ciaak_start();

	   ciaaPOSIX_printf("Init Task...\n");

	   /* open CIAA digital outputs */
	   fd_out = ciaaPOSIX_open("/dev/dio/out/0", ciaaPOSIX_O_RDWR);

	   /* open CIAA digital inputs */
	   fd_in = ciaaPOSIX_open("/dev/dio/in/0", ciaaPOSIX_O_RDONLY);

	   outputs = RN4020_WAKE_SW_MASK+RN4020_WAKE_HW_MASK;
	   ciaaPOSIX_write(fd_out, &outputs, 1);

	   /* open UART connected to USB bridge (FT2232) */
	   fd_uart1 = ciaaPOSIX_open("/dev/serial/uart/1", ciaaPOSIX_O_RDWR);

	   /* open UART connected to RS232 connector */
	   rn4020_init();

	   ciaaPOSIX_ioctl(fd_uart1, ciaaPOSIX_IOCTL_SET_FIFO_TRIGGER_LEVEL, (void *)ciaaFIFO_TRIGGER_LEVEL3);

	   /* Activates the SerialEchoTask tasks */

	   SetRelAlarm(ActivatePeriodicTask, 350, 250);
	   ActivateTask(SerialEchoTaskUno);
	   ActivateTask(SerialEchoTaskDos);


	   /* end InitTask */
	   TerminateTask();
}

/*
 * SerialEchoTaskUno
 *
 * Envia los comandos iniciales al RN4020.
 * Recibe caracteres desde la USB UART y los envia
 * al RN4020.
 */
TASK(SerialEchoTaskUno)
{
   int8_t buf[20];   /* buffer for uart operation              */
   int32_t ret;      /* return value variable for posix calls  */

   /* send a message to the world :) */
   char message[] = "\n\rIniciando RN-4020\n\r";
   ciaaPOSIX_write(fd_uart1, message, ciaaPOSIX_strlen(message));

   /* RN4020 config. */
   rn4020_echo();	// ECHO
   rn4020_factory(); // Set factory default config.
   rn4020_write("SS,C0000000\n", 12); // Allow some services: Device Information, Battery
   rn4020_write("SR,38000800\n", 12); // Auto Advertise, Enable MLDP, Auto MLDP Disable, Auto-enter MLDP Mode
   rn4020_reset(); // Reset module

   while(1)
   {
      ret = ciaaPOSIX_read(fd_uart1, buf, 20);
      if(ret > 0)
      {
    	  rn4020_write(buf,ret);
      }
   }
}

/*
 * SerialEchoTaskDos
 *
 * Recibe caracteres desde el RN4020 y los envia
 * a la UART USB.
 */
TASK(SerialEchoTaskDos)
{
   int8_t buf[20];   /* buffer for uart operation              */
   int8_t i;
   int32_t ret;      /* return value variable for posix calls  */

   char message[] = "\n\rIniciando\n\r";
   ciaaPOSIX_write(fd_uart1, message, ciaaPOSIX_strlen(message));

   while(1)
   {
      ret = rn4020_read(buf,20);
      if (ret > 0)
      {
         ciaaPOSIX_write(fd_uart1, buf, ret);
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
      
   }
}

TASK(PeriodicTask)
{
   uint8_t outputs;
   uint8_t inputs;

   /* blink output */

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

   /* terminate task */
   TerminateTask();
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

