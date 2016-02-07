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
#include "chip.h"
#include "os.h"               /* <= operating system header */
#include "ciaaPOSIX_stdio.h"  /* <= device handler header */
#include "ciaaPOSIX_string.h" /* <= string header */
#include "ciaak.h"            /* <= ciaa kernel header */
#include "bluetooth-rn4020.h"         /* <= own header */


/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/** \brief File descriptor for digital output ports
 *
 * Device path /dev/dio/out/0
 */
static int32_t fd_out;
static RINGBUFF_T * pRB;

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

void rn4020_init(void){
	/*
	CTS (14) OUTPUT (GPIO5)
	pinNamePort = 6;
	pinNamePin  = 9;
	func        = FUNC0;
	gpioPort    = 3;
	gpioPin     = 5;
	 */

	Chip_SCU_PinMux(6, 9, SCU_MODE_INACT | SCU_MODE_ZIF_DIS, FUNC0);

	/*
	RTS (18) INPUT (GPIO8)
	pinNamePort = 6;
	pinNamePin  = 12;
	func        = FUNC0;
	gpioPort    = 2;
	gpioPin     = 8;
	 */

	//PULLDOWN

	Chip_SCU_PinMux(6, 12, SCU_MODE_PULLDOWN | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS, FUNC0);

	/*
	CMD (8) OUTPUT (GPIO3)
	pinNamePort = 6;
	pinNamePin  = 7;
	func        = FUNC4;
	gpioPort    = 5;
	gpioPin     = 15;
	*/

	Chip_SCU_PinMux(6, 7, SCU_MODE_INACT | SCU_MODE_ZIF_DIS, FUNC4);

	/*
	WAKE_HW (15) OUTPUT (GPIO7)
	pinNamePort = 6;
	pinNamePin  = 11;
	func        = FUNC0;
	gpioPort    = 3;
	gpioPin     = 7;
	 */

	Chip_SCU_PinMux(6, 11, SCU_MODE_INACT | SCU_MODE_ZIF_DIS, FUNC0);

	/*
	WAKE_SW (7) OUTPUT (GPIO1)
	pinNamePort = 6;
	pinNamePin  = 4;
	func        = FUNC0;
	gpioPort    = 3;
	gpioPin     = 3;
	*/

	Chip_SCU_PinMux(6, 4, SCU_MODE_INACT | SCU_MODE_ZIF_DIS, FUNC0);
}

/** \brief Initial task
 *
 * This task is started automatically in the application mode 1.
 */
TASK(InitTask)
{
   /* init CIAA kernel and devices */
   ciaak_start();

   /* print message (only on x86) */
   ciaaPOSIX_printf("Init Task...\n");

   ciaaPOSIX_write(fd_uart1);

   /* open CIAA digital outputs */
   fd_out = ciaaPOSIX_open("/dev/dio/out/0", ciaaPOSIX_O_RDWR);

   rn4020_init();

   //RingBuffer_Init(pRB, NULL, sizeof(char), 16);

   Chip_UART_Init(LPC_USART3);
   Chip_UART_TXEnable(LPC_USART3);
   Chip_UART_SetBaud(LPC_USART3, 115200);

   /* Set the WAKE_SW pin high to enter Command mode. */
   /* Escribir
      gpioPort    = 3;
      gpioPin     = 3;
      value     = 1; */
   Chip_GPIO_SetPinState( LPC_GPIO_PORT, 3, 3, 1);



   /*Issue the command SF,1 to reset to the factory default configuration.*/
   Chip_UART_SendBlocking(LPC_USART3, "SF,1\n", 5);
   //Chip_UART_SendRB(LPC_USART3, pRB, "SF,1\r", 5);


	/*Issue the command SS,C0000000 to enable support of the Device Information and Battery services.*/
  // Chip_UART_SendBlocking(LPC_UART1, "SS,C0000000\r", 12);

   //Chip_UART_SendRB(LPC_USART3, pRB, "SS,C0000000\r", 12);


	/*Issue the command SR,00000000 to set the RN4020 module as a peripheral. */
  // Chip_UART_SendBlocking(LPC_UART1, "SR,00000000\r", 12);

   //Chip_UART_SendRB(LPC_USART3, pRB, "SR,00000000\r", 12);


	/* Issue the command R,1 to reboot the RN4020 module and to make the new settings effective.*/
   Chip_UART_SendBlocking(LPC_USART3, "R,1\n", 5);

  // Chip_UART_SendRB(LPC_USART3, pRB, "R,1\n", 4);

  Chip_UART_SendBlocking(LPC_USART3, "A\n", 2);

   /* activate periodic task:
    *  - for the first time after 350 ticks (350 ms)
    *  - and then every 250 ticks (250 ms)
    */
   SetRelAlarm(ActivatePeriodicTask, 350, 250);

   /* terminate task */
   TerminateTask();
}

/** \brief Periodic Task
 *
 * This task is started automatically every time that the alarm
 * ActivatePeriodicTask expires.
 *
 */
TASK(PeriodicTask)
{
   uint8_t outputs;

   /* write blinking message */
   ciaaPOSIX_printf("Blinking\n");

   /* blink output */
   ciaaPOSIX_read(fd_out, &outputs, 1);
   outputs ^= 0x41;
   ciaaPOSIX_write(fd_out, &outputs, 1);

   /* terminate task */
   TerminateTask();
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

