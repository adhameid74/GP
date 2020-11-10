/**
 * @file TIMER_private.h
 * @author Eslam Khaled (Eslam.kh.kamal@gmail.com)
 * @brief  TIMER private file
 * @version 0.1
 * @date 2020-11-10
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef TIMER_PRIVATE_H
#define TIMER_PRIVATE_H

// timer2 0x40000000
// timer3 0x40000400
// timer4 0x40000800
// timer5 0x40000C00
#define SINGLE_SHOT 0
#define MULTI_SHOT  1

#define TIM2_CR1            *((volatile u16 *)0x40000000)
#define TIM2_CR2            *((volatile u16 *)0x40000004)
#define TIM2_SMCR           *((volatile u16 *)0x40000008)
#define TIM2_DIER           *((volatile u16 *)0x4000000C)
#define TIM2_SR             *((volatile u16 *)0x40000010)
#define TIM2_EGR            *((volatile u16 *)0x40000014)
#define TIM2_CCMR1          *((volatile u16 *)0x40000018)
#define TIM2_CCMR2          *((volatile u16 *)0x4000001C)
#define TIM2_CCER           *((volatile u16 *)0x40000020)
#define TIM2_CNT            *((volatile u16 *)0x40000024)
#define TIM2_PSC            *((volatile u16 *)0x40000028)
#define TIM2_ARR            *((volatile u16 *)0x4000002C)
#define TIM2_CCR1           *((volatile u16 *)0x40000034)
#define TIM2_CCR2           *((volatile u16 *)0x40000038)
#define TIM2_CCR3           *((volatile u16 *)0x4000003C)
#define TIM2_CCR4           *((volatile u16 *)0x40000040)
#define TIM2_DCR            *((volatile u16 *)0x40000048)
#define TIM2_DMAR           *((volatile u16 *)0x4000004C)

#define TIM3_CR1            *((volatile u16 *)0x40000400)
#define TIM3_CR2            *((volatile u16 *)0x40000404)
#define TIM3_SMCR           *((volatile u16 *)0x40000408)
#define TIM3_DIER           *((volatile u16 *)0x4000040C)
#define TIM3_SR             *((volatile u16 *)0x40000410)
#define TIM3_EGR            *((volatile u16 *)0x40000414)
#define TIM3_CCMR1          *((volatile u16 *)0x40000418)
#define TIM3_CCMR2          *((volatile u16 *)0x4000041C)
#define TIM3_CCER           *((volatile u16 *)0x40000420)
#define TIM3_CNT            *((volatile u16 *)0x40000424)
#define TIM3_PSC            *((volatile u16 *)0x40000428)
#define TIM3_ARR            *((volatile u16 *)0x4000042C)
#define TIM3_CCR1           *((volatile u16 *)0x40000434)
#define TIM3_CCR2           *((volatile u16 *)0x40000438)
#define TIM3_CCR3           *((volatile u16 *)0x4000043C)
#define TIM3_CCR4           *((volatile u16 *)0x40000440)
#define TIM3_DCR            *((volatile u16 *)0x40000448)
#define TIM3_DMAR           *((volatile u16 *)0x4000044C)

#define TIM4_CR1            *((volatile u16 *)0x40000800)
#define TIM4_CR2            *((volatile u16 *)0x40000804)
#define TIM4_SMCR           *((volatile u16 *)0x40000808)
#define TIM4_DIER           *((volatile u16 *)0x4000080C)
#define TIM4_SR             *((volatile u16 *)0x40000810)
#define TIM4_EGR            *((volatile u16 *)0x40000814)
#define TIM4_CCMR1          *((volatile u16 *)0x40000818)
#define TIM4_CCMR2          *((volatile u16 *)0x4000081C)
#define TIM4_CCER           *((volatile u16 *)0x40000820)
#define TIM4_CNT            *((volatile u16 *)0x40000824)
#define TIM4_PSC            *((volatile u16 *)0x40000828)
#define TIM4_ARR            *((volatile u16 *)0x4000082C)
#define TIM4_CCR1           *((volatile u16 *)0x40000834)
#define TIM4_CCR2           *((volatile u16 *)0x40000838)
#define TIM4_CCR3           *((volatile u16 *)0x4000083C)
#define TIM4_CCR4           *((volatile u16 *)0x40000840)
#define TIM4_DCR            *((volatile u16 *)0x40000848)
#define TIM4_DMAR           *((volatile u16 *)0x4000084C)

#define TIM5_CR1            *((volatile u16 *)0x40000C00)
#define TIM5_CR2            *((volatile u16 *)0x40000C04)
#define TIM5_SMCR           *((volatile u16 *)0x40000C08)
#define TIM5_DIER           *((volatile u16 *)0x40000C0C)
#define TIM5_SR             *((volatile u16 *)0x40000C10)
#define TIM5_EGR            *((volatile u16 *)0x40000C14)
#define TIM5_CCMR1          *((volatile u16 *)0x40000C18)
#define TIM5_CCMR2          *((volatile u16 *)0x40000C1C)
#define TIM5_CCER           *((volatile u16 *)0x40000C20)
#define TIM5_CNT            *((volatile u16 *)0x40000C24)
#define TIM5_PSC            *((volatile u16 *)0x40000C28)
#define TIM5_ARR            *((volatile u16 *)0x40000C2C)
#define TIM5_CCR1           *((volatile u16 *)0x40000C34)
#define TIM5_CCR2           *((volatile u16 *)0x40000C38)
#define TIM5_CCR3           *((volatile u16 *)0x40000C3C)
#define TIM5_CCR4           *((volatile u16 *)0x40000C40)
#define TIM5_DCR            *((volatile u16 *)0x40000C48)
#define TIM5_DMAR           *((volatile u16 *)0x40000C4C)

#endif