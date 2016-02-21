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


#define LED0R_MASK		0x01
#define LED1_MASK       0x02
#define LED2_MASK       0x04
#define LED3_MASK       0x08


void controlLED_interprete(int8_t* ,int32_t );

#endif /* PROJECTS_BLUETOOTH_RN4020_INC_CONTROLLED_H_ */
