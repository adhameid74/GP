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

#include "EEPROM_interface.h"

#include "UDS_TransferData_interface.h"
#include "UDS_RequestDownload_interface.h"

#include "UDS_RequestTransferExit_interface.h"
#include "UDS_RequestTransferExit_private.h"
#include "UDS_RequestTransferExit_config.h"

void UDS_voidRequestTransferExit(INDICATION_SDU* ReceivedMessage)
{
	u8 Local_u8HighNibble, Local_u8LowNibble;
	Function_t BOOTLOADER = *(Function_t*)(BOOTLOADER_ADDRESS);
	if( (RequestDownload_u8ActiveFlag != 1) || (TransferData_u32ReceivedBytes != RequestDownload_u32Size) )
	{
		UDSHandler_voidSendNegResponse(RequestTransferExit, requestSequenceError);
		return;
	}
	if (ReceivedMessage->Length != 1)
	{
		UDSHandler_voidSendNegResponse(RequestTransferExit, incorrectMessageLengthOrInvalidFormat);
		return;
	}
	RequestDownload_u8ActiveFlag = 0;
	u8 Local_au8PosResponse[1] = {POS_RESPONSE_SID};
	Local_u8HighNibble = (u8)(TransferData_u16NumOfLines>>8);
	Local_u8LowNibble = (u8)(TransferData_u16NumOfLines & 0x00FF);
	HEEPROM_voidWriteByte(EEPROM_ADDRESS, EEPROM_NUM_OF_LINES_ADDRESS, Local_u8HighNibble);
	HEEPROM_voidWriteByte(EEPROM_ADDRESS, EEPROM_NUM_OF_LINES_ADDRESS-1, Local_u8LowNibble);
	UDSHandler_voidSendPosResponse(Local_au8PosResponse, 1);
	BOOTLOADER();
}