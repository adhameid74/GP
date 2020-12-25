/**
 * @file TIMER_program.c
 * @author Eslam Khaled (Eslam.kh.kamal@gmail.com)
 * @brief  TIMER program file
 * @version 0.2
 * @date 2020-11-10
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include  "TIMER_interface.h"
#include  "TIMER_config.h"
#include  "TIMER_private.h"

static void (*TIMER_Callback[6]) (void) ;
static u8 TIMER_u8IntervalType[6] ;


void TIMER_voidSetPrescaler(u8 Copy_u8TimerNumber, u16 Copy_u16PrescalerValue)
{
    switch (Copy_u8TimerNumber)
    {
    case TIMER_TIMER2:
        TIM2_PSC = Copy_u16PrescalerValue - 1 ;
        break;

    case TIMER_TIMER3:
        TIM3_PSC = Copy_u16PrescalerValue - 1 ;
        break;

    case TIMER_TIMER4:
        TIM4_PSC = Copy_u16PrescalerValue - 1 ;
        break;

    case TIMER_TIMER5:
        TIM5_PSC = Copy_u16PrescalerValue - 1 ;
        break;

    default:
        break;
    }
}
void TIMER_voidSetBusyWait(u8 Copy_u8TimerNumber , u16 Copy_u16Value)
{
    switch (Copy_u8TimerNumber)
    {
    case TIMER_TIMER2:
        CLR_BIT(TIM2_CR1 , 4);     // Counter used as upcounter
        SET_BIT(TIM2_CR1 , 3);     // Counter stops counting at the next update event (clearing the bit CEN)
        CLR_BIT(TIM2_CR1 , 1);     // UEV enabled
        SET_BIT(TIM2_CR1 , 2);     // Only counter overflow/underflow generates an update interrupt or DMA request if enabled.
        TIM2_ARR = Copy_u16Value ;
        SET_BIT(TIM2_CR1 , 0);    // Counter enabled
        while(GET_BIT(TIM2_SR , 0) == 0);  // Wait untill overflow
        SET_BIT(TIM2_CR1 , 1);     // UEV disabled
        CLR_BIT(TIM2_SR , 0) ;    // Clear Update Interrupt flag (UIF)
        break;

    case TIMER_TIMER3:
        CLR_BIT(TIM3_CR1 , 4);    // Counter used as upcounter
        SET_BIT(TIM3_CR1 , 3);    // Counter stops counting at the next update event (clearing the bit CEN)
        CLR_BIT(TIM3_CR1 , 1);     // UEV enabled
        SET_BIT(TIM3_CR1 , 2);     // Only counter overflow/underflow generates an update interrupt or DMA request if enabled.
        TIM3_ARR = Copy_u16Value ;
        SET_BIT(TIM3_CR1 , 0);    // Counter enabled
        while(GET_BIT(TIM3_SR , 0) == 0);  // Wait untill overflow
        SET_BIT(TIM3_CR1 , 1);     // UEV disabled
        CLR_BIT(TIM3_SR , 0);     // Clear Update Interrupt flag (UIF)
        break;

    case TIMER_TIMER4:
        CLR_BIT(TIM4_CR1 , 4);    // Counter used as upcounter
        SET_BIT(TIM4_CR1 , 3);    // Counter stops counting at the next update event (clearing the bit CEN)
        CLR_BIT(TIM4_CR1 , 1);     // UEV enabled
        SET_BIT(TIM4_CR1 , 2);     // Only counter overflow/underflow generates an update interrupt or DMA request if enabled.
        TIM4_ARR = Copy_u16Value ;
        SET_BIT(TIM4_CR1 , 0);    // Counter enabled
        while(GET_BIT(TIM4_SR , 0) == 0);  // Wait untill overflow
        SET_BIT(TIM4_CR1 , 1);     // UEV disabled
        CLR_BIT(TIM4_SR , 0);     // Clear Update Interrupt flag (UIF)
        break;

    case TIMER_TIMER5:
        CLR_BIT(TIM5_CR1 , 4);    // Counter used as upcounter
        SET_BIT(TIM5_CR1 , 3);    // Counter stops counting at the next update event (clearing the bit CEN)
        CLR_BIT(TIM5_CR1 , 1);     // UEV enabled
        SET_BIT(TIM5_CR1 , 2);     // Only counter overflow/underflow generates an update interrupt or DMA request if enabled.
        TIM5_ARR = Copy_u16Value ;
        SET_BIT(TIM5_CR1 , 0);    // Counter enabled
        while(GET_BIT(TIM5_SR , 0) == 0);  // Wait untill overflow
        SET_BIT(TIM5_CR1 , 1);     // UEV disabled
        CLR_BIT(TIM5_SR , 0);     // Clear Update Interrupt flag (UIF)
        break;

    default:
        break;
    }
}
void TIMER_voidSetIntervalSingle(u8 Copy_u8TimerNumber , u16 Copy_u16Value , void (*Copy_ptr)(void))
{
    switch (Copy_u8TimerNumber)
    {
    case TIMER_TIMER2:
        CLR_BIT(TIM2_CR1 , 4);     // Counter used as upcounter
        SET_BIT(TIM2_CR1 , 3);     // Counter stops counting at the next update event (clearing the bit CEN)
        CLR_BIT(TIM2_CR1 , 1);     // UEV enabled
        SET_BIT(TIM2_CR1 , 2);     // Only counter overflow/underflow generates an update interrupt or DMA request if enabled.
        SET_BIT(TIM2_DIER , 0);    // Update interrupt enabled.
        TIM2_ARR = Copy_u16Value ;
        TIMER_u8IntervalType[2] = SINGLE_SHOT ;
        TIMER_Callback[2] = Copy_ptr ;
        SET_BIT(TIM2_CR1 , 0);    // Counter enabled
        break;

    case TIMER_TIMER3:
        CLR_BIT(TIM3_CR1 , 4);     // Counter used as upcounter
        SET_BIT(TIM3_CR1 , 3);     // Counter stops counting at the next update event (clearing the bit CEN)
        CLR_BIT(TIM3_CR1 , 1);     // UEV enabled
        SET_BIT(TIM3_CR1 , 2);     // Only counter overflow/underflow generates an update interrupt or DMA request if enabled.
        SET_BIT(TIM3_DIER , 0);    // Update interrupt enabled.
        TIM3_ARR = Copy_u16Value ;
        TIMER_u8IntervalType[3] = SINGLE_SHOT ;
        TIMER_Callback[3] = Copy_ptr ;
        SET_BIT(TIM3_CR1 , 0);    // Counter enabled
        break;

    case TIMER_TIMER4:
        CLR_BIT(TIM4_CR1 , 4);     // Counter used as upcounter
        SET_BIT(TIM4_CR1 , 3);     // Counter stops counting at the next update event (clearing the bit CEN)
        CLR_BIT(TIM4_CR1 , 1);     // UEV enabled
        SET_BIT(TIM4_CR1 , 2);     // Only counter overflow/underflow generates an update interrupt or DMA request if enabled.
        SET_BIT(TIM4_DIER , 0);    // Update interrupt enabled.
        TIM4_ARR = Copy_u16Value ;
        TIMER_u8IntervalType[4] = SINGLE_SHOT ;
        TIMER_Callback[4] = Copy_ptr ;
        SET_BIT(TIM4_CR1 , 0);    // Counter enabled
        break;

    case TIMER_TIMER5:
        CLR_BIT(TIM5_CR1 , 4);     // Counter used as upcounter
        SET_BIT(TIM5_CR1 , 3);     // Counter stops counting at the next update event (clearing the bit CEN)
        CLR_BIT(TIM5_CR1 , 1);     // UEV enabled
        SET_BIT(TIM5_CR1 , 2);     // Only counter overflow/underflow generates an update interrupt or DMA request if enabled.
        SET_BIT(TIM5_DIER , 0);    // Update interrupt enabled.
        TIM5_ARR = Copy_u16Value ;
        TIMER_u8IntervalType[5] = SINGLE_SHOT ;
        TIMER_Callback[5] = Copy_ptr ;
        SET_BIT(TIM5_CR1 , 0);    // Counter enabled
        break;

    default:
        break;
    }   

}
void TIMER_voidSetIntervalPeriodic(u8 Copy_u8TimerNumber , u16 Copy_u16Value , void (*Copy_ptr)(void))
{
    switch (Copy_u8TimerNumber)
    {
    case TIMER_TIMER2:
        CLR_BIT(TIM2_CR1 , 4);     // Counter used as upcounter
        CLR_BIT(TIM2_CR1 , 3);     // Counter is not stopped at update event
        CLR_BIT(TIM2_CR1 , 1);     // UEV enabled
        SET_BIT(TIM2_CR1 , 2);     // Only counter overflow/underflow generates an update interrupt or DMA request if enabled.
        SET_BIT(TIM2_DIER , 0);    // Update interrupt enabled.
        TIM2_ARR = Copy_u16Value ;
        TIMER_u8IntervalType[2] = MULTI_SHOT ;
        TIMER_Callback[2] = Copy_ptr ;
        SET_BIT(TIM2_CR1 , 0);    // Counter enabled
        break;

    case TIMER_TIMER3:
        CLR_BIT(TIM3_CR1 , 4);     // Counter used as upcounter
        CLR_BIT(TIM3_CR1 , 3);     // Counter is not stopped at update event
        CLR_BIT(TIM3_CR1 , 1);     // UEV enabled
        SET_BIT(TIM3_CR1 , 2);     // Only counter overflow/underflow generates an update interrupt or DMA request if enabled.
        SET_BIT(TIM3_DIER , 0);    // Update interrupt enabled.
        TIM3_ARR = Copy_u16Value ;
        TIMER_u8IntervalType[3] = MULTI_SHOT ;
        TIMER_Callback[3] = Copy_ptr ;
        SET_BIT(TIM3_CR1 , 0);    // Counter enabled
        break;

    case TIMER_TIMER4:
        CLR_BIT(TIM4_CR1 , 4);     // Counter used as upcounter
        CLR_BIT(TIM4_CR1 , 3);     // Counter is not stopped at update event
        CLR_BIT(TIM4_CR1 , 1);     // UEV enabled
        SET_BIT(TIM4_CR1 , 2);     // Only counter overflow/underflow generates an update interrupt or DMA request if enabled.
        SET_BIT(TIM4_DIER , 0);    // Update interrupt enabled.
        TIM4_ARR = Copy_u16Value ;
        TIMER_u8IntervalType[4] = MULTI_SHOT ;
        TIMER_Callback[4] = Copy_ptr ;
        SET_BIT(TIM4_CR1 , 0);    // Counter enabled
        break;

    case TIMER_TIMER5:
        CLR_BIT(TIM5_CR1 , 4);     // Counter used as upcounter
        CLR_BIT(TIM5_CR1 , 3);     // Counter is not stopped at update event
        CLR_BIT(TIM5_CR1 , 1);     // UEV enabled
        SET_BIT(TIM5_CR1 , 2);     // Only counter overflow/underflow generates an update interrupt or DMA request if enabled.
        SET_BIT(TIM5_DIER , 0);    // Update interrupt enabled.
        TIM5_ARR = Copy_u16Value ;
        TIMER_u8IntervalType[5] = MULTI_SHOT ;
        TIMER_Callback[5] = Copy_ptr ;
        SET_BIT(TIM5_CR1 , 0);    // Counter enabled
        break;

    default:
        break;
    }   
}
void TIM2_IRQHandler(void)
{
    if(TIMER_u8IntervalType[2] == SINGLE_SHOT)
    {
        SET_BIT(TIM2_CR1 , 1);     // UEV disabled
        TIM2_ARR = 0;
        CLR_BIT(TIM2_DIER , 0);    // Update interrupt disabled.
    }
    TIMER_Callback[2]();
    CLR_BIT(TIM2_SR , 0) ;    // Clear Update Interrupt flag (UIF)
    
}
void TIM3_IRQHandler(void)
{
    if(TIMER_u8IntervalType[3] == SINGLE_SHOT)
    {
        SET_BIT(TIM3_CR1 , 1);     // UEV disabled
        TIM3_ARR = 0;
        CLR_BIT(TIM3_DIER , 0);    // Update interrupt disabled.
    }
    TIMER_Callback[3]();
    CLR_BIT(TIM3_SR , 0) ;    // Clear Update Interrupt flag (UIF)
    
}
void TIM4_IRQHandler(void)
{
    if(TIMER_u8IntervalType[4] == SINGLE_SHOT)
    {
        SET_BIT(TIM4_CR1 , 1);     // UEV disabled
        TIM4_ARR = 0;
        CLR_BIT(TIM4_DIER , 0);    // Update interrupt disabled.
    }
    TIMER_Callback[4]();
    CLR_BIT(TIM4_SR , 0) ;    // Clear Update Interrupt flag (UIF)
    
}
void TIM5_IRQHandler(void)
{
    if(TIMER_u8IntervalType[5] == SINGLE_SHOT)
    {
        SET_BIT(TIM5_CR1 , 1);     // UEV disabled
        TIM5_ARR = 0;
        CLR_BIT(TIM5_DIER , 0);    // Update interrupt disabled.
    }
    TIMER_Callback[5]();
    CLR_BIT(TIM5_SR , 0) ;    // Clear Update Interrupt flag (UIF)
    
}
u16 TIMER_u16GetElapsedTime(u8 Copy_u8TimerNumber)
{
    u16 Local_u16Time = 0;
    switch (Copy_u8TimerNumber)
    {
    case TIMER_TIMER2:
        Local_u16Time = TIM2_CNT ;
        break;
    case TIMER_TIMER3:
        Local_u16Time = TIM3_CNT ;
        break;
    case TIMER_TIMER4:
        Local_u16Time = TIM4_CNT ;
        break;
    case TIMER_TIMER5:
        Local_u16Time = TIM5_CNT ;
        break;
    default:
        break;
    }
    return Local_u16Time ;
}
u16 TIMER_u16GetRemainingTime(u8 Copy_u8TimerNumber)
{
    u16 Local_u16Time = 0;
    switch (Copy_u8TimerNumber)
    {
    case TIMER_TIMER2:
        Local_u16Time = TIM2_ARR - TIM2_CNT ;
        break;
    case TIMER_TIMER3:
        Local_u16Time = TIM3_ARR - TIM3_CNT ;
        break;
    case TIMER_TIMER4:
        Local_u16Time = TIM4_ARR - TIM4_CNT ;
        break;
    case TIMER_TIMER5:
        Local_u16Time = TIM5_ARR - TIM5_CNT ;
        break;
    default:
        break;
    }
    return Local_u16Time ;
}
void TIMER_voidResetTimer(u8 Copy_u8TimerNumber)
{
    switch (Copy_u8TimerNumber)
    {
    case TIMER_TIMER2:
        TIM2_ARR = 0;
        TIM2_CNT = 0;
        break;
    case TIMER_TIMER3:
        TIM3_ARR = 0;
        TIM3_CNT = 0;
        break;
    case TIMER_TIMER4:
        TIM4_ARR = 0;
        TIM4_CNT = 0;
        break;
    case TIMER_TIMER5:
        TIM5_ARR = 0;
        TIM5_CNT = 0;
        break;
    default:
        break;
    }
}
void TIMER_voidGeneratePWM(u8 Copy_u8TimerChannelNumber , u16 Copy_u16PeriodTime , u16 Copy_u16TimeON)
{
     switch (Copy_u8TimerChannelNumber)
    {
    case TIMER_TIMER2_CHANNEL1:
        TIM2_CCR1 = Copy_u16TimeON;           // Set TimeON value in capture compare register
        TIM2_CCMR1 |= CHANNEL1_OUTPUT_PWM_MODE1  ;  // Set the channel to be output and PWM MODE 1
        TIM2_CCER  |= CHANNEL1_OUTPUT_ENABLE; // Enable the channel output
        CLR_BIT(TIM2_CR1 , 4);                // Counter used as upcounter
        CLR_BIT(TIM2_CR1 , 3);                // Counter is not stopped at update event
        CLR_BIT(TIM2_CR1 , 1);                // UEV enabled
        SET_BIT(TIM2_CR1 , 2);                // Only counter overflow/underflow generates an update interrupt or DMA request if enabled.
        TIM2_ARR  = Copy_u16PeriodTime;       // Set the PeriodTime in Auto Reload Register
        SET_BIT(TIM2_CR1 , 0);                // Counter enabled
        break;
    case TIMER_TIMER2_CHANNEL2:
        TIM2_CCR2 = Copy_u16TimeON;
        TIM2_CCMR1 |= CHANNEL2_OUTPUT_PWM_MODE1  ;  // Set the channel to be output
        TIM2_CCER  |= CHANNEL2_OUTPUT_ENABLE; // Enable the channel output and PWM MODE 1
        CLR_BIT(TIM2_CR1 , 4);                // Counter used as upcounter
        CLR_BIT(TIM2_CR1 , 3);                // Counter is not stopped at update event
        CLR_BIT(TIM2_CR1 , 1);                // UEV enabled
        SET_BIT(TIM2_CR1 , 2);                // Only counter overflow/underflow generates an update interrupt or DMA request if enabled.
        TIM2_ARR  = Copy_u16PeriodTime;       // Set the PeriodTime in Auto Reload Register
        SET_BIT(TIM2_CR1 , 0);                // Counter enabled
        break;
    case TIMER_TIMER2_CHANNEL3:
        TIM2_CCR3 = Copy_u16TimeON;
        TIM2_CCMR2 |= CHANNEL3_OUTPUT_PWM_MODE1  ;  // Set the channel to be output and PWM MODE 1
        TIM2_CCER  |= CHANNEL3_OUTPUT_ENABLE; // Enable the channel output
        CLR_BIT(TIM2_CR1 , 4);                // Counter used as upcounter
        CLR_BIT(TIM2_CR1 , 3);                // Counter is not stopped at update event
        CLR_BIT(TIM2_CR1 , 1);                // UEV enabled
        SET_BIT(TIM2_CR1 , 2);                // Only counter overflow/underflow generates an update interrupt or DMA request if enabled.
        TIM2_ARR  = Copy_u16PeriodTime;       // Set the PeriodTime in Auto Reload Register
        SET_BIT(TIM2_CR1 , 0);                // Counter enabled
        break;
    case TIMER_TIMER2_CHANNEL4:
        TIM2_CCR4 = Copy_u16TimeON;
        TIM2_CCMR2 |= CHANNEL4_OUTPUT_PWM_MODE1  ;  // Set the channel to be output and PWM MODE 1
        TIM2_CCER  |= CHANNEL4_OUTPUT_ENABLE; // Enable the channel output
        CLR_BIT(TIM2_CR1 , 4);                // Counter used as upcounter
        CLR_BIT(TIM2_CR1 , 3);                // Counter is not stopped at update event
        CLR_BIT(TIM2_CR1 , 1);                // UEV enabled
        SET_BIT(TIM2_CR1 , 2);                // Only counter overflow/underflow generates an update interrupt or DMA request if enabled.
        TIM2_ARR  = Copy_u16PeriodTime;       // Set the PeriodTime in Auto Reload Register
        SET_BIT(TIM2_CR1 , 0);                // Counter enabled
        break;
    case TIMER_TIMER3_CHANNEL1:
        TIM3_CCR1 = Copy_u16TimeON;
        TIM3_CCMR1 |= CHANNEL1_OUTPUT_PWM_MODE1  ;  // Set the channel to be output and PWM MODE 1
        TIM3_CCER  |= CHANNEL1_OUTPUT_ENABLE; // Enable the channel output
        CLR_BIT(TIM3_CR1 , 4);                // Counter used as upcounter
        CLR_BIT(TIM3_CR1 , 3);                // Counter is not stopped at update event
        CLR_BIT(TIM3_CR1 , 1);                // UEV enabled
        SET_BIT(TIM3_CR1 , 2);                // Only counter overflow/underflow generates an update interrupt or DMA request if enabled.
        TIM3_ARR  = Copy_u16PeriodTime;       // Set the PeriodTime in Auto Reload Register
        SET_BIT(TIM3_CR1 , 0);                // Counter enabled
        break;
    case TIMER_TIMER3_CHANNEL2:
        TIM3_CCR2 = Copy_u16TimeON;
        TIM3_CCMR1 |= CHANNEL2_OUTPUT_PWM_MODE1  ;  // Set the channel to be output and PWM MODE 1
        TIM3_CCER  |= CHANNEL2_OUTPUT_ENABLE; // Enable the channel output
        CLR_BIT(TIM3_CR1 , 4);                // Counter used as upcounter
        CLR_BIT(TIM3_CR1 , 3);                // Counter is not stopped at update event
        CLR_BIT(TIM3_CR1 , 1);                // UEV enabled
        SET_BIT(TIM3_CR1 , 2);                // Only counter overflow/underflow generates an update interrupt or DMA request if enabled.
        TIM3_ARR  = Copy_u16PeriodTime;       // Set the PeriodTime in Auto Reload Register
        SET_BIT(TIM3_CR1 , 0);                // Counter enabled
        break;
    case TIMER_TIMER3_CHANNEL3:
        TIM3_CCR3 = Copy_u16TimeON;
        TIM3_CCMR2 |= CHANNEL3_OUTPUT_PWM_MODE1  ;  // Set the channel to be output and PWM MODE 1
        TIM3_CCER  |= CHANNEL3_OUTPUT_ENABLE; // Enable the channel output
        CLR_BIT(TIM3_CR1 , 4);                // Counter used as upcounter
        CLR_BIT(TIM3_CR1 , 3);                // Counter is not stopped at update event
        CLR_BIT(TIM3_CR1 , 1);                // UEV enabled
        SET_BIT(TIM3_CR1 , 2);                // Only counter overflow/underflow generates an update interrupt or DMA request if enabled.
        TIM3_ARR  = Copy_u16PeriodTime;       // Set the PeriodTime in Auto Reload Register
        SET_BIT(TIM3_CR1 , 0);                // Counter enabled
        break;
    case TIMER_TIMER3_CHANNEL4:
        TIM3_CCR4 = Copy_u16TimeON;
        TIM3_CCMR2 |= CHANNEL4_OUTPUT_PWM_MODE1  ;  // Set the channel to be output and PWM MODE 1
        TIM3_CCER  |= CHANNEL4_OUTPUT_ENABLE; // Enable the channel output
        CLR_BIT(TIM3_CR1 , 4);                // Counter used as upcounter
        CLR_BIT(TIM3_CR1 , 3);                // Counter is not stopped at update event
        CLR_BIT(TIM3_CR1 , 1);                // UEV enabled
        SET_BIT(TIM3_CR1 , 2);                // Only counter overflow/underflow generates an update interrupt or DMA request if enabled.
        TIM3_ARR  = Copy_u16PeriodTime;       // Set the PeriodTime in Auto Reload Register
        SET_BIT(TIM3_CR1 , 0);                // Counter enabled
        break;
    case TIMER_TIMER4_CHANNEL1:
        TIM4_CCR1 = Copy_u16TimeON;
        TIM4_CCMR1 |= CHANNEL1_OUTPUT_PWM_MODE1  ;  // Set the channel to be output and PWM MODE 1
        TIM4_CCER  |= CHANNEL1_OUTPUT_ENABLE; // Enable the channel output
        CLR_BIT(TIM4_CR1 , 4);                // Counter used as upcounter
        CLR_BIT(TIM4_CR1 , 3);                // Counter is not stopped at update event
        CLR_BIT(TIM4_CR1 , 1);                // UEV enabled
        SET_BIT(TIM4_CR1 , 2);                // Only counter overflow/underflow generates an update interrupt or DMA request if enabled.
        TIM4_ARR  = Copy_u16PeriodTime;       // Set the PeriodTime in Auto Reload Register
        SET_BIT(TIM4_CR1 , 0);                // Counter enabled
        break;
    case TIMER_TIMER4_CHANNEL2:
        TIM4_CCR2 = Copy_u16TimeON;
        TIM4_CCMR1 |= CHANNEL2_OUTPUT_PWM_MODE1  ;  // Set the channel to be output and PWM MODE 1
        TIM4_CCER  |= CHANNEL2_OUTPUT_ENABLE; // Enable the channel output
        CLR_BIT(TIM4_CR1 , 4);                // Counter used as upcounter
        CLR_BIT(TIM4_CR1 , 3);                // Counter is not stopped at update event
        CLR_BIT(TIM4_CR1 , 1);                // UEV enabled
        SET_BIT(TIM4_CR1 , 2);                // Only counter overflow/underflow generates an update interrupt or DMA request if enabled.
        TIM4_ARR  = Copy_u16PeriodTime;       // Set the PeriodTime in Auto Reload Register
        SET_BIT(TIM4_CR1 , 0);                // Counter enabled
        break;
    case TIMER_TIMER4_CHANNEL3:
        TIM4_CCR3 = Copy_u16TimeON;
        TIM4_CCMR2 |= CHANNEL3_OUTPUT_PWM_MODE1  ;  // Set the channel to be output and PWM MODE 1
        TIM4_CCER  |= CHANNEL3_OUTPUT_ENABLE; // Enable the channel output
        CLR_BIT(TIM4_CR1 , 4);                // Counter used as upcounter
        CLR_BIT(TIM4_CR1 , 3);                // Counter is not stopped at update event
        CLR_BIT(TIM4_CR1 , 1);                // UEV enabled
        SET_BIT(TIM4_CR1 , 2);                // Only counter overflow/underflow generates an update interrupt or DMA request if enabled.
        TIM4_ARR  = Copy_u16PeriodTime;       // Set the PeriodTime in Auto Reload Register
        SET_BIT(TIM4_CR1 , 0);                // Counter enabled
        break;
    case TIMER_TIMER4_CHANNEL4:
        TIM4_CCR4 = Copy_u16TimeON;
        TIM4_CCMR2 |= CHANNEL4_OUTPUT_PWM_MODE1  ;  // Set the channel to be output and PWM MODE 1
        TIM4_CCER  |= CHANNEL4_OUTPUT_ENABLE; // Enable the channel output
        CLR_BIT(TIM4_CR1 , 4);                // Counter used as upcounter
        CLR_BIT(TIM4_CR1 , 3);                // Counter is not stopped at update event
        CLR_BIT(TIM4_CR1 , 1);                // UEV enabled
        SET_BIT(TIM4_CR1 , 2);                // Only counter overflow/underflow generates an update interrupt or DMA request if enabled.
        TIM4_ARR  = Copy_u16PeriodTime;       // Set the PeriodTime in Auto Reload Register
        SET_BIT(TIM4_CR1 , 0);                // Counter enabled
        break;
    default:
        break;
    }
}
