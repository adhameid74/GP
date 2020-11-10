/**
 * @file TIMER_interface.h
 * @author Eslam Khaled (Eslam.kh.kamal@gmail.com)
 * @brief  TIMER Interface file
 * @version 0.1
 * @date 2020-11-10
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

#define TIMER_TIMER2       0
#define TIMER_TIMER3       1
#define TIMER_TIMER4       2
#define TIMER_TIMER5       3

/**
 * @brief  Set timer prescaler
 * 
 * @param Copy_u8TimerNumber      TIMER_TIMER2 , TIMER_TIMER3 , RIMER_TIMER4 
 * @param Copy_u8PrescalerValue   (u16) Prescaler value
 */
void TIMER_voidSetPrescaler(u8 Copy_u8TimerNumber, u16 Copy_u16PrescalerValue);
/**
 * @brief  Synchronus Function for setting timer in Busywait for certain time 
 * 
 * @param Copy_u8TimerNumber     TIMER_TIMER2 , TIMER_TIMER3 , RIMER_TIMER4
 * @param Copy_u16Value          (u16) Timer Value 
 */
void TIMER_voidSetBusyWait(u8 Copy_u8TimerNumber , u16 Copy_u16Value);
/**
 * @brief Asynchronus Function for Setting timer to Interrupt once after certain time
 * 
 * @param Copy_u8TimerNumber    TIMER_TIMER2 , TIMER_TIMER3 , RIMER_TIMER4
 * @param Copy_u16Value         (u16) Timer Value 
 * @param Copy_ptr              (u16) Function Callback       
 */
void TIMER_voidSetIntervalSingle(u8 Copy_u8TimerNumber , u16 Copy_u16Value , void (*Copy_ptr)(void));
/**
 * @brief Asynchronus Function for Setting timer to Interrupt periodicaly after certain time
 * 
 * @param Copy_u8TimerNumber    TIMER_TIMER2 , TIMER_TIMER3 , RIMER_TIMER4
 * @param Copy_u16Value         (u16) Timer Value 
 * @param Copy_ptr              (u16) Function Callback       
 */
void TIMER_voidSetIntervalPeriodic(u8 Copy_u8TimerNumber , u16 Copy_u16Value , void (*Copy_ptr)(void));
/**
 * @brief Get the Elapsed time for certain timer
 * 
 * @param Copy_u8TimerNumber    TIMER_TIMER2 , TIMER_TIMER3 , RIMER_TIMER4
 * @return u16 
 */
u16 TIMER_u16GetElapsedTime(u8 Copy_u8TimerNumber);
/**
 * @brief Get the Remainig time for certain timer
 * 
 * @param Copy_u8TimerNumber 
 * @return u16 
 */
u16 TIMER_u16GetRemainingTime(u8 Copy_u8TimerNumber);
/**
 * @brief  Reset timer (clearing load value register)
 * 
 * @param Copy_u8TimerNumber TIMER_TIMER2 , TIMER_TIMER3 , RIMER_TIMER4
 */
void TIMER_voidResetTimer(u8 Copy_u8TimerNumber);
#endif