/**
 * @file GW_main.c
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 18-07-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO_interface.h"
#include "CAN_interface.h"
#include "DoCAN_interface.h"
#include "NVIC_interface.h"
#include "UART_interface.h"

volatile static u8 ReceivedCommand[50];
volatile static u8 CommandFlag = 0;

void GetDatafromNodeMCU();
void GetResponse(INDICATION_SDU SDU);
u8 AsciiToDecimal(u8 Copy_u8Asci);

void main()
{
    REQUEST_SDU Message;
    CAN_filter_t Filter1;
    u8 Local_u8LowNibble, Local_u8HighNibble, Local_u8Counter;

    Message.SA = SOURCE_ADDRESS;
    Message.TA = TARGET_ADDRESS;

    Filter1.ID = TARGET_ADDRESS;
    Filter1.RTR = CAN_DATA_FRAME;
    Filter1.FIFO_ID = CAN_FIFO0;

    RCC_voidInitSystemClock();
    RCC_voidEnableClock(RCC_APB2, RCC_APB2_GPIOA);
    RCC_voidEnableClock(RCC_APB2, RCC_APB2_USART1);
    RCC_voidEnableClock(RCC_APB1, RCC_APB1_CAN);

    Port_SetPinDirection(PA9, OUTPUT_S10MHZ);
	Port_SetPinMode(PA9, AF_OUTPUT_PUSH_PULL);
	Port_SetPinDirection(PA10, INPUT);
	Port_SetPinMode(PA10, INPUT_FLOATING);

    NVIC_voidEnableInterrupt(NVIC_USART1);
    MUART_voidSetCallback(GetDatafromNodeMCU, MUART1);
    MUART_voidInit(MUART1);

    CAN_voidInit();
    CAN_voidStart();
    CAN_u8WriteFilter(&Filter1);

    CAN_u8SetCallBack(DoCAN_voidIndicateUsData);
    DoCAN_voidSetCallBackForMassage(GetResponse);

    while(1)
    {
        if(CommandFlag)
        {
            Local_u8Counter = 0;
            while( ReceivedCommand[Local_u8Counter] != '\0')
            {
                ReceivedCommand[Local_u8Counter] = AsciiToDecimal(ReceivedCommand[Local_u8Counter]);
                Local_u8Counter++;
            }
            Local_u8Counter = 0;
            Local_u8LowNibble = ReceivedCommand[Local_u8Counter+1];
            Local_u8HighNibble = ReceivedCommand[Local_u8Counter];
            Message.MessageData[Local_u8Counter/2] = (Local_u8HighNibble<<4) | Local_u8LowNibble;
            Local_u8Counter +=2;
            if (Message.MessageData[0] == 0x36)
            {
                Local_u8LowNibble = ReceivedCommand[Local_u8Counter+1];
                Local_u8HighNibble = ReceivedCommand[Local_u8Counter];
                Message.MessageData[Local_u8Counter/2] = (Local_u8HighNibble<<4) | Local_u8LowNibble;
                Local_u8Counter +=2;
                while( ReceivedCommand[Local_u8Counter] != '\0')
                {
                    Message.MessageData[Local_u8Counter-2] = ReceivedCommand[Local_u8Counter];
                    Local_u8Counter++;
                }
                Message.Length.u12 = Local_u8Counter-2;
            }
            else
            {
                while( ReceivedCommand[Local_u8Counter] != '\0' )
                {
                    Local_u8LowNibble = ReceivedCommand[Local_u8Counter+1];
                    Local_u8HighNibble = ReceivedCommand[Local_u8Counter];
                    Message.MessageData[Local_u8Counter/2] = (Local_u8HighNibble<<4) | Local_u8LowNibble;
                    Local_u8Counter +=2;
                }
                Message.Length.u12 = Local_u8Counter/2;
            }
            DoCAN_voidRequestUsData(Message);
            CommandFlag = 0;
        }
    }
}

void GetDatafromNodeMCU(void)
{
	u8 Data = MUART_u8Receive(MUART1);
    static u8 Local_u8Index = 0;
    if( (Data!='\r'))
    {
        ReceivedCommand[Local_u8Index] = Data;
        Local_u8Index++;
    }
    else
    {
        ReceivedCommand[Local_u8Index]='\0';
        Local_u8Index = 0;
        CommandFlag = 1;
    }
}

void GetResponse(INDICATION_SDU SDU)
{
    SDU.MessageData[SDU.Length.u12] = '\0';
    MUART_u8Transmit(MUART1, SDU.MessageData);
}

u8 AsciiToDecimal(u8 Copy_u8Asci)
{
    if ( (Copy_u8Asci >= 48) && (Copy_u8Asci <= 57) )
	{
		return (Copy_u8Asci - 48);
	}
    else if( (Copy_u8Asci >= 65) && (Copy_u8Asci <= 70) )
    {
        return (Copy_u8Asci - 55);
    }
    else if( (Copy_u8Asci >= 97) && (Copy_u8Asci <= 102) )
    {
        return (Copy_u8Asci - 87);
    }
}