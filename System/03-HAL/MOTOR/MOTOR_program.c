/**
 * @file MOTOR_program.c
 * @author Eslam Khaled (Eslam.kh.kamal@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include  "MOTOR_interface.h"
#include  "MOTOR_config.h"
#include  "MOTOR_private.h"

#include  "TIMER_interface.h"
#include  "GPIO_interface.h"

void MOTOR_voidMotorInit(void)
{
    // Determine PORT and PIN number for TIMER and its CHANNEL from Configuration file
    #if (MOTOR1_TIMER == MOTOR_TIMER2)   && (MOTOR1_CHANNEL == MOTOR_CHANNEL1)
        #define MOTOR1_TIMER_CHANNEL MOTOR_TIM2_CHN1
        #define MOTOR1_TIMER_CHANNELx   MOTOR_TIMER2 + MOTOR_CHANNEL1
    #elif (MOTOR1_TIMER == MOTOR_TIMER2) && (MOTOR1_CHANNEL == MOTOR_CHANNEL2)
        #define MOTOR1_TIMER_CHANNEL MOTOR_TIM2_CHN2
        #define MOTOR1_TIMER_CHANNELx   MOTOR_TIMER2 + MOTOR_CHANNEL2
    #elif (MOTOR1_TIMER == MOTOR_TIMER2) && (MOTOR1_CHANNEL == MOTOR_CHANNEL3)
        #define MOTOR1_TIMER_CHANNEL MOTOR_TIM2_CHN3
        #define MOTOR1_TIMER_CHANNELx   MOTOR_TIMER2 + MOTOR_CHANNEL3
    #elif (MOTOR1_TIMER == MOTOR_TIMER2) && (MOTOR1_CHANNEL == MOTOR_CHANNEL4)
        #define MOTOR1_TIMER_CHANNEL MOTOR_TIM2_CHN4
        #define MOTOR1_TIMER_CHANNELx   MOTOR_TIMER2 + MOTOR_CHANNEL4

    #elif (MOTOR1_TIMER == MOTOR_TIMER3)   && (MOTOR1_CHANNEL == MOTOR_CHANNEL1)
        #define MOTOR1_TIMER_CHANNEL MOTOR_TIM3_CHN1
        #define MOTOR1_TIMER_CHANNELx   MOTOR_TIMER3 + MOTOR_CHANNEL1
    #elif (MOTOR1_TIMER == MOTOR_TIMER3) && (MOTOR1_CHANNEL == MOTOR_CHANNEL2)
        #define MOTOR1_TIMER_CHANNEL MOTOR_TIM3_CHN2
        #define MOTOR1_TIMER_CHANNELx   MOTOR_TIMER3 + MOTOR_CHANNEL2
    #elif (MOTOR1_TIMER == MOTOR_TIMER3) && (MOTOR1_CHANNEL == MOTOR_CHANNEL3)
        #define MOTOR1_TIMER_CHANNEL MOTOR_TIM3_CHN3
        #define MOTOR1_TIMER_CHANNELx   MOTOR_TIMER3 + MOTOR_CHANNEL4
    #elif (MOTOR1_TIMER == MOTOR_TIMER3) && (MOTOR1_CHANNEL == MOTOR_CHANNEL4)
        #define MOTOR1_TIMER_CHANNEL MOTOR_TIM3_CHN4
        #define MOTOR1_TIMER_CHANNELx   MOTOR_TIMER3 + MOTOR_CHANNEL4

    #elif (MOTOR1_TIMER == MOTOR_TIMER4)   && (MOTOR1_CHANNEL == MOTOR_CHANNEL1)
        #define MOTOR1_TIMER_CHANNEL MOTOR_TIM4_CHN1
        #define MOTOR1_TIMER_CHANNELx   MOTOR_TIMER4 + MOTOR_CHANNEL1
    #elif (MOTOR1_TIMER == MOTOR_TIMER4) && (MOTOR1_CHANNEL == MOTOR_CHANNEL2)
        #define MOTOR1_TIMER_CHANNEL MOTOR_TIM4_CHN2
        #define MOTOR1_TIMER_CHANNELx   MOTOR_TIMER4 + MOTOR_CHANNEL2
    #elif (MOTOR1_TIMER == MOTOR_TIMER4) && (MOTOR1_CHANNEL == MOTOR_CHANNEL3)
        #define MOTOR1_TIMER_CHANNEL MOTOR_TIM4_CHN3
        #define MOTOR1_TIMER_CHANNELx   MOTOR_TIMER4 + MOTOR_CHANNEL3
    #elif (MOTOR1_TIMER == MOTOR_TIMER4) && (MOTOR1_CHANNEL == MOTOR_CHANNEL4)
        #define MOTOR1_TIMER_CHANNEL MOTOR_TIM4_CHN4
        #define MOTOR1_TIMER_CHANNELx   MOTOR_TIMER4 + MOTOR_CHANNEL4

    #endif

    #if (MOTOR2_TIMER == MOTOR_TIMER2)   && (MOTOR2_CHANNEL == MOTOR_CHANNEL1)
        #define MOTOR2_TIMER_CHANNEL MOTOR_TIM2_CHN1
        #define MOTOR2_TIMER_CHANNELx   MOTOR_TIMER2 + MOTOR_CHANNEL1
    #elif (MOTOR2_TIMER == MOTOR_TIMER2) && (MOTOR2_CHANNEL == MOTOR_CHANNEL2)
        #define MOTOR2_TIMER_CHANNEL MOTOR_TIM2_CHN2
        #define MOTOR2_TIMER_CHANNELx   MOTOR_TIMER2 + MOTOR_CHANNEL2
    #elif (MOTOR2_TIMER == MOTOR_TIMER2) && (MOTOR2_CHANNEL == MOTOR_CHANNEL3)
        #define MOTOR2_TIMER_CHANNEL MOTOR_TIM2_CHN3
        #define MOTOR2_TIMER_CHANNELx   MOTOR_TIMER2 + MOTOR_CHANNEL3
    #elif (MOTOR2_TIMER == MOTOR_TIMER2) && (MOTOR2_CHANNEL == MOTOR_CHANNEL4)
        #define MOTOR2_TIMER_CHANNEL MOTOR_TIM2_CHN4
        #define MOTOR2_TIMER_CHANNELx   MOTOR_TIMER2 + MOTOR_CHANNEL4

    #elif (MOTOR2_TIMER == MOTOR_TIMER3)   && (MOTOR2_CHANNEL == MOTOR_CHANNEL1)
        #define MOTOR2_TIMER_CHANNEL MOTOR_TIM3_CHN1
        #define MOTOR2_TIMER_CHANNELx   MOTOR_TIMER3 + MOTOR_CHANNEL1
    #elif (MOTOR2_TIMER == MOTOR_TIMER3) && (MOTOR2_CHANNEL == MOTOR_CHANNEL2)
        #define MOTOR2_TIMER_CHANNEL MOTOR_TIM3_CHN2
        #define MOTOR2_TIMER_CHANNELx   MOTOR_TIMER3 + MOTOR_CHANNEL2
    #elif (MOTOR2_TIMER == MOTOR_TIMER3) && (MOTOR2_CHANNEL == MOTOR_CHANNEL3)
        #define MOTOR2_TIMER_CHANNEL MOTOR_TIM3_CHN3
        #define MOTOR2_TIMER_CHANNELx   MOTOR_TIMER3 + MOTOR_CHANNEL3
    #elif (MOTOR2_TIMER == MOTOR_TIMER3) && (MOTOR2_CHANNEL == MOTOR_CHANNEL4)
        #define MOTOR2_TIMER_CHANNEL MOTOR_TIM3_CHN4
        #define MOTOR2_TIMER_CHANNELx   MOTOR_TIMER3 + MOTOR_CHANNEL4

    #elif (MOTOR2_TIMER == MOTOR_TIMER4)   && (MOTOR2_CHANNEL == MOTOR_CHANNEL1)
        #define MOTOR2_TIMER_CHANNEL MOTOR_TIM4_CHN1
        #define MOTOR2_TIMER_CHANNELx   MOTOR_TIMER4 + MOTOR_CHANNEL1
    #elif (MOTOR2_TIMER == MOTOR_TIMER4) && (MOTOR2_CHANNEL == MOTOR_CHANNEL2)
        #define MOTOR2_TIMER_CHANNEL MOTOR_TIM4_CHN2
        #define MOTOR2_TIMER_CHANNELx   MOTOR_TIMER4 + MOTOR_CHANNEL2
    #elif (MOTOR2_TIMER == MOTOR_TIMER4) && (MOTOR2_CHANNEL == MOTOR_CHANNEL3)
        #define MOTOR2_TIMER_CHANNEL MOTOR_TIM4_CHN3
        #define MOTOR2_TIMER_CHANNELx   MOTOR_TIMER4 + MOTOR_CHANNEL3
    #elif (MOTOR2_TIMER == MOTOR_TIMER4) && (MOTOR2_CHANNEL == MOTOR_CHANNEL4)
        #define MOTOR2_TIMER_CHANNEL MOTOR_TIM4_CHN4
        #define MOTOR2_TIMER_CHANNELx   MOTOR_TIMER4 + MOTOR_CHANNEL4
    #endif
    // Set the Direction of Motor1 pins to output PUSH_PULL  
    GPIO_voidSetPinDirection(MOTOR1_PIN1 , OUTPUT_10MHZ , PUSH_PULL);
    GPIO_voidSetPinDirection(MOTOR1_PIN2 , OUTPUT_10MHZ , PUSH_PULL);

    // Set the Direction of Motor2 pins to output PUSH_PULL  
    GPIO_voidSetPinDirection(MOTOR2_PIN1 , OUTPUT_10MHZ , PUSH_PULL);
    GPIO_voidSetPinDirection(MOTOR2_PIN2 , OUTPUT_10MHZ , PUSH_PULL);

    // Set the Direction of timer channels to AF_PUSH_PULL
    GPIO_voidSetPinDirection(MOTOR1_TIMER_CHANNEL , OUTPUT_2MHZ , AF_PUSH_PULL);
    GPIO_voidSetPinDirection(MOTOR2_TIMER_CHANNEL , OUTPUT_2MHZ , AF_PUSH_PULL);

    // Set the timer prescaler value 
    TIMER_voidSetPrescaler(MOTOR1_TIMER , 4);
    TIMER_voidSetPrescaler(MOTOR2_TIMER , 4);
}
void MOTOR_voidSetMotorDirection(u8 Copy_u8MotorID , u8 Copy_u8MotorDirection)
{
    if(Copy_u8MotorID == MOTOR1)
    {
        if(Copy_u8MotorDirection == MOTOR_DIRECTION_0)
        {
            GPIO_voidSetPinValue(MOTOR1_PIN1 , LOW);
            GPIO_voidSetPinValue(MOTOR1_PIN2 , LOW);
        }
        else if(Copy_u8MotorDirection == MOTOR_DIRECTION_1)
        {
            GPIO_voidSetPinValue(MOTOR1_PIN1 , HIGH);
            GPIO_voidSetPinValue(MOTOR1_PIN2 , LOW);
        }
        else if(Copy_u8MotorDirection == MOTOR_DIRECTION_2)
        {
            GPIO_voidSetPinValue(MOTOR1_PIN1 , LOW);
            GPIO_voidSetPinValue(MOTOR1_PIN2 , HIGH);
        }
    }
    if(Copy_u8MotorID == MOTOR2)
    {
        if(Copy_u8MotorDirection == MOTOR_DIRECTION_0)
        {
            GPIO_voidSetPinValue(MOTOR2_PIN1 , LOW);
            GPIO_voidSetPinValue(MOTOR2_PIN2 , LOW);
        }
        else if(Copy_u8MotorDirection == MOTOR_DIRECTION_1)
        {
            GPIO_voidSetPinValue(MOTOR2_PIN1 , HIGH);
            GPIO_voidSetPinValue(MOTOR2_PIN2 , LOW);
        }
        else if(Copy_u8MotorDirection == MOTOR_DIRECTION_2)
        {
            GPIO_voidSetPinValue(MOTOR2_PIN1 , LOW);
            GPIO_voidSetPinValue(MOTOR2_PIN2 , HIGH);
        }
    }
}
void MOTOR_voidSetMotorSpeed(u8 Copy_u8MotorID , u16 Copy_u16MotorSpeedPercent)
{
    if(Copy_u8MotorID == MOTOR1)
    {
        TIMER_voidGeneratePWM(MOTOR1_TIMER_CHANNELx,0x0064,Copy_u16MotorSpeedPercent);
    }
    else if(Copy_u8MotorID == MOTOR2)
    {
        TIMER_voidGeneratePWM(MOTOR2_TIMER_CHANNELx,0x0064,Copy_u16MotorSpeedPercent);
    }
}
