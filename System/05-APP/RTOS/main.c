#include "BIT_MATH.h"
#include "STD_TYPES.h"


#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "portmacro.h"
#include "task.h"
#include "queue.h"
#include "list.h"
//#include "projdefs.h"
#include "semphr.h"

/******************************/

/******************************/
#include "RCC_interface.h"
#include "DIO_interface.h"
#include "EXTI_interface.h"
#include "ADC_interface.h"
#include "NVIC_interface.h"
#include "TIMER_interface.h"
#include "UART_interface.h"
#include "SPEED_interface.h"
#include "MOTOR_interface.h"
#include "VSEN_interface.h"

#include "CAR_interface.h"
#include "my_tasks.h"

#include "DoCAN_interface.h"
#include "UDSHandler_interface.h"

void main(void){
	RCC_voidInitSystemClock();
	RCC_voidEnableClock(RCC_APB2, RCC_APB2_GPIOA);
	RCC_voidEnableClock(RCC_APB2, RCC_APB2_GPIOB);
	RCC_voidEnableClock(RCC_APB2, RCC_APB2_GPIOC);
	RCC_voidEnableClock(RCC_APB2, RCC_APB2_ADC1);
	RCC_voidEnableClock(RCC_APB1, RCC_APB1_TIMER2);
	RCC_voidEnableClock(RCC_APB1, RCC_APB1_TIMER3);
	RCC_voidEnableClock(RCC_APB1, RCC_APB1_TIMER4);
	RCC_voidEnableClock(RCC_APB2, RCC_APB2_USART1);
	RCC_voidEnableClock(RCC_APB1, RCC_APB1_USART2);

	MUART_voidInit(1);
	USONIC_voidInit();
	CAR_voidInit();
	/*********************************************/
	TIMER_voidSetPrescaler(TIMER_TIMER2, 8000);

	Port_SetPinDirection(PB5, INPUT);
	Port_SetPinMode(PB5, INPUT_PULL_DOWN);

	/***************************************/
	/***************************************/
	ADC_voidInit();
	u8 Local_u8Channel[1] = {0};
	ADC_voidAssignRegularSequence(1,Local_u8Channel);
	Port_SetPinDirection(PA0, INPUT);
	Port_SetPinMode(PA0, INPUT_ANALOG);
	/***************************************/




	Port_SetPinDirection(PA10, INPUT);
	Port_SetPinMode(PA10, INPUT_FLOATING);
	/****************************************/
	Port_SetPinDirection(PB5,OUTPUT_S10MHZ);
	Port_SetPinMode(PB5,GP_OUTPUT_PUSH_PULL);
	Port_SetPinDirection(2,OUTPUT_S10MHZ);
	Port_SetPinMode(2,GP_OUTPUT_PUSH_PULL);
	Port_SetPinDirection(3,OUTPUT_S10MHZ);
	Port_SetPinMode(3,GP_OUTPUT_PUSH_PULL);
	/******************************************/
	/****************************************/
	Port_SetPinDirection(PA4,OUTPUT_S10MHZ);
	Port_SetPinMode(PA4,GP_OUTPUT_PUSH_PULL);
	Port_SetPinDirection(PA5,OUTPUT_S10MHZ);
	Port_SetPinMode(PA5,GP_OUTPUT_PUSH_PULL);
	Port_SetPinDirection(PA6,OUTPUT_S10MHZ);
	Port_SetPinMode(PA6,GP_OUTPUT_PUSH_PULL);
	/******************************************/

	Port_SetPinDirection(PA11,OUTPUT_S10MHZ);
	Port_SetPinMode(PA11,GP_OUTPUT_PUSH_PULL);

	xSema = xSemaphoreCreateBinary();
	xSemaDirection =xSemaphoreCreateBinary();
	xSemaVoltage =xSemaphoreCreateBinary();
	xSemaSpeed = xSemaphoreCreateBinary();
	xSemaService = xSemaphoreCreateBinary();


    xTaskCreate(vBUTTON_Task,"BUTTON_Task",250,NULL,5,&BTask);
    xTaskCreate(vSwitchPressed,"Blue",250,NULL,4,NULL);
    xTaskCreate(vSetDirection,"Direction",250,NULL,4,NULL);
    /********************************************************/
    xTaskCreate(vVoltageSensor,"V",250,NULL,4,NULL);
    xTaskCreate(vTaskVoltage,"XX",250,NULL,4,NULL);
    xTaskCreate(vSpeedSensor,"SS",250,NULL,4,NULL);
    xTaskCreate(vTaskSpeed,"XXX",250,NULL,4,NULL);
    /*******************************************************/
    xTaskCreate(vServices,"VSS",250,NULL,4,NULL);


    vTaskStartScheduler();
}
