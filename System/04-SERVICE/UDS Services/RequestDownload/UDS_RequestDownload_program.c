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

void UDS_voidRequestDownload(INDICATION_SDU ReceivedMessage)
{
	u8 Local_u8AddressFormat, Local_u8LengthFormat;
	if (ReceivedMessage.Length < 3)
	{
		UDSHandler_voidSendNegResponse(SID, incorrectMessageLengthOrInvalidFormat);
		return;
	}
	if ( (ReceivedMessage.MessageData[1] != 0) || (ReceivedMessage.MessageData[2] == 0))
	{
		UDSHandler_voidSendNegResponse(SID, requestOutOfRange);
		return;
	}
	Local_u8AddressFormat = (ReceivedMessage.MessageData[2]) & (0b00001111);
	Local_u8LengthFormat = (((ReceivedMessage.MessageData[2]) & (0b11110000)) >> 4);
}