/**
 * @file EXTI_interface.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 0.1
 * @date 10-11-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

/* EXTI lines definition */
#define EXTI_LINE0				0
#define EXTI_LINE1				1
#define EXTI_LINE2				2
#define EXTI_LINE3				3
#define EXTI_LINE4				4
#define EXTI_LINE5				5
#define EXTI_LINE6				6
#define EXTI_LINE7				7
#define EXTI_LINE8				8
#define EXTI_LINE9				9
#define EXTI_LINE10				10
#define EXTI_LINE11				11
#define EXTI_LINE12				12
#define EXTI_LINE13				13
#define EXTI_LINE14				14
#define EXTI_LINE15				15

/* EXTI modes definitions */
#define EXTI_RISING				0
#define EXTI_FALLING			1
#define EXTI_ON_CHANGE			2

/**
 * @brief This function enables a certain line external interrupt
 * 
 * @param Copy_u8Line External interrupt line number
 */

void EXTI_voidEnableEXTI(u8 Copy_u8Line);

/**
 * @brief This function disables a certain line external interrupt
 * 
 * @param Copy_u8Line External interrupt line number
 */

void EXTI_voidDisableEXTI(u8 Copy_u8Line);

/**
 * @brief This function activates a certain external interrupt line event
 * 
 * @param Copy_u8Line External interrupt line number
 */
void EXTI_voidSwTrigger(u8 Copy_u8Line);

/**
 * @brief This function sets a certain line external interrupt trigger
 * 
 * @param Copy_u8Line External interrupt line number
 * @param Copy_u8Mode External Interrupt Trigger Event
 */
void EXTI_voidSetSignalLatch(u8 Copy_u8Line, u8 Copy_u8Mode);

/**
 * @brief This function sets the function to be called in the event of a certain line external interrupt
 * 
 * @param CallBackFunc IRQ Pointer To Function
 * @param Copy_u8Line External interrupt line number
 */
void EXTI_voidSetCallBack(void (*CallBackFunc) (void), u8 Copy_u8Line);

#endif
