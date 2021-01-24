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
	Port_SetPinDirection( USONIC_TRIGGER, OUTPUT_S2MHZ);
	Port_SetPinMode( USONIC_TRIGGER, GP_OUTPUT_PUSH_PULL );
	Dio_WriteChannel( USONIC_TRIGGER, 0);
    //Set the Trigger pin as floating input
	Port_SetPinDirection( USONIC_ECHO, INPUT);
	Port_SetPinMode( USONIC_ECHO, INPUT_PULL_DOWN );
    //Set the prescaler of the timer so that the CLK is 1MHZ
    TIMER_voidSetPrescaler(USONIC_TIMER,8);
}



f32 USONIC_f32GetDistance(u8 *DTC_CODE){
    Local_u8Flag=0;
    u8 Local_u8Counter=0;
    f32 Local_f32Distance=0;
    u16 Local_u16TimerCount=0;
    Dio_WriteChannel( USONIC_TRIGGER, 1);
    TIMER_voidSetBusyWait(USONIC_TIMER,10);
    Dio_WriteChannel( USONIC_TRIGGER, 0);
    TIMER_voidSetResetTimer(USONIC_TIMER,TIMER_SET,0xFFFF);
    while (Dio_ReadChannel(USONIC_ECHO)==0&&Local_u8Counter<0xFF)
    {
        Local_u8Counter++;
    }
    if (Local_u8Counter!=0xFF)
    {
        TIMER_voidStartStopCount(USONIC_TIMER ,TIMER_START);
        while (Dio_ReadChannel(USONIC_ECHO)==1);
        TIMER_voidStartStopCount(USONIC_TIMER ,TIMER_STOP);
        Local_u16TimerCount=TIMER_u16GetElapsedTime(USONIC_TIMER);
        Local_f32Distance=(f32)Local_u16TimerCount/58.82;
        TIMER_voidSetResetTimer(USONIC_TIMER,TIMER_RESET,0);
    }
    
    
    if (Local_u8Counter==0xFF)
    {
        *DTC_CODE=5;     //ECHO PIN DISCONNECTED
    }
    else if (Local_u16TimerCount<1766)    //less than 30 cm   
    {
        *DTC_CODE=1;     //RED LED
    }
    else if (Local_u16TimerCount<5900)    //less than 100 cm
    {
        *DTC_CODE=2;     //ORANGE LED
    }
    else if (Local_u16TimerCount<14750)   //less than 250 cm
    {
        *DTC_CODE=3;     //GREEN LED
    }
    else {
        *DTC_CODE=4;     //UNCONFIRMED CASE
    }
    
    
    return Local_f32Distance;
}


/*
void USONIC_f32GetDistanceAsynch(void (*CallBackFunc) (f32)){
    Local_CallBackFunc=CallBackFunc;
    EXTI_voidSetSignalLatch(EXTI_LINE11,EXTI_FALLING);
    EXTI_voidSetCallBack(CallBackFunc,EXTI_LINE11);
    DIO_voidSetPinValue(USONIC_TRIGGER,1);
    TIMER_voidSetBusyWait(USONIC_TIMER,10);
    DIO_voidSetPinValue(USONIC_TRIGGER,0);
    TIMER_voidSetResetTimer(USONIC_TIMER,TIMER_SET,0xFFFF);
    while (DIO_u8GetPinValue(USONIC_ECHO)==0);
    TIMER_voidStartStopCount(USONIC_TIMER ,TIMER_START);
    EXTI_voidEnableEXTI(EXTI_LINE11);
}


void CallBackFunc(void){
    TIMER_voidStartStopCount(USONIC_TIMER ,TIMER_STOP);
    Local_f32Distance=(f32)TIMER_u16GetElapsedTime(USONIC_TIMER)/58.82;
    TIMER_voidSetResetTimer(USONIC_TIMER,TIMER_RESET,0);
    Local_CallBackFunc(Local_f32Distance);
}
*/
