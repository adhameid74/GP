/**********************************************/
/* Author   : Abdallah Hassan                 */
/* Date     : 2020-09-27                      */
/* Version  : V01                             */
/**********************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include  "UART_interface.h"
#include  "UART_config.h"
#include  "UART_private.h"

void MUART_voidInit(u8 Copy_u8UartNumber)
{
	if(Copy_u8UartNumber==MUART1){
		#if MUART_BAUD_RATE == 9600
			MUART->BRR = 0x341;
		#elif MUART_BAUD_RATE == 115200
			MUART->BRR = 0x45;
		#endif
		SET_BIT(MUART->CR1,2);
		SET_BIT(MUART->CR1,3);
		SET_BIT(MUART->CR1,13);
		SET_BIT(MUART->CR1,5);
		/*CLR STATUS REGISTER*/
		MUART->SR = 0;
	}
	else{
		#if MUART2_BAUD_RATE == 9600
			MUART2->BRR = 0x341;
		#elif MUART2_BAUD_RATE == 115200
			MUART2->BRR = 0x45;
		#endif
		SET_BIT(MUART2->CR1,2);
		SET_BIT(MUART2->CR1,3);
		SET_BIT(MUART2->CR1,13);
		/*CLR STATUS REGISTER*/
		MUART2->SR = 0;
	}

}
void MUART_voidTransmit(u8 Copy_u8UartNumber,u8 arr[])
{
	if (Copy_u8UartNumber==MUART1) {
		u8 i = 0;
		while(arr[i] != '\0'){
			MUART -> DR = arr[i];
			while((GET_BIT((MUART -> SR), 6)) == 0);
			i++;
		}
	}
	else{
		u8 i = 0;
		while(arr[i] != '\0'){
			MUART2 -> DR = arr[i];
			while((GET_BIT((MUART2 -> SR), 6)) == 0);
			i++;
		}
	}
}
u8 MUART_u8ReceiveNormal(u8 Copy_u8UartNumber)
{
	if (Copy_u8UartNumber==MUART1) {
		u8 Local_u8Received = 0;
		while(GET_BIT(MUART->SR,5) == 0);
		CLR_BIT(MUART->SR,5);
		Local_u8Received = MUART->DR;
		return Local_u8Received;
	}
	else{
		u8 Local_u8Received = 0;
		while(GET_BIT(MUART2->SR,5) == 0);
		CLR_BIT(MUART2->SR,5);
		Local_u8Received = MUART2->DR;
		return Local_u8Received;
	}
}
u8 MUART_u8ReceiveTimeOut(u8 Copy_u8UartNumber)
{
	if(Copy_u8UartNumber==MUART1){
		u8 Local_u8Received = 0;
		u16 timeout = 0;
		while(GET_BIT(MUART->SR,5) == 0)
		{
			timeout++;
			if(timeout == 1000)
			{
				Local_u8Received=255;
				break;
			}
		}
		if(Local_u8Received == 0)
		{
			Local_u8Received = MUART->DR;
		}
		return Local_u8Received;
	}
	else{
		u8 Local_u8Received = 0;
		u16 timeout = 0;
		while(GET_BIT(MUART2->SR,5) == 0)
		{
			timeout++;
			if(timeout == 1000)
			{
				Local_u8Received=255;
				break;
			}
		}
		if(Local_u8Received == 0)
		{
			Local_u8Received = MUART2->DR;
		}
		return Local_u8Received;
	}
}
u8 MUART_u8ReceiveTimeOut2(u8 Copy_u8UartNumber)
{
	if(Copy_u8UartNumber==MUART1){
		u8 Local_u8Received = 0;
		u16 timeout = 0;
		while(GET_BIT(MUART->SR,5) == 0)
		{
			timeout++;
			if(timeout == 65000)
			{
				Local_u8Received=255;
				break;
			}
		}
		if(Local_u8Received == 0)
		{
			Local_u8Received = MUART->DR;
		}
		return Local_u8Received;
	}
	else{
		u8 Local_u8Received = 0;
		u16 timeout = 0;
		while(GET_BIT(MUART2->SR,5) == 0)
		{
			timeout++;
			if(timeout == 65000)
			{
				Local_u8Received=255;
				break;
			}
		}
		if(Local_u8Received == 0)
		{
			Local_u8Received = MUART2->DR;
		}
		return Local_u8Received;
	}
}
void MUART_voidClearRxne(){
	CLR_BIT(MUART->SR,5);
}
