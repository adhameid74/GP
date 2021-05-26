/**
 * @file SPEED_program.c
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief Program file of speed sensor
 * @version 2.01
 * @date 26-05-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_interface.h"

#include "SPEED_interface.h"
#include "SPEED_private.h"
#include "SPEED_config.h"

void SPEED_voidGetReadingAsynch()
{
	SPEED_u16Reading = TIMER_u16GetElapsedTime(TIMER_ID);
	SPEED_u16Reading = ( (SPEED_u16Reading * 1000) / (NUM_OF_HOLES * EVALUATION_TIME) );
	TIMER_voidSetResetTimer(TIMER_ID, TIMER_RESET, 0);
	TIMER_voidEnableExternalClockSource(TIMER_ID, ((TIMER_ID*10)+21));
}