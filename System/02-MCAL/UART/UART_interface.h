/**********************************************/
/* Author   : Abdallah Hassan                 */
/* Date     : 2020-09-27                      */
/* Version  : V01                             */
/**********************************************/
#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H


#define MUSRT1		1
#define MUSRT2		2

void MUART_voidInit(u8 Copy_u8TimerNumber);
void MUART_voidTransmit(u8 Copy_u8TimerNumber,u8 arr[]);
u8 MUART_u8ReceiveNormal(u8 Copy_u8TimerNumber);
u8 MUART_u8ReceiveTimeOut(u8 Copy_u8TimerNumber);
u8 MUART_u8ReceiveTimeOut2(u8 Copy_u8TimerNumber);
void MUART_voidClearRxne();
#endif
