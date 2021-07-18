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

#include "DTC_interface.h"

#include "CAR_interface.h"
#include "UDS_InputOutputControlByIdentifier_interface.h"

#include "SPEED_interface.h"
#include "SPEED_private.h"
#include "SPEED_config.h"

u16 SPEED_u16DefaultValue = 2500;
u16 SPEED_u16Reading = 0;

void SPEED_voidGetReadingAsynch()
{
	u16 Local_u16ExpectedReading;
	if(Flag == 0)
	{
		for (u8 Local_u8Counter = 0; Local_u8Counter < DTCNUM; Local_u8Counter++)
		{
			SPEED_DTC[Local_u8Counter].Status = DTC_STATUS_MASK;
			SPEED_DTC[Local_u8Counter].FaultDetectionCounter = 0;
			SPEED_DTC[Local_u8Counter].Property = &SPEED_PROP[Local_u8Counter];
			SPEED_DTC[Local_u8Counter].Property->Bits = 0;
			SPEED_DTC[Local_u8Counter].Property->Code = DTC_SpeedNotMatched + Local_u8Counter;
			SPEED_DTC[Local_u8Counter].Property->TestFailedThreshold = FAILED_THRESHOLD;
			SPEED_DTC[Local_u8Counter].Property->TestPassedThreshold = PASSED_THRESHOLD;
			SPEED_DTC[Local_u8Counter].Property->AgingThreshold = AGING_THRESHOLD;
		}
		Flag = 1;
	}

	SPEED_u16Reading = TIMER_u16GetElapsedTime(TIMER_ID);
	SPEED_u16Reading = ( (SPEED_u16Reading * 1000) / (NUM_OF_HOLES * EVALUATION_TIME) );
	TIMER_voidSetResetTimer(TIMER_ID, TIMER_RESET, 0);
	TIMER_voidEnableExternalClockSource(TIMER_ID, ((TIMER_ID*10)+22));

	switch(SPEED_whatShouldIdo)
	{
		case returnControlToECU:
			SPEED_u16PVT = SPEED_u16Reading;
			break;
		case resetToDefault:
			SPEED_u16PVT = SPEED_u16Reading;
			SPEED_u16Reading = SPEED_u16DefaultValue;
			break;
		case freezeCurrentState:
			SPEED_u16Reading = SPEED_u16PVT;
			break;
		case shortTermAdjustment:
			SPEED_u16Reading =  SPEED_valueToUse;
			break;
		default:
    		break;
	}

	if( (CAR_SPEED_CurrentValue > SPEED_LOW_THRESHOLD) && (SPEED_u16Reading == 0) )
	{
		DTC_u8DetectFault(&SPEED_DTC[2], 1);
		return;
	}
	DTC_u8DetectFault(&SPEED_DTC[2], 0);

	Local_u16ExpectedReading = CAR_SPEED_CurrentValue*12; // Habd equation
	if ( (SPEED_u16Reading > (Local_u16ExpectedReading+20)) || (SPEED_u16Reading < (Local_u16ExpectedReading-20)) )
	{
		DTC_u8DetectFault(&SPEED_DTC[0], 1);
	}
	DTC_u8DetectFault(&SPEED_DTC[0], 0);

	if ( SPEED_u16Reading > SPEED_LIMIT )
	{
		DTC_u8DetectFault(&SPEED_DTC[1], 1);
	}
	DTC_u8DetectFault(&SPEED_DTC[1], 0);


}