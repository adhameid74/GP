/**
 * @file TIMER_interface.h
 * @author Eslam Khaled (Eslam.kh.kamal@gmail.com)
 * @brief  TIMER Interface file
 * @version 0.2
 * @date 2020-12-23
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

#define TIMER_TIMER2_CHANNEL1       21
#define TIMER_TIMER2_CHANNEL2       22
#define TIMER_TIMER2_CHANNEL3       23
#define TIMER_TIMER2_CHANNEL4       24

#define TIMER_TIMER3_CHANNEL1       31
#define TIMER_TIMER3_CHANNEL2       32
#define TIMER_TIMER3_CHANNEL3       33
#define TIMER_TIMER3_CHANNEL4       34

#define TIMER_TIMER4_CHANNEL1       41
#define TIMER_TIMER4_CHANNEL2       42
#define TIMER_TIMER4_CHANNEL3       43
#define TIMER_TIMER4_CHANNEL4       44

#define TIMER_SET                   1
#define TIMER_RESET                 2

#define TIMER_START                 1
#define TIMER_STOP                  2

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
 * @brief  Reset timer (clearing load value register) or Set timer (clear counter and set load value with the variable Copy_u16Value)
 * 
 * @param Copy_u8TimerNumber TIMER_TIMER2 , TIMER_TIMER3 , RIMER_TIMER4
 * @param Copy_u8Statue      TIMER_SET , TIMER_RESET
 * @param Copy_u16Value      (u16) Timer Value  
 */
void TIMER_voidSetResetTimer(u8 Copy_u8TimerNumber,u8 Copy_u8Statue,u16 Copy_u16Value);

/**
 * @brief Genetrate PWM Signal 
 * 
 * @param Copy_u8TimerChannelNumber  timer and cahnnel number TIMER_TIMERx_CHANNELx
 * @param Copy_u16PeriodTime         period time
 * @param Copy_u16TimeON             time of high value in period time
 */
void TIMER_voidGeneratePWM(u8 Copy_u8TimerChannelNumber , u16 Copy_u16PeriodTime , u16 Copy_u16TimeON);

/**
 * @brief Start and stop the timer immediatly
 * 
 * @param Copy_u8TimerNumber TIMER_TIMER2 , TIMER_TIMER3 , RIMER_TIMER4
 * @param Copy_u8Statue      TIMER_START , TIMER_STOP
 */
void TIMER_voidStartStopCount(u8 Copy_u8TimerNumber , u8 Copy_u8Statue);
/**
 * @brief Set Auto Reload Register value
 * 
 * @param Copy_u8TimerNumber TIMER_TIMER2 , TIMER_TIMER3 , RIMER_TIMER4
 * @param Copy_u16Value      (u16) Timer Value
 */
void TIMER_voidSetTimerValue(u8 Copy_u8TimerNumber  , u16 Copy_u16Value);
#endif