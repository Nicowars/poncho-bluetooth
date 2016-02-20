/*
 * controlLED.h
 *
 *  Created on: 20/2/2016
 *      Author: lawliet
 */

#ifndef PROJECTS_BLUETOOTH_RN4020_INC_CONTROLLED_H_
#define PROJECTS_BLUETOOTH_RN4020_INC_CONTROLLED_H_

#include "ciaak.h"            /* <= ciaa kernel header */
#include "ciaaPlatforms.h"
#include "ciaaPOSIX_stdio.h"
#include "ciaaPOSIX_string.h"
#include "ciaaPOSIX_stdlib.h"
#include "ciaaPOSIX_assert.h"
#include "os.h"
#define SWITCH1_MASK     0x01
#define SWITCH2_MASK     0x02
#define SWITCH3_MASK     0x04
#define SWITCH4_MASK     0x08
#define RN4020_CTS_MASK		0x10

#define LED0R_MASK		0x01
#define LED1_MASK       0x02
#define LED2_MASK       0x04
#define LED3_MASK       0x08
#define RN4020_WAKE_SW_MASK	0x10
#define RN4020_RTS_MASK		0x20
#define RN4020_WAKE_HW_MASK	0x40
#define RN4020_CMD_MASK		0x80

void controlLED_init();
void controlLED_interprete(int8_t* ,int32_t );
void controlLED_actualizar();

#endif /* PROJECTS_BLUETOOTH_RN4020_INC_CONTROLLED_H_ */
