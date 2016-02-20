/*
 * rn4020.h
 *
 *  Created on: 7/2/2016
 *      Author: jaime
 */

#ifndef RN4020_H_
#define RN4020_H_



void rn4020_init();

void rn4020_echo();

void rn4020_factory();

void rn4020_reset();

ssize_t rn4020_read(void *, size_t);

void rn4020_write(void const *, size_t);

#endif /* RN4020_H_ */
