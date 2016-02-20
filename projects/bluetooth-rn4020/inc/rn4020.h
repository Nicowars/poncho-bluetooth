/*
 * rn4020.h
 *
 *  Created on: 7/2/2016
 *      Author: jaime
 */

#ifndef RN4020_H_
#define RN4020_H_

/* Definitions of digital inputs */
#define SWITCH1_MASK     0x01
#define SWITCH2_MASK     0x02
#define SWITCH3_MASK     0x04
#define SWITCH4_MASK     0x08
#define RN4020_CTS_MASK		0x10
/* End of definitions */

/* Definitions of digital outputs */
#define LED0R_MASK		0x01
#define LED1_MASK       0x02
#define LED2_MASK       0x04
#define LED3_MASK       0x08
#define RN4020_WAKE_SW_MASK	0x10
#define RN4020_RTS_MASK		0x20
#define RN4020_WAKE_HW_MASK	0x40
#define RN4020_CMD_MASK		0x80
/* End of definitions */

/* Definitions of baud rate modifiers */
#define RN4020_BAUDRATE_2400        0
#define RN4020_BAUDRATE_9600        1
#define RN4020_BAUDRATE_19200       2
#define RN4020_BAUDRATE_38400       3
#define RN4020_BAUDRATE_115200      4
#define RN4020_BAUDRATE_230400      5
#define RN4020_BAUDRATE_460800      6
#define RN4020_BAUDRATE_921600      7
/* End of definitions */

/* Definition of features */
#define RN4020_FEAT_CENTRAL         0x80000000
#define RN4020_FEAT_RTREAD          0x40000000
#define RN4020_FEAT_AADV            0x20000000
#define RN4020_FEAT_ENMLDP          0x10000000

#define RN4020_FEAT_AMLDPDIS        0x08000000
#define RN4020_FEAT_NODIRADV        0x04000000
#define RN4020_FEAT_FLOWCTRL        0x02000000
#define RN4020_FEAT_RUNSCSTR        0x01000000

//#define RN4020_FEAT_        0x00800000  RESERVED
#define RN4020_FEAT_ENAUTH          0x00400000
#define RN4020_FEAT_ENRMTCMD        0x00200000
#define RN4020_FEAT_NOSVBOND        0x00100000

//#define RN4020_FEAT_        0x00080000  I/O CAPABILITY
//#define RN4020_FEAT_        0x00040000  I/O CAPABILITY
//#define RN4020_FEAT_        0x00020000  I/O CAPABILITY
#define RN4020_FEAT_BLKSETRC        0x00010000

#define RN4020_FEAT_ENOTA           0x00008000
#define RN4020_FEAT_IOSMODE         0x00004000
#define RN4020_FEAT_SERVER          0x00002000
#define RN4020_FEAT_ENUARTSC        0x00001000

#define RN4020_FEAT_AENTMLDP        0x00000800
#define RN4020_FEAT_MLDPNOST        0x00000400
/* End of definitions */

/* Definition of services */
#define RN4020_SERV_DEVINFO         0x80000000
#define RN4020_SERV_BATT            0x40000000
/* End of definitions */


void rn4020_init( void );

void RN4020_SetServices ( int32_t );

void RN4020_SetFeatures ( int32_t );

void rn4020_echo( void );

void rn4020_factory( void );

void rn4020_reset( void );

ssize_t rn4020_read( void const * , size_t );

void rn4020_write( void * , size_t );


#endif /* RN4020_H_ */
