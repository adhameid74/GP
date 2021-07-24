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

static void (*UART_CallBack[2]) (void) = {NULL};

void MUART_voidInit(u8 Copy_u8UartNumber)
{
	if(Copy_u8UartNumber==MUART1){
		#if UART1_RX_INTERRUPT == 1
			SET_BIT(MUART->CR1,5);
		#endif
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

u8 MUART_u8Transmit(u8 Copy_u8UartNumber,u8 arr[],u16 Copy_u8Length)
{
	u16 Local_u16Timer;
	if (Copy_u8UartNumber==MUART1)
	{
		for(u16 i = 0; i< Copy_u8Length; i++)
		{
			Local_u16Timer = 0;
			MUART -> DR = arr[i];
			while( ((GET_BIT((MUART -> SR), 6)) == 0) && (Local_u16Timer < MUART_TIMEOUT) )
			{
				Local_u16Timer++;
			}
			if ( Local_u16Timer == MUART_TIMEOUT )
			{
				//DTC_u8DetectFault(&UART_DTC[0], 1);
				return TIMEOUT_ERROR;
			}
			//DTC_u8DetectFault(&UART_DTC[0], 0);
		}
	}
	else
	{
		u8 i = 0;
		while(arr[i] != '\0')
		{
			Local_u16Timer = 0;
			MUART2 -> DR = arr[i];
			while( ((GET_BIT((MUART2 -> SR), 6)) == 0) && (Local_u16Timer < MUART_TIMEOUT) )
			{
				Local_u16Timer++;
			}
			if ( Local_u16Timer == MUART_TIMEOUT )
			{
				//DTC_u8DetectFault(&UART_DTC[0], 1);
				return TIMEOUT_ERROR;
			}
			//DTC_u8DetectFault(&UART_DTC[0], 0);
			i++;
		}
	}
	return NO_ERROR;
}
/*
u8 MUART_u8ReceiveNormal(u8 Copy_u8UartNumber)
{
	u8 Local_u8Received = 0;
	u16 Local_u16Timer = 0;
	if (Copy_u8UartNumber==MUART1)
	{
		while( (GET_BIT(MUART->SR,5) == 0) && (Local_u16Timer < MUART_TIMEOUT) )
		{
			Local_u16Timer++;
		}
		if ( Local_u16Timer == MUART_TIMEOUT )
		{
			return TIMEOUT_ERROR;
		}
		CLR_BIT(MUART->SR,5);
		Local_u8Received = MUART->DR;
		return Local_u8Received;
	}
	else
	{
		while( (GET_BIT(MUART2->SR,5) == 0) && (Local_u16Timer < MUART_TIMEOUT) )
		{
			Local_u16Timer++;
		}
		if ( Local_u16Timer == MUART_TIMEOUT )
		{
			return TIMEOUT_ERROR;
		}
		CLR_BIT(MUART2->SR,5);
		Local_u8Received = MUART2->DR;
		return Local_u8Received;
	}
}
*/

u8 MUART_u8Receive(u8 Copy_u8UartNumber)
{
	u16 timeout = 0;
	if(Copy_u8UartNumber==MUART1)
	{
		while( (GET_BIT(MUART->SR,5) == 0) && (timeout < MUART_TIMEOUT) )
		{
			timeout++;
		}
		if(timeout == MUART_TIMEOUT)
		{
			//DTC_u8DetectFault(&UART_DTC[1], 1);
			return 255;
		}
		//DTC_u8DetectFault(&UART_DTC[1], 0);
		return MUART->DR;
	}
	else
	{
		while( (GET_BIT(MUART2->SR,5) == 0) && (timeout < MUART_TIMEOUT) )
		{
			timeout++;
		}
		if(timeout == MUART_TIMEOUT)
		{
			//DTC_u8DetectFault(&UART_DTC[1], 1);
			return 255;
		}
		//DTC_u8DetectFault(&UART_DTC[1], 0);
		return MUART2->DR;
	}
}
MUART_voidSetCallback(void (*CallBackFunc) (void), u8 Copy_u8UartNumber)
{
	UART_CallBack[Copy_u8UartNumber-1] = CallBackFunc;
}
USART1_IRQHandler(void)
{
	if(UART_CallBack[0] != NULL)
	{
		UART_CallBack[0]();
	}
	if(UART_CallBack[1] != NULL)
	{
		UART_CallBack[1]();
	}
}
/*
u8 MUART_u8Receive2(u8 Copy_u8UartNumber)
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
}*/
