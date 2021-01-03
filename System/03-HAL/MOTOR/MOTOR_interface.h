/**
 * @file MOTOR_interface.h
 * @author Eslam Khaled (Eslam.kh.kamal@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef MOTOR_INTERFACE_H
#define MOTOR_INTERFACE_H

#define MOTOR1                          1
#define MOTOR2                          2

#define MOTOR_TIM2_CHN1                PA0             
#define MOTOR_TIM2_CHN2                PA1
#define MOTOR_TIM2_CHN3                PA2
#define MOTOR_TIM2_CHN4                PA3

#define MOTOR_TIM3_CHN1                PA6
#define MOTOR_TIM3_CHN2                PA7
#define MOTOR_TIM3_CHN3                PB0
#define MOTOR_TIM3_CHN4                PB1

#define MOTOR_TIM4_CHN1                PB6
#define MOTOR_TIM4_CHN2                PB7
#define MOTOR_TIM4_CHN3                PB8
#define MOTOR_TIM4_CHN4                PB9

#define MOTOR_TIMER2                      20
#define MOTOR_TIMER3                      30
#define MOTOR_TIMER4                      40

#define MOTOR_CHANNEL1                  1
#define MOTOR_CHANNEL2                  2
#define MOTOR_CHANNEL3                  3
#define MOTOR_CHANNEL4                  4

#define MOTOR_DIRECTION_0              0
#define MOTOR_DIRECTION_1              1
#define MOTOR_DIRECTION_2              2

/**
 * @brief Initialize Motor driver pins' direction and timer channel
 * 
 */
void MOTOR_voidMotorInit(void);
/**
 * @brief Control motor rotation direction
 * 
 * @param Copy_u8MotorID            MOTOR1 or MOTOR2
 * @param Copy_u8MotorDirection     MOTOR_DIRECTION0   Motor polarity will be 0,0  (STOP)
 *                                  MOTOR_DIRECTION1   Motor polarity will be 0,1  (Clockwise)     *depends on motor connection
 *                                  MOTOR_DIRECTION2   Motor polarity will be 1,0  (Anticlockwise) *depends on motor connection
 */
void MOTOR_voidSetMotorDirection(u8 Copy_u8MotorID , u8 Copy_u8MotorDirection);
/**
 * @brief Control motor rotaion speed with PWM generation
 * 
 * @param Copy_u8MotorID                MOTOR1 or MOTOR2
 * @param Copy_u16MotorSpeedPercent     Percentage of Max speed (integer value from 0 : 100)
 */
void MOTOR_voidSetMotorSpeed(u8 Copy_u8MotorID , u16 Copy_u16MotorSpeedPercent);
#endif
