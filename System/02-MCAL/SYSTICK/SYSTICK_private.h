/**
 * @file SYSTICK_private.h
 * @author Ahmed M.Abdelfattah (ahmedm7md24@gmail.com)
 * @brief 
 * @version 1
 * @date 2021-05-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _SYSTICK_PRIVATE_H
#define _SYSTICK_PRIVATE_H

typedef struct EXTI_private
{
    volatile u32 CTRL;
    volatile u32 LOAD;
    volatile u32 VAL;
    volatile u32 CALIB;
}SYSTICK_t;

#define SYSTICK  ((volatile SYSTICK_t *)0xE000E010)

#define     AHB             1
#define     AHB_BY_8        2

#define 	SetInternalSingle 			1
#define 	SetInternalPeriodic 		2
#endif
