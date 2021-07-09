/**
 * @file UDS_InputOutputControlByIdentifier_program.c
 * @author Eslam Khaled (eslam.kh.kamal@gmail.com)
 * @brief UDS_InputOutputControlByIdentifier service implementation
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

#include "USONIC_interface.h"
#include "CAR_interface.h"
#include "VSEN_interface.h"

#include "UDS_InputOutputControlByIdentifier_interface.h"
#include "UDS_InputOutputControlByIdentifier_private.h"
#include "UDS_InputOutputControlByIdentifier_config.h"

u16 USONIC1_valueToUse;
u16 USONIC2_valueToUse;
u8  USONIC1_whatShouldIdo = returnControlToECU;
u8  USONIC2_whatShouldIdo = returnControlToECU;

u16 VOLT_valueToUse;
u8  VOLT_whatShouldIdo = returnControlToECU;

u16 CAR_SPEED_valueToUse;
u16 CAR_DIRECTION_valueToUse;
u8  CAR_SPEED_whatShouldIdo = returnControlToECU;
u8  CAR_DIRECTION_whatShouldIdo = returnControlToECU;

void UDS_voidInputOutputControlByID(INDICATION_SDU* ReceivedMessage)
{
	// check for errors and send negative response
	if (ReceivedMessage->Length.u12 > 4 || ReceivedMessage->Length.u12 < 3)
	{
		UDSHandler_voidSendNegResponse(InputOutputControlByIdentifier, incorrectMessageLengthOrInvalidFormat);
		return;
	}
	if(IsNotID(ReceivedMessage->MessageData[1]))
	{
		UDSHandler_voidSendNegResponse(InputOutputControlByIdentifier, requestOutOfRange);
		return;
	}
	if(IsNotSubFunction(ReceivedMessage->MessageData[2]))
	{
		UDSHandler_voidSendNegResponse(InputOutputControlByIdentifier, subFunctionNotSupported);
		return;
	}

	ControlOptionRecord ControlRecord;	
	ControlRecord.DID = ReceivedMessage->MessageData[1];
	ControlRecord.subFunction = ReceivedMessage->MessageData[2];
	if(ReceivedMessage->Length.u12 == 4)
	{
		ControlRecord.ValueToUse = ReceivedMessage->MessageData[3];
	}
	u16 ControlStatusRecord = ExecutecontrolOptionRecord(ControlRecord);   // the size to be confirmed
	
	u8 Local_u8PosResponse[5] = {POS_RESPONSE_SID, ControlRecord.DID , ControlRecord.subFunction , ControlStatusRecord>>8 , ControlStatusRecord};    // the size to be confirmed
	UDSHandler_voidSendPosResponse(Local_u8PosResponse, 5);
}

u16 ExecutecontrolOptionRecord(ControlOptionRecord ControlRecord)   // the return size to be confirmed
{
	u8 dumb;
	u16 Local_u16ControlStatusRecord;
	switch (ControlRecord.DID)
	{
	case DID_SPEED:
		/* code */
		break;
		
	case DID_FRONTDISTANCE:
		if (ControlRecord.subFunction == shortTermAdjustment)
		{
			USONIC1_valueToUse =  ControlRecord.ValueToUse;
		}
		USONIC1_whatShouldIdo = ControlRecord.subFunction;
		Local_u16ControlStatusRecord = USONIC_f32GetDistance(USONIC1,dumb);
		break;

	case DID_BACKDISTANCE:
		if (ControlRecord.subFunction == shortTermAdjustment)
		{
			USONIC2_valueToUse =  ControlRecord.ValueToUse;
		}
		USONIC2_whatShouldIdo = ControlRecord.subFunction;
		Local_u16ControlStatusRecord = USONIC_f32GetDistance(USONIC2,dumb);
		break;

	case DID_VOLT:
		if (ControlRecord.subFunction == shortTermAdjustment)
		{
			VOLT_valueToUse =  ControlRecord.ValueToUse;
		}
		VOLT_whatShouldIdo = ControlRecord.subFunction;
		Local_u16ControlStatusRecord = VSEN_u8ReadVoltage();
		break;

	case DID_CAR_DIRECTION:
		CAR_DIRECTION_whatShouldIdo = ControlRecord.subFunction;
		if (ControlRecord.subFunction == shortTermAdjustment)
		{
			CAR_voidSetCarDirection(ControlRecord.ValueToUse);
			Local_u16ControlStatusRecord = ControlRecord.ValueToUse;
		}
		else if (ControlRecord.subFunction == resetToDefault)
		{
			CAR_voidSetCarDirection(CAR_DIRECTION_DefaultValue);
			Local_u16ControlStatusRecord = CAR_DIRECTION_DefaultValue;
		}
		else if (ControlRecord.subFunction == freezeCurrentState)
		{
			CAR_voidSetCarDirection(CAR_DIRECTION_CurrentValue);
			Local_u16ControlStatusRecord = CAR_DIRECTION_CurrentValue;
		}
		else if (ControlRecord.subFunction == returnControlToECU)
		{
			CAR_voidSetCarDirection(CAR_DIRECTION_DefaultValue);
			Local_u16ControlStatusRecord = CAR_DIRECTION_DefaultValue;
		}
		
		break;

	case DID_CAR_SPEED:
		CAR_DIRECTION_whatShouldIdo = ControlRecord.subFunction;
		if (ControlRecord.subFunction == shortTermAdjustment)
		{
			CAR_SPEED_valueToUse = ControlRecord.ValueToUse;
			CAR_voidSetCarSpeed(CAR_SPEED_valueToUse);
			Local_u16ControlStatusRecord = ControlRecord.ValueToUse;
		}
		else if (ControlRecord.subFunction == resetToDefault)
		{
			CAR_voidSetCarSpeed(CAR_SPEED_DefaultValue);
			Local_u16ControlStatusRecord = CAR_SPEED_DefaultValue;
		}
		else if (ControlRecord.subFunction == freezeCurrentState)
		{
			CAR_voidSetCarSpeed(CAR_SPEED_CurrentValue);
			Local_u16ControlStatusRecord = CAR_SPEED_CurrentValue;
		}
		else if (ControlRecord.subFunction == returnControlToECU)
		{
			CAR_voidSetCarSpeed(CAR_SPEED_DefaultValue);
			Local_u16ControlStatusRecord = CAR_SPEED_DefaultValue;
		}
		
		break;
	
	default:
		break;
	}
	return Local_u16ControlStatusRecord;
}

u8 IsNotID( u8 Copy_u8DataId )
{
    switch (Copy_u8DataId)
	{
	case DID_SPEED:
		break;
	case DID_FRONTDISTANCE:
		break;
	case DID_BACKDISTANCE:
		break;
	case DID_VOLT:
		break;
	case DID_UART1:
		break;
	case DID_UART2:
		break;
	case DID_TIMER2:
		break;
	case DID_TIMER3:
		break;
	case DID_TIMER4:
		break;
	case DID_ADC:
		break;
	
	default:
		return 1;
	}
	return 0;
}

u8 IsNotSubFunction (u8 Copy_u8SubFunction)
{
    if(Copy_u8SubFunction == returnControlToECU || Copy_u8SubFunction == resetToDefault || Copy_u8SubFunction == freezeCurrentState || Copy_u8SubFunction == shortTermAdjustment )
    {
        return 0;
    }
    return 1;
}
