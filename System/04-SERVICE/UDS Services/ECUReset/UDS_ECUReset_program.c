/**
 * @file UDS_ECUReset_program.c
 * @author Eslam Khaled (eslam.kh.kamal@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DoCAN_interface.h"
#include "UDSHandler_interface.h"

#include "UDS_ECUReset_interface.h"
#include "UDS_ECUReset_private.h"
#include "UDS_ECUReset_config.h"

#include "NVIC_interface.h"

void UDS_voidECUReset(INDICATION_SDU* ReceivedMessage)
{
	if (ReceivedMessage.Length != 2)
	{
		UDSHandler_voidSendNegResponse(ECUReset, incorrectMessageLengthOrInvalidFormat);
		return;
	}
	else if(ReceivedMessage.MessageData[1] == softReset)
	{
		u8 Local_u8PosResponse[2] = {POS_RESPONSE_SID, softReset};
		UDSHandler_voidSendPosResponse(Local_u8PosResponse, 2);
		NVIC_voidSystemReset();
		return;
	}
	else
	{
		UDSHandler_voidSendNegResponse(ECUReset, subFunctionNotSupported);
		return;
	}
	
}