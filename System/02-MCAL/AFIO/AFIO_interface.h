/**********************************************/
/* Author   : Eslam Khaled                    */
/* Date     : 2020-09-03                      */
/* Version  : V01                             */
/**********************************************/
#ifndef AFIO_INTERFACE_H
#define AFIO_INTERFACE_H

#define AFIO_PORTA          0b0000
#define AFIO_PORTB          0b0001
#define AFIO_PORTC          0b0010

void AFIO_voidSetEXTIConfig (u8 Copy_u8Line , u8 Copy_u8Port);

#endif