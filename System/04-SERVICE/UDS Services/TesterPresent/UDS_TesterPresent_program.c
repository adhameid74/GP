/**
 * @file UDS_TesterPresent_program.c
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 09-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DoCAN_interface.h"
#include "UDSHandler_interface.h"

#include "UDS_DiagnosticSessionControl_interface.h"

#include "UDS_TesterPresent_interface.h"
#include "UDS_TesterPresent_private.h"
#include "UDS_TesterPresent_config.h"

void UDS_voidTesterPresent(INDICATION_SDU* ReceivedMessage)
{
	if (ReceivedMessage.Length != 2)
	{
		UDSHandler_voidSendNegResponse(SID, incorrectMessageLengthOrInvalidFormat);
		return;
	}
	if(ReceivedMessage.MessageData[1] == zeroSubFunction)
	{
		u8 Local_au8PosResponse[2] = {POS_RESPONSE_SID, zeroSubFunction};
		UDSHandler_voidSendPosResponse(Local_au8PosResponse, 2);
		UDS_u8SessionTimer = 0;
		return;
	}
	else
	{
		UDSHandler_voidSendNegResponse(SID, subFunctionNotSupported);
		return;
	}
}