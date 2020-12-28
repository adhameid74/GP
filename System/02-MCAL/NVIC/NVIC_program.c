/**
 * @file NVIC_program.c
 * @author Ahmed M.Abdelfattah (ahmedm7md24@gmail.com)
 * @brief 
 * @version 1
 * @date 2020-11-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "NVIC_interface.h"
#include "NVIC_private.h"
#include "NVIC_config.h"
/**
 * @brief This function set the corresponding bit in the ISER Register and enable the interrupt

 * 
 * @param Copy_u8IntNumber 
 */
void NVIC_voidEnableInterrupt   (u8 Copy_u8IntNumber)
{
    if(Copy_u8IntNumber<=31){
        NVIC_ISER0=(1<<Copy_u8IntNumber);
    }
    else if (Copy_u8IntNumber<=63)
    {
        Copy_u8IntNumber=Copy_u8IntNumber-32;
        NVIC_ISER1=(1<<Copy_u8IntNumber);
    }
    else
    {
        
    }
}
/**
 * @brief This function set the corresponding bit in the ICER Register and disable the interrupt
 * 
 * @param Copy_u8IntNumber 
 */
void NVIC_voidDisableInterrupt  (u8 Copy_u8IntNumber)
{
    if(Copy_u8IntNumber<=31){
        NVIC_ICER0=(1<<Copy_u8IntNumber);
    }
    else if (Copy_u8IntNumber<=63)
    {
        Copy_u8IntNumber=Copy_u8IntNumber-32;
        NVIC_ICER1=(1<<Copy_u8IntNumber);
    }
    else
    {
        
    }
}
/**
 * @brief This function set the corresponding bit in the ISPR Register and set the pending flag
 * 
 * @param Copy_u8IntNumber 
 */
void NVIC_voidSetPendingFlag    (u8 Copy_u8IntNumber)
{
    if(Copy_u8IntNumber<=31){
        NVIC_ISPR0=(1<<Copy_u8IntNumber);
    }
    else if (Copy_u8IntNumber<=63)
    {
        Copy_u8IntNumber=Copy_u8IntNumber-32;
        NVIC_ISPR1=(1<<Copy_u8IntNumber);
    }
    else
    {
        
    }
}
/**
 * @brief This function set the corresponding bit in the ICPR Register and clear the pending flag
 * 
 * @param Copy_u8IntNumber 
 */
void NVIC_voidClearPendingFlag  (u8 Copy_u8IntNumber)
{
    if(Copy_u8IntNumber<=31){
        NVIC_ICPR0=(1<<Copy_u8IntNumber);
    }
    else if (Copy_u8IntNumber<=63)
    {
        Copy_u8IntNumber=Copy_u8IntNumber-32;
        NVIC_ICPR0=(1<<Copy_u8IntNumber);
    }
    else
    {
        
    }
}
/**
 * @brief This function get the Active flag of the corresponding interrupt
 * 
 * @param Copy_u8IntNumber 
 * @return u8 
 */
u8   NVIC_u8GetActiveFlag       (u8 Copy_u8IntNumber)
{
    u8 Local_u8ActiveFlag;
    if(Copy_u8IntNumber<=31){
        Local_u8ActiveFlag=GET_BIT(NVIC_IABR0,Copy_u8IntNumber);
    }
    else if (Copy_u8IntNumber<=63)
    {
        Copy_u8IntNumber=Copy_u8IntNumber-32;
        Local_u8ActiveFlag=GET_BIT(NVIC_IABR1,Copy_u8IntNumber);
    }
    else
    {
        
    }
    return Local_u8ActiveFlag;
}
/**
 * @brief This function used to change the periority of an interrupt
 * 
 * @param Copy_u8IntNumber 
 * @param Copy_u8GroupPriority 
 * @param Copy_u8SupPriority 
 * @param Copy_u32Channel 
 */
void NVIC_voidSetPriority  (u8 Copy_u8IntNumber ,u8 Copy_u8GroupPriority ,u8 Copy_u8SupPriority ,u32 Copy_u32Channel)
{
    u8 Local_u8Priority;
    Local_u8Priority = Copy_u8SupPriority|(Copy_u8GroupPriority<<((Copy_u32Channel-NVIC_4GROUP_0SUB)/256));

    if (Copy_u8IntNumber >= 0)
    {
        NVIC_IPR[Copy_u8IntNumber] = Local_u8Priority << 4;
    }
    SCB_AIRCR = Copy_u32Channel;    
}