/**
 * @file UDS_RequestTransferExit_program.c
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

#include "UDS_RequestTransferExit_interface.h"
#include "UDS_RequestTransferExit_private.h"
#include "UDS_RequestTransferExit_config.h"

void UDS_voidRequestTransferExit(INDICATION_SDU* ReceivedMessage)
{
	if (ReceivedMessage->Length != 1)
	{
		UDSHandler_voidSendNegResponse(SID, incorrectMessageLengthOrInvalidFormat);
		return;
	}
	u8 Local_au8PosResponse[1] = {POS_RESPONSE_SID};
	UDSHandler_voidSendPosResponse(Local_au8PosResponse, 1);
}