/**********************************************/
/* Author   : Eslam Khaled                    */
/* Date     : 8 Aug 2020                      */
/* Version  : V01                             */
/**********************************************/
#ifndef _RCC_CONFIG_H
#define _RCC_CONFIG_H

#define RCC_CLOCK_TYPE RCC_HSI              // RCC_HSI is default (you can change it)
/* Options */
/*
 RCC_HSE_CRYSTAL 
 RCC_HSE_RC      
 RCC_HSI         
 RCC_PLL         
*/
#if RCC_CLOCK_TYPE == RCC_PLL
    #define PLL_INPUT RCC_PLL_HSI_DIV_2     // RCC_PLL_HSI_DIV_2 is default (you can change it)
#endif
/* Options */
/*
 RCC_PLL_HSI_DIV_2 
 RCC_PLL_HSE_DIV_2     
 RCC_HSE                 
*/

#if RCC_CLOCK_TYPE == RCC_PLL
    #define RCC_MUL_VALUE 2                 // 2 is default (you can change it)
#endif
/* Options */
/*
 2 to 16              
*/

#endif