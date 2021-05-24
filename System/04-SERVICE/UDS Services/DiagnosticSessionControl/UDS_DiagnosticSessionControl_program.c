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

#include "UDS_DiagnosticSessionControl_interface.h"
#include "UDS_DiagnosticSessionControl_private.h"
#include "UDS_DiagnosticSessionControl_config.h"

void UDS_voidDiagnosticSessionControl(INDICATION_SDU ReceivedMessage)
{
	if (ReceivedMessage.Length != 2)
	{
		UDSHandler_voidSendNegResponse(SID, incorrectMessageLengthOrInvalidFormat);
		return;
	}
	if (UDS_DEFAULT_SESSION == ReceivedMessage.MessageData[1])
	{
		SendPosResponse(UDS_DEFAULT_SESSION);
		UDS_u8SessionTimer = 0;
		UDS_u8ActiveSession = UDS_DEFAULT_SESSION;
		return;
	}
	else if (UDS_PROGRAMMING_SESSION == ReceivedMessage.MessageData[1])
	{
		SendPosResponse(UDS_PROGRAMMING_SESSION);
		UDS_u8SessionTimer = 0;
		UDS_u8ActiveSession = UDS_PROGRAMMING_SESSION;
		return;
	}
	else if (UDS_EXTENDED_SESSION == ReceivedMessage.MessageData[1])
	{
		if (UDS_PROGRAMMING_SESSION == UDS_u8ActiveSession)
		{
			UDSHandler_voidSendNegResponse(SID, conditionsNotCorrect);
			return;
		}
		SendPosResponse(UDS_EXTENDED_SESSION);
		UDS_u8SessionTimer = 0;
		UDS_u8ActiveSession = UDS_EXTENDED_SESSION;
		return;
	}
	else if (UDS_SAFETY_SESSION == ReceivedMessage.MessageData[1])
	{
		if (UDS_PROGRAMMING_SESSION == UDS_u8ActiveSession)
		{
			UDSHandler_voidSendNegResponse(SID, conditionsNotCorrect);
			return;
		}
		SendPosResponse(UDS_SAFETY_SESSION);
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

static void SendPosResponse(u8 Copy_u8Session)
{
	REQUEST_SDU PositiveResponse;
	PositiveResponse.SA = SOURCE_ADDRESS;
	PositiveResponse.TA = TARGET_ADDRESS;
	PositiveResponse.Length = POS_RESPONSE_LENGTH;
	u8 MSG[POS_RESPONSE_LENGTH] = {POS_RESPONSE_SID , Copy_u8Session};
	PositiveResponse.MessageData = MSG;
	DoCAN_voidRequestUsData(PositiveResponse);
}