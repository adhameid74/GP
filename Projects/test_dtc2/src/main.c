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
	jh.FaultDetectionCounter = 0;
	jh.Status=0x10;
	jh.Property->Bits=0;


	CAN_voidInit();
	CAN_voidStart();


	Port_SetPinDirection(PB6, OUTPUT_S10MHZ);
	Port_SetPinMode(PB6,AF_OUTPUT_OPEN_DRAIN);
	Port_SetPinDirection(PB7, OUTPUT_S10MHZ);
	Port_SetPinMode(PB7,AF_OUTPUT_OPEN_DRAIN);
	MI2C_voidInti();
	Port_SetPinDirection(PA0, OUTPUT_S10MHZ);
	Port_SetPinMode(PA0,GP_OUTPUT_PUSH_PULL);
	Dio_WriteChannel(PA0,0);
	HEEPROM_voidDeletePages(0xa0,0x0000,1);
	Dio_WriteChannel(PA0,1);

	CAN_filter_t FILTER2 = {0x55, CAN_DATA_FRAME, CAN_FIFO0};
	CAN_u8WriteFilter(&FILTER2);
	CAN_u8SetCallBack(DoCAN_voidIndicateUsData);
	DTC_u8DetectFault(&jh,1);
	aghjj=HEEPROM_u8ReadByte(0xa0,23);
	aghjj=HEEPROM_u8ReadByte(0xa0,24);
	DoCAN_voidSetCallBackForMassage(UDSHandler_voidCallService);


	while(1){

	}


}
