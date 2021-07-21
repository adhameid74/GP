/*
 * my_tasks.c
 *
 *  Created on: Jul 7, 2021
 *      Author: Abdallah
 */
#include "my_tasks.h"
u32 Zone_1=100 ;
u32 Zone_2=30 ;
u8 i=0;
void vUSOINIC_TASK(void *pv){


	while(1){
		u8 Local_u8DTC_F = 0;
		u8 Local_u8DTC_R = 0;
		Front_Distance = USONIC_f32GetDistance(USONIC1,&Local_u8DTC_F);
		Rear_Distance = USONIC_f32GetDistance(USONIC2,&Local_u8DTC_R);

 		if(Front_Distance > Zone_1){
 			Dio_WriteChannel(PB5,1);
			Dio_WriteChannel(3,0);
			Dio_WriteChannel(2,0);
		}
		else if(Front_Distance >Zone_2){
			Dio_WriteChannel(2,1);
			Dio_WriteChannel(3,0);
			Dio_WriteChannel(PB5,0);
		}
		else {
			Dio_WriteChannel(3,1);
			Dio_WriteChannel(PB5,0);
			Dio_WriteChannel(2,0);
		}

		if(Rear_Distance > Zone_1){
 			Dio_WriteChannel(PA4,1);
			Dio_WriteChannel(PA5,0);
			Dio_WriteChannel(PA6,0);
		}
		else if(Rear_Distance >Zone_2){
 			Dio_WriteChannel(PA5,1);
			Dio_WriteChannel(PA4,0);
			Dio_WriteChannel(PA6,0);
		}
		else {
 			Dio_WriteChannel(PA6,1);
			Dio_WriteChannel(PA4,0);
			Dio_WriteChannel(PA5,0);

		}

	}
}
void vBUTTON_Task(void*pv){


	while(1){
		if(xSemaphoreTake(xSema,portMAX_DELAY)==pdPASS){
			i++;
			if(i == 1){
				xTaskCreate(vUSOINIC_TASK,"USOINIC_TASK",250,NULL,4,&USONIC_Handle);
			}
			else if(i >= 2){
				vTaskDelete(USONIC_Handle);
	 			Dio_WriteChannel(PA6,0);
				Dio_WriteChannel(PA4,0);
				Dio_WriteChannel(PA5,0);
	 			Dio_WriteChannel(PB5,0);
				Dio_WriteChannel(PA2,0);
				Dio_WriteChannel(PA3,0);
				i=0;
			}



		}


	}

}


void vSwitchPressed(void *pv){
	TickType_t xLastWakeTime;
	xLastWakeTime =xTaskGetTickCount();
	TickType_t xPeriod =pdMS_TO_TICKS(150);
	while(1){
		Direction = MUART_u8ReceiveTimeOut(1);
		if(Direction == 'W'|Direction =='w')
			xSemaphoreGive(xSema);
		if(Direction=='R' | Direction=='F' |Direction=='B' |Direction=='L' |Direction == 'S' )
			xSemaphoreGive(xSemaDirection);
		vTaskDelayUntil(&xLastWakeTime ,xPeriod);



	}
}

void vSetDirection(void* pv){
	while(1){
		if(xSemaphoreTake(xSemaDirection ,portMAX_DELAY) ==pdPASS){
			CAR_voidSetCarSpeed(100);
			switch (Direction) {
				case 'F':
					//Dio_WriteChannel(0,1);
					CAR_voidSetCarDirection(CAR_FORWARD);
					break;
				case 'B':
					//Dio_WriteChannel(0,0);
					CAR_voidSetCarDirection(CAR_BACKWARD);
					break;
				case 'R':
					//Dio_WriteChannel(1,1);
					CAR_voidSetCarDirection(CAR_RIGHT);
					break;
				case 'L':
					//Dio_WriteChannel(1,0);
					CAR_voidSetCarDirection(CAR_LEFT);
					break;

				case 'S':
					//Dio_FlipChannel(2);
					CAR_voidSetCarDirection(CAR_STOP);
					break;
				default :
					break;
			}
		}
	}

}

void vVoltageSensor(void *pv){

	TickType_t xLastWakeTime;
	xLastWakeTime =xTaskGetTickCount();
	TickType_t xPeriod =pdMS_TO_TICKS(300);
	u16 Local_u16Value = 0;
	while(1){
		Local_u16Value = VSEN_u8ReadVoltage();
		if(Local_u16Value > 0){
			xSemaphoreGive( xSemaVoltage);
		}
		vTaskDelayUntil(&xLastWakeTime ,xPeriod);
		}


}

void vTaskVoltage(void *pv){
	while(1){
		if(xSemaphoreTake(xSemaVoltage ,portMAX_DELAY) ==pdPASS){
			//Dio_FlipChannel(PB12);
		}
	}
}

void vSpeedSensor(void *pv)
{

	TickType_t xLastWakeTime;
	xLastWakeTime =xTaskGetTickCount();
	TickType_t xPeriod =pdMS_TO_TICKS(300);
	while(1){
		SPEED_voidGetReadingAsynch();
		if(SPEED_u16Reading > 0 ){
			xSemaphoreGive(xSemaSpeed);

		}
		vTaskDelayUntil(&xLastWakeTime ,xPeriod);

		}

}

void vTaskSpeed(void *pv)
{

	while(1){
		if(xSemaphoreTake(xSemaSpeed ,portMAX_DELAY) ==pdPASS){
			Dio_FlipChannel(PA11);
		}
	}
}




