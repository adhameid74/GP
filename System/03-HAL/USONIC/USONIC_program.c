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


#include "DIO_interface.h"
#include "TIMER_interface.h"
#include "DTC_interface.h"

#include "UDS_InputOutputControlByIdentifier_interface.h"

#include "USONIC_interface.h"
#include "USONIC_private.h"
#include "USONIC_config.h"

u8 Local_u8Flag=0;


void USONIC_voidInit()
{
    //Set ECHO pin as 2MHZ output pin and initialy Low
	Port_SetPinDirection( USONIC1_TRIGGER, OUTPUT_S2MHZ);
    Port_SetPinDirection( USONIC2_TRIGGER, OUTPUT_S2MHZ);
	Port_SetPinMode( USONIC1_TRIGGER, GP_OUTPUT_PUSH_PULL );
    Port_SetPinMode( USONIC2_TRIGGER, GP_OUTPUT_PUSH_PULL );
	Dio_WriteChannel( USONIC1_TRIGGER, 0);
    Dio_WriteChannel( USONIC2_TRIGGER, 0);
    //Set the Trigger pin as floating input
	Port_SetPinDirection( USONIC1_ECHO, INPUT);
    Port_SetPinDirection( USONIC2_ECHO, INPUT);
	Port_SetPinMode( USONIC1_ECHO, INPUT_PULL_DOWN );
    Port_SetPinMode( USONIC2_ECHO, INPUT_PULL_DOWN );
    //Set the prescaler of the timer so that the CLK is 1MHZ
    TIMER_voidSetPrescaler(USONIC_TIMER,8);

    //DTC PART
    for (u8 Local_u8Counter = 0; Local_u8Counter < DTCNUM; Local_u8Counter++)
    {
        dtc_usonic[Local_u8Counter].Status = DTC_STATUS_MASK;
		dtc_usonic[Local_u8Counter].FaultDetectionCounter = 0;
		dtc_usonic[Local_u8Counter].Property = &USONIC_PROP[Local_u8Counter];
		dtc_usonic[Local_u8Counter].Property->Bits = 0;
        dtc_usonic[Local_u8Counter].Property->Code=DTC_Usonic1EchoDisconnect+Local_u8Counter;
        dtc_usonic[Local_u8Counter].Property->TestFailedThreshold=FAILED_THRESHOLD;
        dtc_usonic[Local_u8Counter].Property->TestPassedThreshold=PASSED_THRESHOLD;
        dtc_usonic[Local_u8Counter].Property->AgingThreshold=AGING_THRESHOLD;
    }
}

f32 USONIC_f32GetDistance(u8 Copy_u8UsonicNumber, u8* Copy_pu8Light_Color)
{
    dtcItem_t* ptr;
    Local_u8Flag=0;
    u8 Local_u8Counter=0;
    u8 Local_u8Counter2=0;
    f32 Local_f32Distance=0;
    u16 Local_u16TimerCount=0;
    if (Copy_u8UsonicNumber==USONIC1)
    {
        Dio_WriteChannel( USONIC1_TRIGGER, 1);
        TIMER_voidSetBusyWait(USONIC_TIMER,10);
        Dio_WriteChannel( USONIC1_TRIGGER, 0);
        TIMER_voidSetResetTimer(USONIC_TIMER,TIMER_SET,0xFFFF);
        while (Dio_ReadChannel(USONIC1_ECHO)==0&&Local_u8Counter<0xFF)
        {
            Local_u8Counter++;
        }
        if (Local_u8Counter!=0xFF)
        {
            TIMER_voidStartStopCount(USONIC_TIMER ,TIMER_START);
            while (Dio_ReadChannel(USONIC1_ECHO)==1&&Local_u8Counter2<15000)
            {
            Local_u8Counter2++;
            }
            TIMER_voidStartStopCount(USONIC_TIMER ,TIMER_STOP);
            Local_u16TimerCount=TIMER_u16GetElapsedTime(USONIC_TIMER);
            Local_f32Distance=(f32)Local_u16TimerCount/58.82;
            TIMER_voidSetResetTimer(USONIC_TIMER,TIMER_RESET,0);
        }


        ptr=&dtc_usonic[0];
        if (Local_u8Counter==0xFF)       //ECHO PIN DISCONNECTED OR NOT RECEIVED
        {
        	DTC_u8DetectFault(ptr, 1);
        }
        else{                                                        //READ ANY DISTANCE
        	DTC_u8DetectFault(ptr, 0);
            ptr=&dtc_usonic[1];
            if (Local_u8Counter2==15000)    //ECHO  NOT RECEIVED
            {
            	DTC_u8DetectFault(ptr, 1);
            }
            else{
            	DTC_u8DetectFault(ptr, 0);

                ptr=&dtc_usonic[2];
                if (Local_u16TimerCount<1766)    //less than 30 cm   
                {
                	DTC_u8DetectFault(ptr, 1);
                    *Copy_pu8Light_Color = USONIC_RED_LIGHT;                //RED LED

                }
                else if (Local_u16TimerCount>=1766)
                {
                	DTC_u8DetectFault(ptr, 0);
                }

                ptr=&dtc_usonic[3];
                if (Local_u16TimerCount>=1766 && Local_u16TimerCount<5900)    //less than 100 cm
                {
                	DTC_u8DetectFault(ptr,1);
                    *Copy_pu8Light_Color = USONIC_YELLOW_LIGHT;                    //YELLOW LED
                }
                else if (Local_u16TimerCount<1766  || Local_u16TimerCount>=5900)
                {
                	DTC_u8DetectFault(ptr, 0);
                }

                ptr=&dtc_usonic[4];
                if (Local_u16TimerCount>=5900)   //less than 250 cm
                {
                	DTC_u8DetectFault(ptr, 1);
                    *Copy_pu8Light_Color = USONIC_GREEN_LIGHT;                   //GREEN LED
                }
                else if (Local_u16TimerCount<5900)
                {
                	DTC_u8DetectFault(ptr, 0);
                }
            }
        }

        switch (USONIC1_whatShouldIdo)
        {
        case returnControlToECU:
            USONIC1_f32LastValue=Local_f32Distance;
            return Local_f32Distance;
            break;
        case shortTermAdjustment:
            return USONIC1_valueToUse;
            break;
        case freezeCurrentState:
            return USONIC1_f32LastValue;
            break;
        case resetToDefault:
            USONIC1_f32LastValue=Local_f32Distance;
            return USONIC1_f32DefaultValue;
            break;
        default:
            break;
        }
    }
    else{
        Dio_WriteChannel( USONIC2_TRIGGER, 1);
        TIMER_voidSetBusyWait(USONIC_TIMER,10);
        Dio_WriteChannel( USONIC2_TRIGGER, 0);
        TIMER_voidSetResetTimer(USONIC_TIMER,TIMER_SET,0xFFFF);
        while (Dio_ReadChannel(USONIC2_ECHO)==0&&Local_u8Counter<0xFF)
        {
            Local_u8Counter++;
        }
        if (Local_u8Counter!=0xFF)
        {
            TIMER_voidStartStopCount(USONIC_TIMER ,TIMER_START);
            while (Dio_ReadChannel(USONIC2_ECHO)==1&&Local_u8Counter2<15000)
            {
            Local_u8Counter2++;
            }
            TIMER_voidStartStopCount(USONIC_TIMER ,TIMER_STOP);
            Local_u16TimerCount=TIMER_u16GetElapsedTime(USONIC_TIMER);
            Local_f32Distance=(f32)Local_u16TimerCount/58.82;
            TIMER_voidSetResetTimer(USONIC_TIMER,TIMER_RESET,0);
        }

        ptr=&dtc_usonic[5];
        if (Local_u8Counter==0xFF)       //ECHO PIN DISCONNECTED OR NOT RECEIVED
        {
        	DTC_u8DetectFault(ptr, 1);
        }
        else{                                                        //READ ANY DISTANCE
        	DTC_u8DetectFault(ptr, 0);
            ptr=&dtc_usonic[6];
            if (Local_u8Counter2==15000)    //ECHO  NOT RECEIVED
            {
            	DTC_u8DetectFault(ptr, 1);
            }
            else{
            	DTC_u8DetectFault(ptr, 0);

                ptr=&dtc_usonic[7];
                if (Local_u16TimerCount<1766)    //less than 30 cm   
                {
                	DTC_u8DetectFault(ptr, 1);
                    *Copy_pu8Light_Color = USONIC_RED_LIGHT;                //RED LED

                }
                else if (Local_u16TimerCount>=1766)
                {
                	DTC_u8DetectFault(ptr, 0);
                }

                ptr=&dtc_usonic[8];
                if (Local_u16TimerCount>=1766 && Local_u16TimerCount<5900)    //less than 100 cm
                {
                	DTC_u8DetectFault(ptr,1);
                    *Copy_pu8Light_Color = USONIC_YELLOW_LIGHT;                    //YELLOW LED
                }
                else if (Local_u16TimerCount<1766  || Local_u16TimerCount>=5900)
                {
                	DTC_u8DetectFault(ptr, 0);
                }

                ptr=&dtc_usonic[9];
                if (Local_u16TimerCount>=5900 )   //less than 250 cm (14750)
                {
                	DTC_u8DetectFault(ptr, 1);
                	*Copy_pu8Light_Color = USONIC_GREEN_LIGHT;                   //GREEN LED
                }
                else if (Local_u16TimerCount<5900)
                {
                	DTC_u8DetectFault(ptr, 0);
                }
            }
        }

        switch (USONIC2_whatShouldIdo)
        {
        case returnControlToECU:
            USONIC2_f32LastValue=Local_f32Distance;
            return Local_f32Distance;
            break;
        case shortTermAdjustment:
            return USONIC2_valueToUse;
            break;
        case freezeCurrentState:
            return USONIC2_f32LastValue;
            break;
        case resetToDefault:
            USONIC2_f32LastValue=Local_f32Distance;
            return USONIC2_f32DefaultValue;
            break;
        default:
            break;
        }
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
