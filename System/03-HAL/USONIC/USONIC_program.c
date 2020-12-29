/**
 * @file USONIC_program.c
 * @author Ahmed M.Abdelfattah (ahmedm7md24@gmail.com)
 * @brief 
 * @version 1
 * @date 2020-12-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "USONIC_interface.h"
#include "USONIC_private.h"
#include "USONIC_config.h"
#include "DIO_interface.h"
#include "TIMER_interface.h"

u8 Local_u8Flag=0;


void USONIC_voidInit(){
    //Set ECHO pin as 2MHZ output pin and initialy Low
	DIO_voidSetPinDirection (USONIC_TRIGGER, OUTPUT_GP_2MHZ_PP);
	DIO_voidSetPinValue     (USONIC_TRIGGER, LOW);
    //Port_SetPinDirection(USONIC_TRIGGER,OUTPUT_S2MHZ);
    //Port_SetPinMode(USONIC_TRIGGER,GP_OUTPUT_PUSH_PULL);
    //Dio_WriteChannel(USONIC_TRIGGER,0);
    //Set the Trigger pin as floating input
	DIO_voidSetPinDirection (USONIC_ECHO, INPUT_FLOATING);
    //Port_SetPinDirection(USONIC_ECHO,INPUT);
    //Port_SetPinMode(USONIC_ECHO,INPUT_FLOATING);
    //Set the prescaler of the timer so that the CLK is 1MHZ
    TIMER_voidSetPrescaler(USONIC_TIMER,8);
}



f32 USONIC_f32GetDistance(){
    Local_u8Flag=0;
    f32 Local_f32Distance=0;
    DIO_voidSetPinValue(USONIC_TRIGGER,1);
    TIMER_voidSetBusyWait(USONIC_TIMER,10);
    DIO_voidSetPinValue(USONIC_TRIGGER,0);
    TIMER_voidSetResetTimer(USONIC_TIMER,TIMER_SET,0xFFFF);
    while (DIO_u8GetPinValue(USONIC_ECHO)==0);
    TIMER_voidStartStopCount(USONIC_TIMER ,TIMER_START);
    while (DIO_u8GetPinValue(USONIC_ECHO)==1);
    TIMER_voidStartStopCount(USONIC_TIMER ,TIMER_STOP);
    Local_f32Distance=(f32)TIMER_u16GetElapsedTime(USONIC_TIMER)/58.82;
    TIMER_voidSetResetTimer(USONIC_TIMER,TIMER_RESET,0);
    return Local_f32Distance;
}
