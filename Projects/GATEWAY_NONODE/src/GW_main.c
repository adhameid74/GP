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

volatile static u8 ReceivedCommand = 0;
//volatile static u8 CommandFlag = 0;

void GetDatafromNodeMCU();
void GetResponse(INDICATION_SDU SDU);
//u8 AsciiToDecimal(u8 Copy_u8Asci);

u8 flag = 0;

void main()
{
    REQUEST_SDU Message;
    CAN_filter_t Filter1;

    Message.SA = SOURCE_ADDRESS;
    Message.TA = TARGET_ADDRESS;
    Message.MessageData[0] = 0x19;
    Message.MessageData[1] = 0x11;
    Message.MessageData[2] = 0x01;
    Message.Length.u12 = 3;
    Filter1.ID = SOURCE_ADDRESS;
    Filter1.RTR = CAN_DATA_FRAME;
    Filter1.FIFO_ID = CAN_FIFO0;

    RCC_voidInitSystemClock();
    RCC_voidEnableClock(RCC_APB2, RCC_APB2_GPIOA);
    //RCC_voidEnableClock(RCC_APB2, RCC_APB2_USART1);
    RCC_voidEnableClock(RCC_APB1, RCC_APB1_CAN);

    /*Port_SetPinDirection(PA9, OUTPUT_S10MHZ);
	Port_SetPinMode(PA9, AF_OUTPUT_PUSH_PULL);
	Port_SetPinDirection(PA10, INPUT);
	Port_SetPinMode(PA10, INPUT_FLOATING);

    NVIC_voidEnableInterrupt(NVIC_USART1);
    MUART_voidSetCallback(GetDatafromNodeMCU, MUART1);
    MUART_voidInit(MUART1);*/

    CAN_voidInit();
    CAN_voidStart();
    CAN_u8WriteFilter(&Filter1);

    CAN_u8SetCallBack(DoCAN_voidIndicateUsData);
    DoCAN_voidSetCallBackForMassage(GetResponse);
    DoCAN_voidRequestUsData(Message);
    while(1)
    {

    }
}

/*void GetDatafromNodeMCU(void)
{

	if(flag == 0)
	{
		u8 Data = MUART_u8Receive(MUART1);
		if(Data == '1')
		{
			ReceivedCommand = 1;
		}
	}

}*/

void GetResponse(INDICATION_SDU SDU)
{
    //MUART_u8Transmit(MUART1, SDU.MessageData,(u16)(SDU.Length.u12));
    flag = 0;
}

/*u8 AsciiToDecimal(u8 Copy_u8Asci)
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
}*/
