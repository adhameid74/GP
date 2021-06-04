/**
 * @file SYSTICK_program.c
 * @author Ahmed M.Abdelfattah (ahmedm7md24@gmail.com)
 * @brief 
 * @version 1
 * @date 2021-05-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SYSTICK_INTERFACE.h"
#include "SYSTICK_PRIVATE.h"
#include "SYSTICK_CONFIG.h"

void (*Callback)(void);
u8 Local_u8Flag;

void SYSTICK_voidInit (void)
{
    #if SYSTICK_CLK==AHB
    SET_BIT(SYSTICK -> CTRL,2);
    #elif SYSTICK_CLK==AHB_BY_8
    CLR_BIT(SYSTICK -> CTRL,2);
    #else
    #error "Wrong SYSTICK_CLK Selections"
    #endif
    CLR_BIT(SYSTICK-> CTRL,0);
}


void SYSTICK_voidSetIntervalPeriodic (u32 copy_u32CounterValue,void (*Copy_ptr)(void) )
{
    CLR_BIT(SYSTICK-> CTRL,0);
	SYSTICK->LOAD =0;
	SYSTICK ->VAL =0;
    Local_u8Flag=SetInternalPeriodic;
	SYSTICK ->LOAD =0x00FFFFFF & copy_u32CounterValue;
    SET_BIT(SYSTICK-> CTRL,0);
    Callback=Copy_ptr;
    SET_BIT(SYSTICK -> CTRL,1);
}

void SYSTICK_voidSetIntervalSingle (u32 copy_u32CounterValue,void (*Copy_ptr)(void))
{
	CLR_BIT(SYSTICK-> CTRL,0);
	SYSTICK->LOAD =0;
	SYSTICK ->VAL =0;
    Local_u8Flag=SetInternalSingle;
    SYSTICK ->LOAD = 0x00FFFFFF & copy_u32CounterValue;
    SET_BIT(SYSTICK-> CTRL,0);
    Callback=Copy_ptr;
    SET_BIT(SYSTICK -> CTRL,1);
}


void SYSTICK_voidStopTimer (void)
{
    CLR_BIT(SYSTICK-> CTRL,0);
    SYSTICK->LOAD =0;
    SYSTICK->VAL =0;
}

void SYSTICK_voidSetBusyWait (u32 copy_u32CounterValue)
{
	SYSTICK->LOAD = 0x00FFFFFF & copy_u32CounterValue;
	SET_BIT(SYSTICK-> CTRL,0);
	while(GET_BIT(SYSTICK -> CTRL,16)==0)
	{

	}
	CLR_BIT(SYSTICK-> CTRL,0);
	SYSTICK->LOAD =0;
	SYSTICK ->VAL =0;
}

u32 SYSTICK_u32GetElapsedTime(void)
{
	return (SYSTICK ->LOAD - SYSTICK ->VAL);
}
u32 SYSTICK_u32GetERemainingTime(void)
{
	return SYSTICK ->VAL;
}

void SysTick_Handler(void)
{
    Callback();
    if(Local_u8Flag==SetInternalSingle){
    SYSTICK_voidStopTimer();
    }
}
