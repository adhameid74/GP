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
#include "UDSHandler_interface.h"

#include "UDS_RequestDownload_interface.h"

#include "EEPROM_interface.h"

#include "UDS_TransferData_interface.h"
#include "UDS_TransferData_private.h"
#include "UDS_TransferData_config.h"

void UDS_voidTransferData(INDICATION_SDU* ReceivedMessage)
{
    u8 Local_u8Byte = 0;
    u16 Local_u16CheckSum = 0;

    if( RequestDownload_u8ActiveFlag != 1 )
    {
        UDSHandler_voidSendNegResponse(TransferData, requestSequenceError);
        return;
    }

    if ( RequestDownload_u32Size == TransferData_u32ReceivedBytes )
    {
        UDSHandler_voidSendNegResponse(TransferData, requestSequenceError);
        return;
    }

    if( (ReceivedMessage->Length < 3) || (ReceivedMessage->Length > maxNumberOfBlockLength) )
    {
        UDSHandler_voidSendNegResponse(TransferData, incorrectMessageLengthOrInvalidFormat);
        return;
    }

    if(ReceivedMessage->MessageData[1] == TransferData_u8ExpectedBSC)
    {
        if ( (RequestDownload_u32Size - TransferData_u32ReceivedBytes) < (ReceivedMessage->Length-2) )
        {
            UDSHandler_voidSendNegResponse(TransferData, transferDataSuspended);
            return;
        }

        if ( ReceivedMessage->MessageData[2] != ':' )
        {
            UDSHandler_voidSendNegResponse(TransferData, transferDataSuspended);
            return;
        }

        for (u8 Local_u8Counter = 3; Local_u8Counter < (ReceivedMessage->Length-2); Local_u8Counter+=2)
        {
            if ( (ReceivedMessage->MessageData[Local_u8Counter] == ':') || (ReceivedMessage->MessageData[Local_u8Counter+1] == ':'))
            {
                UDSHandler_voidSendNegResponse(TransferData, transferDataSuspended);
                return;
            }
            Local_u8Byte = ReceivedMessage->MessageData[Local_u8Counter] << 4;
            Local_u8Byte |= (ReceivedMessage->MessageData[Local_u8Counter+1] & 0x0F);
            HEEPROM_voidWriteByte(EEPROM_ADDRESS, TransferData_u8NextAddress++, Local_u8Byte);
            Local_u16CheckSum+=Local_u8Byte;
            Local_u8Byte = 0;
        }

        Local_u16CheckSum = ((~Local_u16CheckSum)+1)&0xFF;
        Local_u8Byte = ReceivedMessage->MessageData[ReceivedMessage->Length-2] << 4;
        Local_u8Byte |= (ReceivedMessage->MessageData[ReceivedMessage->Length-1] & 0x0F);
        if (Local_u8Byte != (u8)Local_u16CheckSum)
        {
            UDSHandler_voidSendNegResponse(TransferData, transferDataSuspended);
            return;
        }
        /*else
        {
            HEEPROM_voidWriteByte(EEPROM_ADDRESS, TransferData_u8NextAddress++, Local_u8Byte);
        }*/

        TransferData_u32ReceivedBytes+=(ReceivedMessage->Length-2);
        TransferData_u8ExpectedBSC++;
        TransferData_u16NumOfLines++;
        u8 Local_au8PosResponse[2] = {POS_RESPONSE_SID, ReceivedMessage->MessageData[1]};
        UDSHandler_voidSendPosResponse(Local_au8PosResponse, 2);
    }

    else if(ReceivedMessage->MessageData[1] == (TransferData_u8ExpectedBSC-1))
    {
        u8 Local_au8PosResponse[2] = {POS_RESPONSE_SID, ReceivedMessage->MessageData[1]};
        UDSHandler_voidSendPosResponse(Local_au8PosResponse, 2);
    }

    else
    {
        UDSHandler_voidSendNegResponse(TransferData, wrongBlockSequenceCounter);
        return;
    }
}