/**********************************************/
/* Author   : Eslam Khaled                    */
/* Date     : 2020-09-28                      */
/* Version  : V01                             */
/**********************************************/
#ifndef UART_CONFIG_H
#define UART_CONFIG_H

#define UART_BAUD_RATE       9600
#define UART_Fck             8000000

#define UART_WORD_LENGTH    UART_8BIT
/* Options */
/*
    UART_8BIT
    UART_9BIT
*/
#define UART_WAKEUP     UART_IDLE_LINE
/* Options */
/*
    UART_IDLE_LINE
    UART_ADDRESS_MARK
*/
#define UART_PARITY     UART_EVEN_PARITY
/* Options */
/*
    UART_EVEN_PARITY
    UART_ODD_PARITY
*/
#define UART_PARITY_CONTROL     UART_PC_DISABLE
/* Options */
/*
    UART_PC_DISABLE
    UART_PC_ENABLE

    // When the parity control is enabled, the computed parity is inserted at the MSB position 
    // (9th bit if M=1; 8th bit if M=0) and parity is checked on the received data. 
*/
#define UART_STOP_BITS      UART_1_STOP_BITS
/* Options */
/*
    UART_1_STOP_BITS
    UART_HALF_STOP_BITS
    UART_2_STOP_BITS
    UART_ONE_HALF_STOP_BITS

    // The 0.5 Stop bit and 1.5 Stop bit are not available for UART4 & UART5
*/

#endif