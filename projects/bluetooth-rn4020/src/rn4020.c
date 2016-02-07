/*
 * rn4020.c
 *
 *  Created on: 7/2/2016
 *      Author: jaime
 */

#include "chip.h"

void rn4020_init(void){

	/*
	CTS (14) OUTPUT (GPIO5)
	pinNamePort = 6;
	pinNamePin  = 9;
	func        = FUNC0;
	gpioPort    = 3;
	gpioPin     = 5; */
	Chip_SCU_PinMux(6, 9, SCU_MODE_INACT | SCU_MODE_ZIF_DIS, FUNC0);

	/*
	RTS (18) INPUT (GPIO8)
	pinNamePort = 6;
	pinNamePin  = 12;
	func        = FUNC0;
	gpioPort    = 2;
	gpioPin     = 8; */
	//PULLDOWN
	Chip_SCU_PinMux(6, 12, SCU_MODE_PULLDOWN | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS, FUNC0);

	/*
	CMD (8) OUTPUT (GPIO3)
	pinNamePort = 6;
	pinNamePin  = 7;
	func        = FUNC4;
	gpioPort    = 5;
	gpioPin     = 15; */
	Chip_SCU_PinMux(6, 7, SCU_MODE_INACT | SCU_MODE_ZIF_DIS, FUNC4);

	/*
	WAKE_HW (15) OUTPUT (GPIO7)
	pinNamePort = 6;
	pinNamePin  = 11;
	func        = FUNC0;
	gpioPort    = 3;
	gpioPin     = 7; */
	Chip_SCU_PinMux(6, 11, SCU_MODE_INACT | SCU_MODE_ZIF_DIS, FUNC0);

	/*
	WAKE_SW (7) OUTPUT (GPIO1)
	pinNamePort = 6;
	pinNamePin  = 4;
	func        = FUNC0;
	gpioPort    = 3;
	gpioPin     = 3; */
	Chip_SCU_PinMux(6, 4, SCU_MODE_INACT | SCU_MODE_ZIF_DIS, FUNC0);

	/* Set the WAKE_SW pin high to enter Command mode. */
	/* Escribir
	   gpioPort    = 3;
	   gpioPin     = 3;
	   value     = 1; */
	Chip_GPIO_SetPinState( LPC_GPIO_PORT, 3, 3, 1);


}
