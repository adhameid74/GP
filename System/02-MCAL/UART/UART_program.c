/**********************************************/
/* Author   : Eslam Khaled                    */
/* Date     : 2020-09-28                      */
/* Version  : V01                             */
/**********************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include  "UART_interface.h"
#include  "UART_config.h"
#include  "UART_private.h"

void UART_voidInit(void)
{
    USART1 -> CR1 = 0 ;
    #if UART_WORD_LENGTH == UART_9BIT
        SET_BIT(USART1 -> CR1 , 12);
    #endif
    #if UART_WAKEUP == UART_ADDRESS_MARK
        SET_BIT(USART1 -> CR1 , 11);
    #endif
    #if UART_PARITY_CONTROL == UART_PC_ENABLE
        SET_BIT(USART1 -> CR1 , 10);
    #endif    
    #if UART_PARITY == UART_ODD_PARITY
        SET_BIT(USART1 -> CR1 , 9);
    #endif

    USART1 -> CR2 = 0;
    #if UART_STOP_BITS == UART_HALF_STOP_BITS
        SET_BIT(USART1 -> CR2 , 12);
    #elif UART_STOP_BITS == UART_2_STOP_BITS
        SET_BIT(USART1 -> CR2 , 13);
    #elif UART_STOP_BITS == UART_ONE_HALF_STOP_BITS
        SET_BIT(USART1 -> CR2 , 12);
        SET_BIT(USART1 -> CR2 , 13);
    #endif

    USART1 -> SR = 0 ;      // Clear status Register

    USART1 -> BRR = Get_BRR_Value();
    SET_BIT(USART1 -> CR1 , 13) ;        // USART Enable 
    SET_BIT(USART1 -> CR1 , 3)  ;        // Transmitter Enable 
    SET_BIT(USART1 -> CR1 , 2)  ;        // Receiver Enable 
};
void UART_voidTransmit (u8 Copy_UARTNumber , u8* Copy_DataTransmitted)
{
    u8 Local_counter = 0;
    while(Copy_DataTransmitted[Local_counter] )
    {
        USART1 -> DR = Copy_DataTransmitted[Local_counter];
        while(GET_BIT(USART1 -> SR , 6) == 0);      // Wait till the transmit is complete
        Local_counter += 1 ;
    }
}
u8 UART_u8Receive  (u8 Copy_UARTNumber )
{
    u8 Local_Data = 0;
    u16 Local_Timeout = 0 ;
    while(GET_BIT(USART1 -> SR , 5) == 0)
    {
        Local_Timeout += 1;
        if(Local_Timeout = 10000)
        {
            Local_Data = 255;
            break;   
        }
    }
    Local_Data = (USART1 -> DR) & 0xFF;         // return 8bit only
    return Local_Data;
}
volatile static u16 Get_BRR_Value (void)
{
    f32 DIV = UART_Fck/(16.0*UART_BAUD_RATE);
    u16 mantissa = DIV ;
    f32 flt = DIV - mantissa ;
    flt  = flt * 16 ;
    if(flt >= 16.0) mantissa += 1;
    u16 flt_int = flt ;
    f32 flt_float = flt - flt_int ;
    if(flt_float >= 0.5) flt_int += 1;
    u16 BRR =  (mantissa<<4) + flt_int ;
    return BRR ;
}