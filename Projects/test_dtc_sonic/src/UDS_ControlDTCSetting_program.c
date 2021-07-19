/**
 * @file UDS_ControlDTCSetting_program.c
 * @author Ahmed M.Abdelfattah (ahmedm7md24@gmail.com)
 * @brief  
 * @version 1
 * @date 2020-7-13
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DoCAN_interface.h"
#include "UDSHandler_interface.h"

#include "UDS_ControlDTCSetting_interface.h"
#include "UDS_ControlDTCSetting_private.h"
#include "UDS_ControlDTCSetting_config.h"

u8 UDS_u8DTCSetting = DTC_SETTING_ON;

void UDS_voidControlDTCSetting(INDICATION_SDU* ReceivedMessage)
{
    if (ReceivedMessage->Length.u12 != 2)
	{
		UDSHandler_voidSendNegResponse(ControlDTCSetting, incorrectMessageLengthOrInvalidFormat);
		return;
	}
    if(ReceivedMessage->MessageData[1] == DTC_SETTING_ON)
    {
        UDS_u8DTCSetting = DTC_SETTING_ON;
    }
    else if(ReceivedMessage->MessageData[1] == DTC_SETTING_OFF)
    {
        UDS_u8DTCSetting = DTC_SETTING_OFF;
    }
    else
    {
        UDSHandler_voidSendNegResponse(ControlDTCSetting, subFunctionNotSupported);
		return;
    }

    u8 Local_au8PosResponse[2] = {POS_RESPONSE_SID, ReceivedMessage->MessageData[1]};
	UDSHandler_voidSendPosResponse(Local_au8PosResponse, 2);
}
