/**
 * @file UDSHandler_program.c
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 24-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DoCAN_interface.h"

#include "UDS_ClearDiagnosticInformation_interface.h"
#include "UDS_DiagnosticSessionControl_interface.h"
#include "UDS_ReadDataById_interface.h"
#include "UDS_WriteDataById_interface.h"
#include "UDS_ReadDTCInformation_interface.h"
#include "UDS_RequestDownload_interface.h"
#include "UDS_RequestTransferExit_interface.h"
#include "UDS_TesterPresent_interface.h"
#include "UDS_TransferData_interface.h"
#include "UDS_ECUReset_interface.h"
#include "UDS_InputOutputControlByIdentifier_interface.h"

#include "UDSHandler_interface.h"
#include "UDSHandler_private.h"
#include "UDSHandler_config.h"

void UDSHandler_voidCallService(INDICATION_SDU ReceivedMessage)
{
	if (ReceivedMessage.MessageData[0] == DiagnosticSessionControl)
	{
		UDS_voidDiagnosticSessionControl(&ReceivedMessage);
	}
	else if (ReceivedMessage.MessageData[0] == ClearDiagnosticInformation)
	{
		UDS_u8ClearDiagnosticInformation(ReceivedMessage);
	}
	else if (ReceivedMessage.MessageData[0] == ReadDTCInformation)
	{
		UDS_u8ReadDTCInformation(ReceivedMessage);
	}
	else if (ReceivedMessage.MessageData[0] == ReadDataByIdentifier)
	{
		UDS_voidReadDataById(&ReceivedMessage);
	}
	else if (ReceivedMessage.MessageData[0] == RequestDownload)
	{
		UDS_voidRequestDownload(&ReceivedMessage);
	}
	else if (ReceivedMessage.MessageData[0] == TransferData)
	{
		UDS_voidTransferData(&ReceivedMessage);
	}
	else if (ReceivedMessage.MessageData[0] == RequestTransferExit)
	{
		UDS_voidRequestTransferExit(&ReceivedMessage);
	}
	else if (ReceivedMessage.MessageData[0] == TesterPresent)
	{
		UDS_voidTesterPresent(&ReceivedMessage);
	}
	else if (ReceivedMessage.MessageData[0] == WriteDataByIdentifier)
	{
		UDS_voidWriteDataById(&ReceivedMessage);
	}
	else
	{
		UDSHandler_voidSendNegResponse(ReceivedMessage.MessageData[0], serviceNotSupported);
	}
}

void UDSHandler_voidSendNegResponse(u8 Copy_u8SID, u8 Copy_u8NRC)
{
	REQUEST_SDU NegativeResponse;
	NegativeResponse.SA = SOURCE_ADDRESS;
	NegativeResponse.TA = TARGET_ADDRESS;
	NegativeResponse.Length.u12 = NRC_LENGTH;
	u8 Local_au8Data[NRC_LENGTH] = {NRC_ID , Copy_u8SID , Copy_u8NRC};
	NegativeResponse.MessageData = Local_au8Data;
	DoCAN_voidRequestUsData(NegativeResponse);
}

void UDSHandler_voidSendPosResponse(u8* Copy_pu8Message, u8 Copy_u8Length)
{
	REQUEST_SDU PositiveResponse;
	PositiveResponse.SA = SOURCE_ADDRESS;
	PositiveResponse.TA = TARGET_ADDRESS;
	PositiveResponse.Length.u12 = Copy_u8Length;
	PositiveResponse.MessageData = Copy_pu8Message;
	DoCAN_voidRequestUsData(PositiveResponse);
}
