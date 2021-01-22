/**********************************************/
/* Author   : Eslam Khaled                    */
/* Date     : 2020-09-28                      */
/* Version  : V01                             */
/**********************************************/
#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

#define UART1      1
#define UART2      2

void UART_voidInit(void);
void UART_voidTransmit (u8 Copy_UARTNumber , u8* Copy_DataTransmitted);
u8 UART_u8Receive  (u8 Copy_UARTNumber , u16 Copy_UARTTimeOut ); // Copy_UARTTimeOut = 0 -> means no time out

#endif