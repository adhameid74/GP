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
#define USONIC1_ECHO			    PB10
#define USONIC1_TRIGGER 			PB11

#define USONIC2_ECHO			    PA10
#define USONIC2_TRIGGER 			PA11

/*
    options:
    TIMER_TIMER2
    TIMER_TIMER3
    TIMER_TIMER4
*/
#define USONIC_TIMER    TIMER_TIMER2


#endif
