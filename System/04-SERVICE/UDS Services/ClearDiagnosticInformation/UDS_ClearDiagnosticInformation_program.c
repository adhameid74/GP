/**
 * @file UDS_ClearDiagnosticInformation_program.c
 * @author Ahmed M.Abdelfattah (ahmedm7md24@gmail.com)
 * @brief  
 * @version 1
 * @date 2020-4-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EEPROM_interface.h"

#include "DoCAN_interface.h"
#include "UDSHandler_interface.h"
#include "DTC_interface.h"

#include "UDS_ClearDiagnosticInformation_interface.h"
#include "UDS_ClearDiagnosticInformation_private.h"
#include "UDS_ClearDiagnosticInformation_config.h"

void UDS_voidClearDiagnosticInformation(INDICATION_SDU *message)
{

    if (message->Length.u12 != 1)
	{
		UDSHandler_voidSendNegResponse(ClearDiagnosticInformation,incorrectMessageLengthOrInvalidFormat);
		return ;
	}
    HEEPROM_voidDeleteMultipleBytes(EEPROM_ADDRESS, DTC_EEPROM_START_ADDRESS, DTC_NUMBER);
	u8 Local_Au8PositiveResponce[1]={POS_RESPONSE_SID};
	UDSHandler_voidSendPosResponse(Local_Au8PositiveResponce,1);
}



