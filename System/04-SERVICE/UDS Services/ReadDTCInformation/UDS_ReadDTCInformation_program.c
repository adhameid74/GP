/**
 * @file UDS_ReadDTCInformation_program.c
 * @author Ahmed M.Abdelfattah (ahmedm7md24@gmail.com)
 * @brief  
 * @version 1
 * @date 2020-4-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <string.h>

#include "DoCAN_interface.h"
#include "UDSHandler_interface.h"
#include "DTC_interface.h"

#include "UDS_ReadDTCInformation_interface.h"
#include "UDS_ReadDTCInformation_private.h"
#include "UDS_ReadDTCInformation_config.h"


u8 UDS_u8ReadDTCInformation( INDICATION_SDU message)
{
    if (message.Length.u12 != 3)
	{
		UDSHandler_voidSendNegResponse(ReadDTCInformation,incorrectMessageLengthOrInvalidFormat);
		return 0;
	}
    u8 Local_Au8dtc[DTC_NUMBER];
	u8 Local_u8temp,Local_u8counter=0;

    if(message.MessageData[1] == reportMirrorMemoryDTCByStatusMask) //reportMirrorMemoryDTCByStatusMask
    {
	//Function of EEPROM (Local_Au8dtc,offset,DTC_NUMBER);
		for(u8 i = 0; i < DTC_NUMBER; i++)
		{
			if(Local_Au8dtc[i] == 0xFF){
				Local_Au8dtc[i] = 0;
				continue;
			}
				
			Local_u8temp=message.MessageData[2]&Local_Au8dtc[i];
			if (Local_u8temp!=0)
			{
				Local_u8counter++;
			}
			else{
				Local_Au8dtc[i]=0;
			}
		}

		u8 Local_Au8PositiveResponce[(2*Local_u8counter)+3];
		memset(Local_Au8PositiveResponce,POS_RESPONSE_SID,((2*Local_u8counter)+3)*sizeof(u8));
		Local_Au8PositiveResponce[1] = reportMirrorMemoryDTCByStatusMask;
		Local_Au8PositiveResponce[2] = DTCStatusAvailabilityMask;
		Local_u8temp=3;
		for (u8 i = 0; i < DTC_NUMBER; i++)
		{
			if (Local_Au8dtc[i]==0)
			{
				continue;
			}
			Local_Au8PositiveResponce[Local_u8temp]=i;
			Local_Au8PositiveResponce[Local_u8temp+1]=Local_Au8dtc[i];
			Local_u8temp+=2;
		}
		UDSHandler_voidSendPosResponse(Local_Au8PositiveResponce,(2*Local_u8counter)+3);
		return 1;
    }
    else if(message.MessageData[1] == reportNumberOfMirrorMemoryDTCByStatusMask) //reportNumberOfMirrorMemoryDTCByStatusMask
    {
        //Function of EEPROM (Local_Au8dtc,offset,DTC_NUMBER);
		for(u8 i = 0; i < DTC_NUMBER; i++)
		{
			if(Local_Au8dtc[i] == 0xFF){
				Local_Au8dtc[i] = 0;
				continue;
			}
			Local_u8temp=message.MessageData[2]&Local_Au8dtc[i];
			if (Local_u8temp!=0)
			{
				Local_u8counter++;
			}
			else{
				Local_Au8dtc[i]=0;
			}
		}
		u8 Local_Au8PositiveResponce2[4]={POS_RESPONSE_SID,reportNumberOfMirrorMemoryDTCByStatusMask,DTCStatusAvailabilityMask,Local_u8counter};
		UDSHandler_voidSendPosResponse(Local_Au8PositiveResponce2,4);
		return 1;
    }
    
    else
    {
		UDSHandler_voidSendNegResponse(ReadDTCInformation,subFunctionNotSupported);
		return 0;
    }
}
