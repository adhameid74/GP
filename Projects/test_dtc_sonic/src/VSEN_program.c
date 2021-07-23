/**
 * @file VSEN_program.c
 * @author Abdallah Hassan (abdallahhashem029@gmail.com)
 * @brief source file for voltage sensor
 * @version 0.1
 * @date 2020-12-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"

#include "DTC_interface.h"

#include "VSEN_interface.h"
#include "VSEN_config.h"
#include "VSEN_private.h"


u16 VSEN_u16DefaultValue = 4500;

u16 VSEN_u16ReadVoltage()
{
	u16 Local_u16Value = 0;
	u16 Local_u16Vref = 0;

	if(Flag == 0)
	{
		for (u8 Local_u8Counter = 0; Local_u8Counter < DTCNUM; Local_u8Counter++)
		{
			VSEN_DTC[Local_u8Counter].Status = DTC_STATUS_MASK;
			VSEN_DTC[Local_u8Counter].FaultDetectionCounter = 0;
			VSEN_DTC[Local_u8Counter].Property = &VSEN_PROP[Local_u8Counter];
			VSEN_DTC[Local_u8Counter].Property->Bits = 0;
			VSEN_DTC[Local_u8Counter].Property->Code = DTC_VSenVoltageHigh + Local_u8Counter;
			VSEN_DTC[Local_u8Counter].Property->TestFailedThreshold = FAILED_THRESHOLD;
			VSEN_DTC[Local_u8Counter].Property->TestPassedThreshold = PASSED_THRESHOLD;
			VSEN_DTC[Local_u8Counter].Property->AgingThreshold = AGING_THRESHOLD;
		}
		Flag = 1;
	}

	#if VREF == VREF_3_3
		Local_u16Vref = 3300;
	#elif VREF == VREF_5
		Local_u16Vref = 5000;
	#else
		#error ("Wrong Configuration of VREF")
	#endif

	Local_u16Value = ADC_u16ReadRegularSync();
	if (Local_u16Value == 0)
	{
		DTC_u8DetectFault(&VSEN_DTC[2], 1);
		return 0;
	}
	DTC_u8DetectFault(&VSEN_DTC[2], 0);

	Local_u16Value = (u32)Local_u16Vref*(u32)Local_u16Value/ADC_RES;
	Local_u16Value = Local_u16Value*5;
	Local_u16Value = 0.6659*Local_u16Value + 86.18;

/*	switch(VOLT_whatShouldIdo)
	{
		case returnControlToECU:
			VSEN_u16PVT = Local_u16Value;
			return Local_u16Value;
			break;
		case resetToDefault:
			VSEN_u16PVT = Local_u16Value;
			return VSEN_u16DefaultValue;
			break;
		case freezeCurrentState:
			return VSEN_u16PVT;
			break;
		case shortTermAdjustment:
			return VOLT_valueToUse;
			break;
		default:
    		break;
	}*/

	if ( Local_u16Value > HIGH_THRESHOLD )
	{
		DTC_u8DetectFault(&VSEN_DTC[0], 1);
		DTC_u8DetectFault(&VSEN_DTC[1], 0);
	}
	else if ( Local_u16Value < LOW_THRESHOLD )
	{
		DTC_u8DetectFault(&VSEN_DTC[0], 0);
		DTC_u8DetectFault(&VSEN_DTC[1], 1);
	}
	else
	{
		DTC_u8DetectFault(&VSEN_DTC[0], 0);
		DTC_u8DetectFault(&VSEN_DTC[1], 0);
	}
	return Local_u16Value;
}
