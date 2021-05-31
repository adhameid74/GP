/**
 * @file SYSTICK_interface.h
 * @author Ahmed M.Abdelfattah (ahmedm7md24@gmail.com)
 * @brief 
 * @version 1
 * @date 2021-05-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _SYSTICK_INTERFACE_H
#define _SYSTICK_INTERFACE_H

void SYSTICK_voidInit (void);
/* copy_u32CounterValue Must be 24 bit only */
void SYSTICK_voidSetInternalPeriodic (u32 copy_u32CounterValue,void (*Copy_ptr)(void));
/* copy_u32CounterValue Must be 24 bit only */
void SYSTICK_voidSetInternalSingle (u32 copy_u32CounterValue,void (*Copy_ptr)(void));
/* Stop the timer from counting */
void SYSTICK_voidStopTimer (void);
/* copy_u32CounterValue Must be 24 bit only */
void SYSTICK_voidSetBusyWait (u32 copy_u32CounterValue);
u32 SYSTICK_u32GetElapsedTime(void);
u32 SYSTICK_u32GetERemainingTime(void);

#endif
