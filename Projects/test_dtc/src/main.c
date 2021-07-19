/*
/**
 * @file DoCAN_program.c
 * @author Ahmed Hendawy
 * @brief
 * @version 0.0
 * @date 22-03-2021
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "CAN_interface.h"
#include "DoCAN_interface.h"
#include "RCC_interface.h"
#include "I2C_interface.h"
#include "DIO_interface.h"
#include "EEPROM_interface.h"
#include "DTC_interface.h"
#include "NVIC_interface.h"
#include "UDSHandler_interface.h"

//REQUEST_SDU Message;
//void indication_message(INDICATION_SDU ReceivedMessage);
void main (void) {
	volatile u8 aghjj=0;
	RCC_voidInitSystemClock();
	RCC_voidEnableClock(RCC_APB2,RCC_APB2_GPIOB);
	RCC_voidEnableClock(RCC_APB1,RCC_APB1_I2C1);
	RCC_voidEnableClock(RCC_APB1, RCC_APB1_CAN);
	RCC_voidEnableClock(RCC_APB2, RCC_APB2_GPIOA);
	dtcItem_t jh;
	dtcProperty_t property1;
	jh.Property = &property1;
	jh.Property->Code = DTC_TestFailure;
	jh.Property->TestPassedThreshold = -1;
	jh.Property->TestFailedThreshold = 0;
	jh.Property->AgingThreshold = 1;
	jh.Status.ConfirmedDTC=0;
	jh.Status.TestFailed=0;
	jh.Status.TestFailedThisOperationCycle=0;
	jh.Status.WarningIndicatorRequested=0;
	jh.Status.TestNotCompletedThisOperationCycle=1;

/*	Message.SA = 0x55;
	Message.TA = 0x56;
	Message.MessageData[0] = ReadDTCInformation;
	Message.MessageData[1] = 0x11;
	Message.MessageData[2] = 0x02;
	Message.Length.u12 = 3;*/

	CAN_voidInit();
	CAN_voidStart();
//	DoCAN_voidRequestUsData(Message);


	Port_SetPinDirection(PB6, OUTPUT_S10MHZ);
	Port_SetPinMode(PB6,AF_OUTPUT_OPEN_DRAIN);
	Port_SetPinDirection(PB7, OUTPUT_S10MHZ);
	Port_SetPinMode(PB7,AF_OUTPUT_OPEN_DRAIN);
	MI2C_voidInti();
	Port_SetPinDirection(PA0, OUTPUT_S10MHZ);
	Port_SetPinMode(PA0,GP_OUTPUT_PUSH_PULL);
	Dio_WriteChannel(PA0,1);
	HEEPROM_voidDeletePages(EEPROM_ADDRESS,0x0000,1);
	//CAN_filter_t FILTER1 = {0x55, CAN_DATA_FRAME, CAN_FIFO0};
	CAN_filter_t FILTER2 = {0x55, CAN_DATA_FRAME, CAN_FIFO0};
	//CAN_voidWriteFilter(&FILTER1);
	CAN_voidWriteFilter(&FILTER2);
	CAN_voidSetCallBack(DoCAN_voidIndicateUsData);
	DTC_u8DetectFault(&jh,1);
	aghjj=HEEPROM_u8ReadByte(EEPROM_ADDRESS,23);

	aghjj=HEEPROM_u8ReadByte(EEPROM_ADDRESS,24);

//	HEEPROM_voidWriteByte(EEPROM_ADDRESS,24, 10);
//	HEEPROM_voidDeletePages(EEPROM_ADDRESS,0x0000,1);
	DoCAN_voidSetCallBackForMassage(UDSHandler_voidCallService);


	while(1){

	}


}
/*void indication_message(INDICATION_SDU ReceivedMessage)
{
	static u8 i = 0;
	if(ReceivedMessage.MessageData[0] == 0x59)
	{
		Message.MessageData[0] = ReadDTCInformation;
		Message.MessageData[1] = 0x0F;
		Message.MessageData[2] = 0x02;
		Message.Length.u12 = 3;
		DoCAN_voidRequestUsData(Message);
		if(ReceivedMessage.MessageData[1] == 0x0F)
		{
			if(i == 0)
			{
				Message.MessageData[0] = ClearDiagnosticInformation;
				Message.Length.u12 = 1;
				DoCAN_voidRequestUsData(Message);
				i++;
			}
			else
			{
				Dio_WriteChannel(PA0,1);
			}

		}
		if(ReceivedMessage.MessageData[1] == 0x11)
		{
			Message.MessageData[0] = ReadDTCInformation;
			Message.MessageData[1] = 0x0F;
			Message.MessageData[2] = 0x02;
			Message.Length.u12 = 3;
			DoCAN_voidRequestUsData(Message);
		}
	}
	else if(ReceivedMessage.MessageData[0] == 0x54)
	{
		Message.MessageData[0] = ReadDTCInformation;
		Message.MessageData[1] = 0x11;
		Message.MessageData[2] = 0x02;
		Message.Length.u12 = 3;
		DoCAN_voidRequestUsData(Message);
	}
}*/

