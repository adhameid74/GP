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

#include "UDS_TransferData_interface.h"
#include "EEPROM_interface.h"

#include "UDS_RequestDownload_interface.h"
#include "UDS_RequestDownload_private.h"
#include "UDS_RequestDownload_config.h"

u32 RequestDownload_u32Size;
u8 RequestDownload_u8ActiveFlag = 0;

void UDS_voidRequestDownload(INDICATION_SDU* ReceivedMessage)
{
	u8 Local_u8AddressFormat, Local_u8LengthFormat;
	RequestDownload_u32Size = 0;

	if ( RequestDownload_u8ActiveFlag == 1 )
	{
		UDSHandler_voidSendNegResponse(RequestDownload, conditionsNotCorrect);
		return;
	}
	
	if (ReceivedMessage->Length.u12 < 3)
	{
		UDSHandler_voidSendNegResponse(RequestDownload, incorrectMessageLengthOrInvalidFormat);
		return;
	}

	Local_u8AddressFormat = (ReceivedMessage->MessageData[2]) & (0b00001111);
	Local_u8LengthFormat = (((ReceivedMessage->MessageData[2]) & (0b11110000)) >> 4);
	if ( (Local_u8AddressFormat != 4) || (Local_u8LengthFormat == 0) || (ReceivedMessage->MessageData[1] != 0))
	{
		UDSHandler_voidSendNegResponse(RequestDownload, requestOutOfRange);
		return;
	}
	if ( ReceivedMessage->Length.u12 != (Local_u8AddressFormat+Local_u8LengthFormat+3) )
	{
		UDSHandler_voidSendNegResponse(RequestDownload, incorrectMessageLengthOrInvalidFormat);
		return;
	}
	for (u8 Local_u8Counter = 0; Local_u8Counter < Local_u8LengthFormat; Local_u8Counter++)
	{
		RequestDownload_u32Size |= (ReceivedMessage->MessageData[3+Local_u8AddressFormat+Local_u8Counter]) << ((Local_u8LengthFormat*8)- (8*(Local_u8Counter+1)));
	}
	if ( (ReceivedMessage->MessageData[3] != 0x08) || (ReceivedMessage->MessageData[4] != 0) || (ReceivedMessage->MessageData[5] != 0x10) || (ReceivedMessage->MessageData[6] != 0) || (RequestDownload_u32Size == 0) )
	{
		UDSHandler_voidSendNegResponse(RequestDownload, requestOutOfRange);
		return;
	}

	RequestDownload_u8ActiveFlag = 1;
	TransferData_u8ExpectedBSC = 1;
	TransferData_u32ReceivedBytes = 0;
	TransferData_u16NumOfLines = 0;
	TransferData_u8NextAddress = EEPROM_APP_START_ADDRESS;

	u8 Local_au8PosResponse[3] = {POS_RESPONSE_SID, lengthFormatIdentifier, maxNumberOfBlockLength};
	UDSHandler_voidSendPosResponse(Local_au8PosResponse, 3);
}
