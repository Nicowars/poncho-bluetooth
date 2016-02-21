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

/*
 * Autores
 * ---------------------------
 * Gabriel Morgillo
 * Nicolás Laurella
 * Alex Muriel
 * Jaime Zubieta Battista
 * Manuel Solito
 */

/*==================[inclusions]==========================*/
#include "os.h"               /* <= operating system header */
#include "ciaaPOSIX_stdio.h"  /* <= device handler header */
#include "ciaaPOSIX_string.h" /* <= string header */
#include "ciaak.h"            /* <= ciaa kernel header */

#include "bluetooth-rn4020.h"         /* <= own header */
#include "rn4020.h"				/* Modulo Bluetooh header */
#include "controlLED.h"			/* Interprete de comandos LED header */



/*==================[macros and definitions]=================================*/
/*==================[internal data declaration]==============================*/
/*==================[internal functions declaration]=========================*/
/*==================[internal data definition]===============================*/

/** \brief File descriptor for digital output ports
 *
 * Device path /dev/dio/out/0
 */
int32_t fd_out;

/** \brief File descriptor for digital output ports
 *
 * Device path /dev/dio/in/0
 */
int32_t fd_in;

/*
 * mantiene el estado de los pulsadores para que funcionen por flanco
 */
static int8_t estado[3];
   
/** \brief File descriptor of the USB uart
 *
 * Device path /dev/serial/uart/1
 */
static int32_t fd_uart1;

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

/** Breve descripcion de la funcion inicializacion
 * inicializa el modulo buetooth
 * activa el modo echo
 */
void inicializacion(void){
	   /* send a message to the world :) */
	   char message[] = "\n\rIniciando RN-4020\n\r";
	   ciaaPOSIX_write(fd_uart1, message, ciaaPOSIX_strlen(message));

	   /* RN4020 config. */
	   rn4020_ToggleEcho();	// ECHO
	   rn4020_PartialFactory(); // Set factory default config.
	   rn4020_Write("SS,C0000000\n", 12); // Allow some services: Device Information, Battery
	   rn4020_Write("SR,38000800\n", 12); // Auto Advertise, Enable MLDP, Auto MLDP Disable, Auto-enter MLDP Mode
	   rn4020_Reboot(); // Reset module
}

/** \brief Initial task
 *
 * This task is started automatically in the application mode 1.
 */
TASK(InitTask)
{
	/* init CIAA kernel and devices */
	   ciaak_start();

	   ciaaPOSIX_printf("Init Task...\n");

	   /* open CIAA digital outputs */
	   fd_out = ciaaPOSIX_open("/dev/dio/out/0", ciaaPOSIX_O_RDWR);

	   /* open CIAA digital inputs */
	   fd_in = ciaaPOSIX_open("/dev/dio/in/0", ciaaPOSIX_O_RDONLY);

	   /* open UART connected to USB bridge (FT2232) */
	   fd_uart1 = ciaaPOSIX_open("/dev/serial/uart/1", ciaaPOSIX_O_RDWR);

	   /* open UART connected to RS232 connector */
	   rn4020_Init();

	   /* configura la UART */
	   ciaaPOSIX_ioctl(fd_uart1, ciaaPOSIX_IOCTL_SET_FIFO_TRIGGER_LEVEL, (void *)ciaaFIFO_TRIGGER_LEVEL3);

	   /*inicializa el modulo */
	   inicializacion();

	   /* Activates the SerialEchoTask tasks */
	   SetRelAlarm(ActivateButtonsTask, 350, 250);
	   ActivateTask(SerialRXTask);
	   ActivateTask(SerialTXTask);

	   /* end InitTask */
	   TerminateTask();
}

/* Breve descripcion de la funcion SerialRXTask
 *
 * Envia los comandos iniciales al RN4020.
 * Recibe caracteres desde la USB UART y los envia
 * al RN4020.
 */
TASK(SerialRXTask)
{
   int8_t buf[20];   /* buffer for uart operation              */
   int32_t ret;      /* return value variable for posix calls  */

   /* loop infinito */
   while(1) {
	   //lee de UART USB
      ret = ciaaPOSIX_read(fd_uart1, buf, 20);
      if(ret > 0) {
    	  //envia los datos recibidos al modulo
    	  rn4020_Write(buf,ret);
      }
   }
}

/* Breve descripcion de la funcion SerialTXTask
 *
 * Recibe caracteres desde el RN4020 y los envia
 * a la UART USB.
 */
TASK(SerialTXTask)
{
   int8_t buf[20];   /* buffer for uart operation              */
   int32_t ret;      /* return value variable for posix calls  */

   /*loop infinito*/
   while(1)
   {
	   //lee del modulo
      ret = rn4020_Read(buf,20);
      if (ret > 0)
      {
    	  //escribe en UART USB
         ciaaPOSIX_write(fd_uart1, buf, ret);
         //Comprueba si lo que se recibio es un camando del LED
         controlLED_interprete(buf,ret);
      }
   }
}

/* Breve descripcion de la funcion ButtonsTask
 *
 */
TASK(ButtonsTask)
{
	   uint8_t outputs;
	   uint8_t inputs;

	   //lee los pulsadores
	   ciaaPOSIX_read(fd_in, &inputs, 1);

	   //si hubo un flanco descendente en el interruptor 1
	   if (((inputs&SWITCH1_MASK)==0)&& (estado[0]==0)){
		   //intercambia entre CMD y MLDP
		   	 ciaaPOSIX_read(fd_out, &outputs, 1);
		     outputs ^= /*LED1_MASK|*/RN4020_CMD_MASK;
		     ciaaPOSIX_write(fd_out, &outputs, 1);
		     estado[0]=1;
	   }
	   else
		   estado[0]=!(inputs&SWITCH1_MASK);

	   //si hubo un flanco descendente en el interruptor 2
	   if (((inputs&SWITCH2_MASK)==0)&& (estado[1]==0)){
		   //conmuta el valor de wake software
		   	 ciaaPOSIX_read(fd_out, &outputs, 1);
		     outputs ^= (RN4020_WAKE_SW_MASK/*|LED2_MASK*/);
		     ciaaPOSIX_write(fd_out, &outputs, 1);
		     estado[1]=1;
	   }
	   else
		   estado[1]=!(inputs&SWITCH2_MASK);

	   //si hubo un flanco descendente en el interruptor 3
	   if (((inputs&SWITCH3_MASK)==0)&& (estado[2]==0)){
		   //conmuta el valor de wake hardware
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
/*==================[end of file]============================================*/
