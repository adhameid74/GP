/**********************************************/
/* Author   : Eslam Khaled                    */
/* Date     : 8 Aug 2020                      */
/* Version  : V01                             */
/**********************************************/
#ifndef _RCC_INTERFACE_H
#define _RCC_INTERFACE_H

#define RCC_AHB     0
#define RCC_APB1    1
#define RCC_APB2    2

#define RCC_AFIO    0
#define RCC_PORTA   2
#define RCC_PORTB   3
#define RCC_PORTC   4
#define RCC_PORTD   5
#define RCC_PORTE   6
#define RCC_PORTF   7
#define RCC_PORTG   8
#define RCC_ADC1	9
#define RCC_ADC2	10
#define RCC_TIM1	11
#define RCC_SPI1	12
#define RCC_TIM8	13
#define RCC_USART1	14
#define RCC_ADC3	15
#define RCC_TIM9	19
#define RCC_TIM10	20
#define RCC_TIM11	21

void RCC_voidEnableClock     (u8 Copy_u8BusId, u8 Copy_u8PerId);
void RCC_voidDisableClock    (u8 Copy_u8BusId, u8 Copy_u8PerId);
void RCC_voidInitSysClock    (void);

#endif
