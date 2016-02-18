/*
 * rn4020.h
 *
 *  Created on: 7/2/2016
 *      Author: jaime
 */

#ifndef RN4020_H_
#define RN4020_H_

/*
 * Configura los pines GPIO utilizados por el poncho.
 * Envia 1 a WAKE_SW para poner el RN4020 en modo Activo.
 * En modo Activo, el RN4020 esta listo para recibir comandos
 * desde UART.
 */
void rn4020_init(void);

#endif /* RN4020_H_ */
