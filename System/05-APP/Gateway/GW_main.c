#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO_interface.h"
//#include "CAN_interface.h"
//#include "DoCAN_interface.h"
#include "NVIC_interface.h"
#include "UART_interface.h"

volatile static u8 ReceivedCommand[50];

void GetDatafromNodeMCU(void);

void main()
{
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
//    CAN_voidInit();

    while(1)
    {

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
    	MUART_u8Transmit(MUART1,"received: ");
    	MUART_u8Transmit(MUART1,ReceivedCommand);
    }

}
