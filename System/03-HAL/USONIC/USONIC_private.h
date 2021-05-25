/**
 * @file USONIC_private.h
 * @author Ahmed M.Abdelfattah (ahmedm7md24@gmail.com)
 * @brief  
 * @version 1
 * @date 2020-12-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef USONIC_private_H
#define USONIC_private_H

#define DTCNUM                     5
#define FAILED_THRESHOLD           127
#define PASSED_THRESHOLD           -128
#define AGING_THRESHOLD            255


#define RED_LIGHT                   1
#define YELLOW_LIGHT                2
#define GREEN_LIGHT                 3

//static void voidTimeOut (void);



static dtcItem_t dtc_usonic[DTCNUM];


#endif
