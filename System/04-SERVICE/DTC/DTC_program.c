/**
 * @file DTC_program.c
 * @author Ahmed M.Abdelfattah (ahmedm7md24@gmail.com)
 * @brief  
 * @version 1
 * @date 2021-5-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EEPROM_interface.h"

#include "DTC_interface.h"
#include "DTC_private.h"
#include "DTC_config.h"

void dtcSetFault(dtcItem_t* it)
{
	it->Status.TestFailed = 1;
	it->Status.ConfirmedDTC = 1;
	it->Status.TestFailedThisOperationCycle = 1;
	it->Status.TestNotCompletedThisOperationCycle = 0;
	it->Status.WarningIndicatorRequested = it->Property->Bits.WarningIndicatorRequested;
}

void dtcSetPassed(dtcItem_t* it)
{
	it->Status.TestFailed = 0;
	it->Status.ConfirmedDTC = 1;
	it->Status.TestFailedThisOperationCycle = 0;
	it->Status.TestNotCompletedThisOperationCycle = 0;
	it->Status.WarningIndicatorRequested = it->Property->Bits.WarningIndicatorRequested;
}

u8 DTC_u8DetectFault(dtcItem_t* it,  u8 isFault)
{
	u8 StatusBits;
	if(isFault)
	{
		if(it->FaultDetectionCounter < it->Property->TestFailedThreshold)
		{
			if(it->FaultDetectionCounter < 0)
				it->FaultDetectionCounter = 0;
			else
				it->FaultDetectionCounter++;
		}
		else
		{
			if(!it->Status.TestFailed)
			{
				dtcSetFault(it);
				StatusBits=0x07;
				StatusBits|=( it->Property->Bits.WarningIndicatorRequested<<(3));
				HEEPROM_voidWriteByte(EEPROM_ADDRESS, it->Property->Code, StatusBits);
				return DTC_TEST_RESULT_FAILED;
			}
		}
	}
	else
	{
		if(it->FaultDetectionCounter > it->Property->TestPassedThreshold)
		{
			if(it->FaultDetectionCounter > 0)
				it->FaultDetectionCounter = 0;
			else
				it->FaultDetectionCounter--;
		}
		else
		{
			if(it->Status.TestFailed || it->Status.TestNotCompletedThisOperationCycle)
			{
				it->Status.TestFailed = 0;
				it->Status.TestNotCompletedThisOperationCycle = 0;
				if (it->Status.TestFailedThisOperationCycle)
				{
					if(it->Property->Bits.AutoRestore)
					{
						dtcSetPassed(it);
						StatusBits=0x02;
						StatusBits|=( it->Property->Bits.WarningIndicatorRequested<<(3));
						HEEPROM_voidWriteByte(EEPROM_ADDRESS, it->Property->Code, StatusBits);
						return DTC_TEST_RESULT_PASSED;
					}
					else if(it->Property->Bits.IsCritical)                  
					{
						return DTC_TEST_RESULT_UNCOMPLITED;
					}
				}
				else
				{
					dtcSetPassed(it);
					StatusBits=0x02;
					StatusBits|=( it->Property->Bits.WarningIndicatorRequested<<(3));
					HEEPROM_voidWriteByte(EEPROM_ADDRESS, it->Property->Code, StatusBits);
					return DTC_TEST_RESULT_PASSED;
				}
			}
			else
			{
				StatusBits=0x02;
				StatusBits|=( it->Status.TestFailedThisOperationCycle<<(2));
				StatusBits|=( it->Property->Bits.WarningIndicatorRequested<<(3));
				HEEPROM_voidWriteByte(EEPROM_ADDRESS, it->Property->Code, StatusBits);
				return DTC_TEST_RESULT_PASSED;
			}
		}
	}
	return DTC_TEST_RESULT_UNCOMPLITED;
}
