/**
 * @file EXTI_private.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 0.1
 * @date 10-11-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

/* EXTI registers definitions */
typedef struct
{
	volatile u32 IMR;
	volatile u32 EMR;
	volatile u32 RTSR;
	volatile u32 FTSR;
	volatile u32 SWIER;
	volatile u32 PR;
}EXTI_t;

#define EXTI 			((volatile EXTI_t*)0x40010400)

#endif
