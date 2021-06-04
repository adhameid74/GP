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
#include "UDSHandler_interface.h"

#include "UDS_RequestDownload_interface.h"
#include "UDS_RequestDownload_private.h"
#include "UDS_RequestDownload_config.h"

void UDS_voidRequestDownload(INDICATION_SDU* ReceivedMessage)
{
	u8 Local_u8AddressFormat, Local_u8LengthFormat;
	if (ReceivedMessage->Length < 3)
	{
		UDSHandler_voidSendNegResponse(RequestDownload, incorrectMessageLengthOrInvalidFormat);
		return;
	}
	Local_u8AddressFormat = (ReceivedMessage->MessageData[2]) & (0b00001111);
	Local_u8LengthFormat = (((ReceivedMessage->MessageData[2]) & (0b11110000)) >> 4);
	if ( (Local_u8AddressFormat != 1) || (Local_u8LengthFormat == 0) || (ReceivedMessage->MessageData[1] != 0))
	{
		UDSHandler_voidSendNegResponse(RequestDownload, requestOutOfRange);
		return;
	}
	if ( ReceivedMessage->Length != (Local_u8AddressFormat+Local_u8LengthFormat+3) )
	{
		UDSHandler_voidSendNegResponse(RequestDownload, incorrectMessageLengthOrInvalidFormat);
		return;
	}
	if ( (ReceivedMessage->MessageData[3] != FLASH_APP_ADDRESS) || (ReceivedMessage->MessageData[4] == 0) )
	{
		UDSHandler_voidSendNegResponse(RequestDownload, requestOutOfRange);
		return;
	}
	u8 Local_au8PosResponse[3] = {POS_RESPONSE_SID, lengthFormatIdentifier, maxNumberOfBlockLength};
	UDSHandler_voidSendPosResponse(Local_au8PosResponse, 3);
}