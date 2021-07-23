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

#include"FreeRTOSConfig.h"
#include"FreeRTOS.h"
#include"portmacro.h"
#include"task.h"
#include"queue.h"
#include"list.h"
#include"semphr.h"

#include "ADC_interface.h"
#include "CAN_interface.h"
#include "DoCAN_interface.h"
#include "TIMER_interface.h"
#include "RCC_interface.h"
#include "I2C_interface.h"
#include "DIO_interface.h"
#include "EEPROM_interface.h"
#include "DTC_interface.h"
#include "NVIC_interface.h"
#include "UDSHandler_interface.h"
#include "UART_interface.h"
#include "USONIC_interface.h"
#include "VSEN_interface.h"
#include "MOTOR_interface.h"
#include "SPEED_interface.h"
#include "CAR_interface.h"
#include "my_tasks.h"

void main (void) {
	volatile u16 aghjj=0;
	/**************************************************/
	RCC_voidInitSystemClock();
	RCC_voidEnableClock(RCC_APB2, RCC_APB2_GPIOA);
	RCC_voidEnableClock(RCC_APB2,RCC_APB2_GPIOB);

	RCC_voidEnableClock(RCC_APB2,RCC_APB2_ADC1);

	RCC_voidEnableClock(RCC_APB1,RCC_APB1_TIMER2);
	RCC_voidEnableClock(RCC_APB1,RCC_APB1_TIMER3);
	RCC_voidEnableClock(RCC_APB1,RCC_APB1_TIMER4);

	RCC_voidEnableClock(RCC_APB2,RCC_APB2_USART1);

	RCC_voidEnableClock(RCC_APB1,RCC_APB1_I2C1);
	RCC_voidEnableClock(RCC_APB1, RCC_APB1_CAN);




	/************************************************************/

	MUART_voidInit(MUART1);
	USONIC_voidInit();

	CAN_voidInit();
	CAR_voidInit();
	CAN_voidStart();



	ADC_voidInit();
	DoCAN_voidSetCallBackForMassage(vTaskSemaphoreService);

	/***********************************************************/
	TIMER_voidSetPrescaler(TIMER_TIMER2,8000);
	/***********************************************************/

	Port_SetPinDirection(PA1, INPUT);
	Port_SetPinMode(PA1,INPUT_PULL_DOWN);
	Port_SetPinDirection(PB6, OUTPUT_S10MHZ);
	Port_SetPinMode(PB6,AF_OUTPUT_OPEN_DRAIN);
	Port_SetPinDirection(PB7, OUTPUT_S10MHZ);
	Port_SetPinMode(PB7,AF_OUTPUT_OPEN_DRAIN);
	MI2C_voidInti();
	Port_SetPinDirection(PA0, INPUT);
	Port_SetPinMode(PA0,INPUT_ANALOG);

	Port_SetPinDirection(PB5, OUTPUT_S10MHZ);
	Port_SetPinMode(PB5,GP_OUTPUT_PUSH_PULL);
	Port_SetPinDirection(PA2, OUTPUT_S10MHZ);
	Port_SetPinMode(PA2,GP_OUTPUT_PUSH_PULL);
	Port_SetPinDirection(PA3, OUTPUT_S10MHZ);
	Port_SetPinMode(PA3,GP_OUTPUT_PUSH_PULL);
	Port_SetPinDirection(PA4, OUTPUT_S10MHZ);
	Port_SetPinMode(PA4,GP_OUTPUT_PUSH_PULL);
	Port_SetPinDirection(PA5, OUTPUT_S10MHZ);
	Port_SetPinMode(PA5,GP_OUTPUT_PUSH_PULL);
	Port_SetPinDirection(PA6, OUTPUT_S10MHZ);
	Port_SetPinMode(PA6,GP_OUTPUT_PUSH_PULL);
	/*********************************************************/


	HEEPROM_voidDeletePages(0xa0,0x0000,1);
	CAN_filter_t FILTER2 = {0x55, CAN_DATA_FRAME, CAN_FIFO0};
	CAN_u8WriteFilter(&FILTER2);
	CAN_u8SetCallBack(DoCAN_voidIndicateUsData);


	u8 laofjn[1]={0};
	ADC_voidAssignRegularSequence(1,laofjn);
	/****************************************************/
	xSema = xSemaphoreCreateBinary();
	xSemaDirection =xSemaphoreCreateBinary();
	xSemaVoltage =xSemaphoreCreateBinary();
	xSemaSpeed = xSemaphoreCreateBinary();
	xSemaService =xSemaphoreCreateBinary();


    xTaskCreate(vBUTTON_Task,"BUTTON_Task",250,NULL,5,&BTask);
    xTaskCreate(vSwitchPressed,"Blue",250,NULL,4,NULL);
    xTaskCreate(vSetDirection,"Direction",250,NULL,4,NULL);
    xTaskCreate(vSetDirection,"Direction",250,NULL,4,NULL);
    /********************************************************/
    xTaskCreate(vVoltageSensor,"V",250,NULL,4,NULL);
    xTaskCreate(vTaskVoltage,"XX",250,NULL,4,NULL);
    xTaskCreate(vSpeedSensor,"SS",250,NULL,4,NULL);
    xTaskCreate(vTaskSpeed,"XXX",250,NULL,4,NULL);
    xTaskCreate(vTaskService,"YYYY",250,NULL,5,NULL);
    /*******************************************************/

    vTaskStartScheduler();
    /*******************************************************/

}
