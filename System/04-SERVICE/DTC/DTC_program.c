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

#include "UDS_ControlDTCSetting_interface.h"

#include "DTC_interface.h"
#include "DTC_private.h"
#include "DTC_config.h"

void dtcSetFault(dtcItem_t* it)
{
	it->Status |= 0x07;
	it->Status &= 0xEF;
	if ( GET_BIT(it->Property->Bits, BITS_WarningIndicatorRequested) )
	{
		SET_BIT(it->Status, STATUS_WarningIndicatorRequested);
	}
	else
	{
		CLR_BIT(it->Status, STATUS_WarningIndicatorRequested);
	}
}

void dtcSetPassed(dtcItem_t* it)
{
	it->Status = 0;
	SET_BIT(it->Status, STATUS_ConfirmedDTC);
	if ( GET_BIT(it->Property->Bits, BITS_WarningIndicatorRequested) )
	{
		SET_BIT(it->Status, STATUS_WarningIndicatorRequested);
	}
}

u8 DTC_u8DetectFault(dtcItem_t* it,  u8 isFault)
{
	if(UDS_u8DTCSetting == DTC_SETTING_ON)
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
				if(GET_BIT(it->Status, STATUS_TestFailed) == 0)
				{
					dtcSetFault(it);
					HEEPROM_voidWriteByte(EEPROM_ADDRESS, it->Property->Code, it->Status);
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
				if(GET_BIT(it->Status, STATUS_TestFailed) || GET_BIT(it->Status, STATUS_TestNotCompletedThisOperationCycle))
				{
					it->Status &= 0xEE;
					if (GET_BIT(it->Status, STATUS_TestFailedThisOperationCycle))
					{
						if(GET_BIT(it->Property->Bits, BITS_AutoRestore))
						{
							dtcSetPassed(it);
							HEEPROM_voidWriteByte(EEPROM_ADDRESS, it->Property->Code, it->Status);
							return DTC_TEST_RESULT_PASSED;
						}
						else if(GET_BIT(it->Property->Bits, BITS_IsCritical))                  
						{
							return DTC_TEST_RESULT_UNCOMPLITED;
						}
					}
					else
					{
						dtcSetPassed(it);
						HEEPROM_voidWriteByte(EEPROM_ADDRESS, it->Property->Code, it->Status);
						return DTC_TEST_RESULT_PASSED;
					}
				}
				else
				{
					HEEPROM_voidWriteByte(EEPROM_ADDRESS, it->Property->Code, it->Status);
					return DTC_TEST_RESULT_PASSED;
				}
			}
		}
		return DTC_TEST_RESULT_UNCOMPLITED;
	}
	else
	{
		return DTC_TEST_RESULT_UNCOMPLITED;
	}
}
