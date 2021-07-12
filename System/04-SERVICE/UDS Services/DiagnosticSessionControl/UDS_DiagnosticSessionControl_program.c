/**
 * @file UDS_DiagnosticSessionControl_program.c
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 04-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DoCAN_interface.h"
#include "UDSHandler_interface.h"

#include "UDS_DiagnosticSessionControl_interface.h"
#include "UDS_DiagnosticSessionControl_private.h"
#include "UDS_DiagnosticSessionControl_config.h"

u8 UDS_u8ActiveSession = UDS_DEFAULT_SESSION;
u8 UDS_u8SessionTimer = 0;

void UDS_voidDiagnosticSessionControl(INDICATION_SDU* ReceivedMessage)
{
	if (ReceivedMessage->Length.u12 != 2)
	{
		UDSHandler_voidSendNegResponse(SID, incorrectMessageLengthOrInvalidFormat);
		return;
	}
	if (UDS_DEFAULT_SESSION == ReceivedMessage->MessageData[1])
	{
		u8 Local_au8PosResponse[2] = {POS_RESPONSE_SID, UDS_DEFAULT_SESSION};
		UDSHandler_voidSendPosResponse(Local_au8PosResponse, 2);
		UDS_u8SessionTimer = 0;
		UDS_u8ActiveSession = UDS_DEFAULT_SESSION;
		return;
	}
	else if (UDS_PROGRAMMING_SESSION == ReceivedMessage->MessageData[1])
	{
		u8 Local_au8PosResponse[2] = {POS_RESPONSE_SID, UDS_PROGRAMMING_SESSION};
		UDSHandler_voidSendPosResponse(Local_au8PosResponse, 2);
		UDS_u8SessionTimer = 0;
		UDS_u8ActiveSession = UDS_PROGRAMMING_SESSION;
		return;
	}
	else if (UDS_EXTENDED_SESSION == ReceivedMessage->MessageData[1])
	{
		if (UDS_PROGRAMMING_SESSION == UDS_u8ActiveSession)
		{
			UDSHandler_voidSendNegResponse(SID, conditionsNotCorrect);
			return;
		}
		u8 Local_au8PosResponse[2] = {POS_RESPONSE_SID, UDS_EXTENDED_SESSION};
		UDSHandler_voidSendPosResponse(Local_au8PosResponse, 2);
		UDS_u8SessionTimer = 0;
		UDS_u8ActiveSession = UDS_EXTENDED_SESSION;
		return;
	}
	else if (UDS_SAFETY_SESSION == ReceivedMessage->MessageData[1])
	{
		if (UDS_PROGRAMMING_SESSION == UDS_u8ActiveSession)
		{
			UDSHandler_voidSendNegResponse(SID, conditionsNotCorrect);
			return;
		}
		u8 Local_au8PosResponse[2] = {POS_RESPONSE_SID, UDS_SAFETY_SESSION};
		UDSHandler_voidSendPosResponse(Local_au8PosResponse, 2);
		UDS_u8SessionTimer = 0;
		UDS_u8ActiveSession = UDS_SAFETY_SESSION;
		return;
	}
	else
	{
		UDSHandler_voidSendNegResponse(SID, subFunctionNotSupported);
		return;
	}
}
