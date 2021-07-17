#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO_interface.h"
#include "CAN_interface.h"
#include "DoCAN_interface.h"
#include "NVIC_interface.h"
#include "UART_interface.h"

static u8 ReceivedCommand[50];

void GetDatafromNodeMCU(u8 Data);

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

void GetDatafromNodeMCU(u8 Data)
{
    static u8 Local_u8Index = 0;

}