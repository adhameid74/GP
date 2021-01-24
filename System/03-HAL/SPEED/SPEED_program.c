/**
 * @file SPEED_program.c
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief Program file of speed sensor
 * @version 2.0
 * @date 28-12-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_interface.h"
#include "EXTI_interface.h"
#include "DIO_interface.h"

#include "SPEED_interface.h"
#include "SPEED_private.h"
#include "SPEED_config.h"

void SPEED_voidGetReadingSynch(SPEED_t* SENSOR)
{
	MODE = SYNCH;
	(SENSOR->Reading) = 0;
//	TIMER_voidSetIntervalSingle((SENSOR->TIMER_ID), (SENSOR->EVALUATION_TIME), CALL_BACK_FUNC);
	TIMER_voidSetTimerValue((SENSOR->TIMER_ID), (SENSOR->EVALUATION_TIME));
	TIMER_voidStartStopCount((SENSOR->TIMER_ID), TIMER_START);
	while(TIMER_u16GetRemainingTime((SENSOR->TIMER_ID)) != 0)
	{
		if((Dio_ReadChannel(SENSOR->PIN)) == 1)
		{
			(SENSOR->Reading)++;
			while((Dio_ReadChannel(SENSOR->PIN)) == 1);
		}
	}
	TIMER_voidSetResetTimer((SENSOR->TIMER_ID), TIMER_START, 0);
	(SENSOR->Reading) = (SENSOR->Reading)/(SENSOR->NUM_OF_HOLES);
	(SENSOR->Reading) = ((SENSOR->Reading)*1000)/((SENSOR->EVALUATION_TIME) * (SENSOR->TICK_TIME));
}

void SPEED_voidGetReadingAsynch(SPEED_t* SENSOR, void (*Copy_funcptr) (void))
{
	MODE = ASYNCH;
	u8 Local_u8Line = (SENSOR->PIN)%16;
	(SENSOR->Reading) = 0;
	Reading = &(SENSOR->Reading);
	EXTI_voidSetSignalLatch(Local_u8Line, EXTI_RISING);
	EXTI_voidSetCallBack(CALL_BACK_FUNC, Local_u8Line);
	TIMER_voidSetIntervalSingle((SENSOR->TIMER_ID), (SENSOR->EVALUATION_TIME), Copy_funcptr);
	EXTI_voidEnableEXTI(Local_u8Line);
}

static void CALL_BACK_FUNC()
{
	if(MODE == SYNCH)
	{
		MODE = TIMER_DONE;
	}
	else if(MODE == ASYNCH)
	{
		(*Reading)++;
	}
}
