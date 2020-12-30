/**
 * @file EXTI_program.c
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 0.1
 * @date 10-11-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"

/* Call Back Functions Array */
static void (*EXTI_CallBack[16]) (void) = {NULL};

void EXTI_voidEnableEXTI(u8 Copy_u8Line)
{
	if (Copy_u8Line > EXTI_LINE15)
	{
		/* Error */
	}
	else
	{
		SET_BIT(EXTI->IMR, Copy_u8Line);
	}
}

void EXTI_voidDisableEXTI(u8 Copy_u8Line)
{
	if(Copy_u8Line > EXTI_LINE15)
	{
		/* Error */
	}
	else
	{
		CLR_BIT(EXTI->IMR, Copy_u8Line);
	}
}

void EXTI_voidSwTrigger(u8 Copy_u8Line)
{
	if(Copy_u8Line > EXTI_LINE15)
	{
		/* Error */
	}
	else
	{
		SET_BIT(EXTI->SWIER, Copy_u8Line);
	}
}

void EXTI_voidSetSignalLatch(u8 Copy_u8Line, u8 Copy_u8Mode)
{
	if(Copy_u8Line > EXTI_LINE15)
	{
		/* Error */
	}
	else
	{
		if(Copy_u8Mode == EXTI_RISING)
		{
			SET_BIT(EXTI->RTSR, Copy_u8Line);
		}
		else if(Copy_u8Mode == EXTI_FALLING)
		{
			SET_BIT(EXTI->FTSR, Copy_u8Line);
		}
		else if(Copy_u8Mode == EXTI_ON_CHANGE)
		{
			SET_BIT(EXTI->RTSR, Copy_u8Line);
			SET_BIT(EXTI->FTSR, Copy_u8Line);
		}
		else
		{
			/* Error */
		}
	}
}

void EXTI_voidSetCallBack(void (*CallBackFunc) (void), u8 Copy_u8Line)
{
	if(CallBackFunc == NULL)
	{
		/* Error */
	}
	if(Copy_u8Line > EXTI_LINE15)
	{
		/* Error */
	}
	EXTI_CallBack[Copy_u8Line] = CallBackFunc;
}

/*	IRQ Handlers  */
void EXTI0_IRQHandler(void)
{
	if (EXTI_CallBack[0] != NULL)
	{
		(*EXTI_CallBack[0])();
	}
	SET_BIT(EXTI->PR, 0);
}

void EXTI1_IRQHandler(void)
{
	if (EXTI_CallBack[1] != NULL)
	{
		(*EXTI_CallBack[1])();
	}
	SET_BIT(EXTI->PR, 1);
}

void EXTI2_IRQHandler(void)
{
	if (EXTI_CallBack[2] != NULL)
	{
		(*EXTI_CallBack[2])();
	}
	SET_BIT(EXTI->PR, 2);
}

void EXTI3_IRQHandler(void)
{
	if (EXTI_CallBack[3] != NULL)
	{
		(*EXTI_CallBack[3])();
	}
	SET_BIT(EXTI->PR, 3);
}

void EXTI4_IRQHandler(void)
{
	if (EXTI_CallBack[4] != NULL)
	{
		(*EXTI_CallBack[4])();
	}
	SET_BIT(EXTI->PR, 4);
}

void EXTI9_5_IRQHandler (void)
{
	for (u8 Local_u8Counter = 5; Local_u8Counter < 10; Local_u8Counter++)
	{
		if( (GET_BIT(EXTI->PR, Local_u8Counter)) == 1)
		{
			if (EXTI_CallBack[Local_u8Counter] != NULL)
			{
				(*EXTI_CallBack[Local_u8Counter])();
			}
			SET_BIT(EXTI->PR, Local_u8Counter);
			break;
		}
	}
}

void EXTI15_10_IRQHandler (void)
{
	for (u8 Local_u8Counter = 10; Local_u8Counter < 16; Local_u8Counter++)
	{
		if( (GET_BIT(EXTI->PR, Local_u8Counter)) == 1)
		{
			if (EXTI_CallBack[Local_u8Counter] != NULL)
			{
				(*EXTI_CallBack[Local_u8Counter])();
			}
			SET_BIT(EXTI->PR, Local_u8Counter);
			break;
		}
	}
}