/**********************************************/
/* Author   : Abdallah Hassan                 */
/* Date     : 2020-09-27                      */
/* Version  : V01                             */
/**********************************************/
#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H


#define MUART1		1
#define MUART2		2

void MUART_voidInit(u8 Copy_u8TimerNumber);
u8 MUART_u8Transmit(u8 Copy_u8UartNumber,u8 arr[]);
//u8 MUART_u8ReceiveNormal(u8 Copy_u8TimerNumber);
u8 MUART_u8Receive(u8 Copy_u8TimerNumber);
//void MUART_voidClearRxne();
MUART_voidSetCallback(void (*CallBackFunc) (void), u8 Copy_u8UartNumber);

#endif
