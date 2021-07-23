/*
 * my_tasks.h
 *
 *  Created on: Jul 7, 2021
 *      Author: Abdallah
 */

#ifndef MY_TASKS_H_
#define MY_TASKS_H_

#include "STD_TYPES.h"

#include "USONIC_interface.h"
#include "DIO_interface.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "portmacro.h"
#include "task.h"
#include "queue.h"
#include "list.h"
//#include "projdefs.h"
#include "semphr.h"

//#include "EXTI_interface.h"
#include "ADC_interface.h"
#include "NVIC_interface.h"
#include "SPEED_interface.h"
#include "TIMER_interface.h"
#include "UART_interface.h"
#include "MOTOR_interface.h"
#include "VSEN_interface.h"
#include "DoCAN_interface.h"
#include "UDSHandler_interface.h"
#include "CAR_interface.h"

volatile u8 Direction ;
TaskHandle_t USONIC_Handle;
TaskHandle_t BTask;
f32 volatile Front_Distance ;
f32 volatile Rear_Distance;

/*****************************/
/*******************************/
SemaphoreHandle_t xSemaSpeed ;

/*******************************/
SemaphoreHandle_t xSema ;
SemaphoreHandle_t xSemaDirection ;
SemaphoreHandle_t xSemaVoltage ;
SemaphoreHandle_t xSemaService ;

void vUSOINIC_TASK(void *pv);
void vSwitchPressed(void *pv);
void vBUTTON_Task(void*pv);
void vSetDirection(void* pv);
/******************************/
void vVoltageSensor(void *pv);
void vTaskVoltage(void *pv);
void vSpeedSensor(void *pv);
void vTaskSpeed(void *pv);
void vTaskSemaphoreService(INDICATION_SDU message);
void vTaskService(void *pv);




#endif /* MY_TASKS_H_ */
