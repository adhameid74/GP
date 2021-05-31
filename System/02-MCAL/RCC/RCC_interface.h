/**********************************************************/
/* Author		: Abdallah Hassan 		*/
/* Date 		: 8/8/2020				*/
/* Version		: V01					*/
/**********************************************************/
#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

void RCC_InitSystemClock(void);
void RCC_voidEnableClock(u8 Copy_u8BusId, u8 Copy_u8PerId);
void RCC_voidDisableClock(u8 Copy_u8BusId, u8 Copy_u8PerId);

#define RCC_AHB 			    0
#define RCC_APB1			    1
#define RCC_APB2			    2

#define RCC_AHB_DMA1		    0
#define RCC_AHB_DMA2		    1
#define RCC_AHB_FPEC		    4
#define RCC_AHB_CRC			    6
#define RCC_AHB_FSMC		    8
#define RCC_AHB_SDIO		    10

#define RCC_APB2_AF				0
#define RCC_APB2_GPIOA			2
#define RCC_APB2_GPIOB			3
#define RCC_APB2_GPIOC			4

#define RCC_APB2_ADC1			9
#define RCC_APB2_ADC2			10
#define RCC_APB2_ADC3			15

#define RCC_APB1_TIMER2			0
#define RCC_APB1_TIMER3			1
#define RCC_APB1_TIMER4			2
#define RCC_APB1_TIMER5			3
#define RCC_APB1_TIMER6			4
#define RCC_APB1_TIMER7			5
#define RCC_APB1_TIMER12		6
#define RCC_APB1_TIMER13		7
#define RCC_APB1_TIMER14		8
#define RCC_APB2_TIMER1			11
#define RCC_APB2_TIMER8			13
#define RCC_APB2_TIMER9			19
#define RCC_APB2_TIMER10		20
#define RCC_APB2_TIMER11		21

#define RCC_APB1_WATDOG			11

#define RCC_APB2_SPI1			12
#define RCC_APB1_SPI2			14
#define RCC_APB1_SPI3			15

#define RCC_APB2_USART1			14
#define RCC_APB1_USART2			17
#define RCC_APB1_USART3			18
#define RCC_APB1_USART4			19
#define RCC_APB1_USART15		20

#define RCC_APB1_I2C1			21
#define RCC_APB1_I2C2			22

#define RCC_APB1_CAN			25
#define RCC_APB1_DAC			29







#endif
