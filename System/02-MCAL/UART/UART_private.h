/**********************************************/
/* Author   : Eslam Khaled                    */
/* Date     : 2020-09-28                      */
/* Version  : V01                             */
/**********************************************/
#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H

typedef struct
{
    u32 SR;
    u32 DR;
    u32 BRR;
    u32 CR1;
    u32 CR2;
    u32 CR3;
    u32 GTPR;
}USART1_Registers;

typedef struct
{
    u32 SR;
    u32 DR;
    u32 BRR;
    u32 CR1;
    u32 CR2;
    u32 CR3;
    u32 GTPR;
}USART2_Registers;

#define USART1 ((USART1_Registers *) 0x40013800)
#define USART2 ((USART2_Registers *) 0x40004400)

volatile static u16 Get_BRR_Value (void);

#define     UART_8BIT               0
#define     UART_9BIT               1

#define     UART_IDLE_LINE          0
#define     UART_ADDRESS_MARK       1

#define     UART_EVEN_PARITY        0
#define     UART_ODD_PARITY         1

#define     UART_PC_DISABLE         0
#define     UART_PC_ENABLE          1

#define     UART_1_STOP_BITS             0
#define     UART_HALF_STOP_BITS          1
#define     UART_2_STOP_BITS             2
#define     UART_ONE_HALF_STOP_BITS      3


#endif