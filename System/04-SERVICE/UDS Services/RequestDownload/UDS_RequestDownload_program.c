/**
 * @file UDS_RequestDownload_program.c
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

#include "UDS_RequestDownload_interface.h"
#include "UDS_RequestDownload_private.h"
#include "UDS_RequestDownload_config.h"

void UDS_voidRequestDownload(INDICATION_SDU ReceivedMessage)
{
	u8 Local_u8AddressFormat, Local_u8LengthFormat;
	if (ReceivedMessage.Length < 3)
	{
		SendNegResponse(incorrectMessageLengthOrInvalidFormat);
		return;
	}
	if ( (ReceivedMessage.MessageData[1] != 0) || (ReceivedMessage.MessageData[2] == 0))
	{
		SendNegResponse(requestOutOfRange);
		return;
	}
	Local_u8AddressFormat = (ReceivedMessage.MessageData[2]) & (0b00001111);
	Local_u8LengthFormat = (((ReceivedMessage.MessageData[2]) & (0b11110000)) >> 4);
}

static void SendPosResponse()
{
	REQUEST_SDU PositiveResponse;
	PositiveResponse.SA = SOURCE_ADDRESS;
	PositiveResponse.TA = TARGET_ADDRESS;
	PositiveResponse.Length = POS_RESPONSE_LENGTH;
	u8 MSG[POS_RESPONSE_LENGTH] = {POS_RESPONSE_SID , lengthFormatIdentifier, maxNumberOfBlockLength};
	PositiveResponse.MessageData = MSG;
	DoCAN_voidRequestUsData(PositiveResponse);
}

static void SendNegResponse(u8 Copy_u8NRC)
{
	REQUEST_SDU NegativeResponse;
	NegativeResponse.SA = SOURCE_ADDRESS;
	NegativeResponse.TA = TARGET_ADDRESS;
	NegativeResponse.Length = NRC_LENGTH;
	u8 MSG[NRC_LENGTH] = {NRC_ID , SID , Copy_u8NRC};
	NegativeResponse.MessageData = MSG;
	DoCAN_voidRequestUsData(NegativeResponse);
}
