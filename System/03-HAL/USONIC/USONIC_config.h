/**
 * @file USONIC_config.h
 * @author Ahmed M.Abdelfattah (ahmedm7md24@gmail.com)
 * @brief  TIMER Interface file
 * @version 1
 * @date 2020-12-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef USONIC_config_H
#define USONIC_config_H


/*
    Example PA1
*/
#define USONIC_ECHO			    PORTB,PIN10
#define USONIC_TRIGGER			PORTB,PIN11

/*
    options:
    TIMER_TIMER2
    TIMER_TIMER3
    TIMER_TIMER4
*/
#define USONIC_TIMER    TIMER_TIMER3


#endif
