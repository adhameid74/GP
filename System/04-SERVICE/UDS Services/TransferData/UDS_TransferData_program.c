/**
 * @file UDS_TransferData_program.c
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 12-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DoCAN_interface.h"

#include "UDS_TransferData_interface.h"
#include "UDS_TransferData_private.h"
#include "UDS_TransferData_config.h"

void UDS_voidTransferData(INDICATION_SDU ReceivedMessage)
{

}

static void SendPosResponse()
{
	REQUEST_SDU PositiveResponse;
	PositiveResponse.SA = SOURCE_ADDRESS;
	PositiveResponse.TA = TARGET_ADDRESS;
	PositiveResponse.Length = POS_RESPONSE_LENGTH;
	u8 MSG[POS_RESPONSE_LENGTH] = {POS_RESPONSE_SID , 0};
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
