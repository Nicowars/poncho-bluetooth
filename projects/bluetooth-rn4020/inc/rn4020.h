/*
 * rn4020.h
 *
 *  Created on: 7/2/2016
 *      Author: jaime
 */

#ifndef RN4020_H_
#define RN4020_H_

#define SWITCH1     0x01
#define SWITCH2     0x02
#define SWITCH3     0x04
#define SWITCH4     0x08
#define RN4020_CTS_MASK		0x10

#define LED0R_MASK		0x01
#define LED1_MASK       0x02
#define LED2_MASK       0x04
#define LED3_MASK       0x08
#define RN4020_WAKE_SW_MASK	0x10
#define RN4020_RTS_MASK		0x20
#define RN4020_WAKE_HW_MASK	0x40
#define RN4020_CMD_MASK		0x80

#endif /* RN4020_H_ */
