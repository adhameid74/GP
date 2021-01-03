/**
 * @file MOTOR_config.h
 * @author Eslam Khaled (Eslam.kh.kamal@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef MOTOR_CONFIG_H
#define MOTOR_CONFIG_H

#define MOTOR1_TIMER    MOTOR_TIMER3
#define MOTOR2_TIMER	MOTOR_TIMER3
/*
    options
    -------
    MOTOR_TIMER2
    MOTOR_TIMER3
    MOTOR_TIMER4
*/
#define MOTOR1_CHANNEL  MOTOR_CHANNEL1
#define MOTOR2_CHANNEL	MOTOR_CHANNEL2
/*
    Options
    -------
    MOTOR_CHANNEL1
    MOTOR_CHANNEL2
    MOTOR_CHANNEL3
    MOTOR_CHANNEL4
*/
#define MOTOR1_PIN1			PA11
#define MOTOR1_PIN2			PA12

#define MOTOR2_PIN1			PA13
#define MOTOR2_PIN2			PA14
/*
    Example PA1
*/
#endif
