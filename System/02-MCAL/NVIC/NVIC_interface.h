/**
 * @file NVIC_interface.h
 * @author Ahmed M.Abdelfattah (ahmedm7md24@gmail.com)
 * @brief 
 * @version 1
 * @date 2020-11-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _NVIC_INTERFACE_H
#define _NVIC_INTERFACE_H


void NVIC_voidEnableInterrupt   (u8 Copy_u8IntNumber);
void NVIC_voidDisableInterrupt  (u8 Copy_u8IntNumber);
void NVIC_voidSetPendingFlag    (u8 Copy_u8IntNumber);
void NVIC_voidClearPendingFlag  (u8 Copy_u8IntNumber);
u8   NVIC_u8GetActiveFlag       (u8 Copy_u8IntNumber);
void NVIC_voidSetPriority       (u8 Copy_u8IntNumber ,u8 Copy_u8GroupPriority ,u8 Copy_u8SupPriority ,u32 Copy_u32Channel);
void NVIC_voidSystemReset  (void);


/* NVIC Group and Supgroup config */
#define NVIC_4GROUP_0SUB         0x05FA0300      //4 bits for groups 0 bits for sub groups
#define NVIC_3GROUP_1SUB         0x05FA0400      //3 bits for groups 1 bits for sub groups
#define NVIC_2GROUP_2SUB         0x05FA0500      //2 bits for groups 2 bits for sub groups
#define NVIC_1GROUP_3SUB         0x05FA0600      //1 bits for groups 3 bits for sub groups
#define NVIC_0GROUP_4SUB         0x05FA0700      //0 bits for groups 4 bits for sub groups

/* NVIC Interrupts Definition */
#define NVIC_WWDG				 0
#define NVIC_PVD				 1
#define NVIC_TAMPER				 2
#define NVIC_RTC				 3
#define NVIC_FLASH				 4
#define NVIC_RCC				 5
#define NVIC_EXTI0				 6
#define NVIC_EXTI1				 7
#define NVIC_EXTI2				 8
#define NVIC_EXTI3				 9
#define NVIC_EXTI4				 10
#define NVIC_DMA1_CHANNEL1		 11
#define NVIC_DMA1_CHANNEL2		 12
#define NVIC_DMA1_CHANNEL3		 13
#define NVIC_DMA1_CHANNEL4		 14
#define NVIC_DMA1_CHANNEL5		 15
#define NVIC_DMA1_CHANNEL6		 16
#define NVIC_DMA1_CHANNEL7		 17
#define NVIC_ADC1_2				 18
#define NVIC_USB_HP_CAN_TX		 19
#define NVIC_USB_LP_CAN_RX0		 20
#define NVIC_CAN_RX1			 21
#define NVIC_CAN_SCE			 22
#define NVIC_EXTI9_5			 23
#define NVIC_TIM1_BRK			 24
#define NVIC_TIM1_UP			 25
#define NVIC_TIM1_TRG_COM		 26
#define NVIC_TIM1_CC			 27
#define NVIC_TIM2				 28
#define NVIC_TIM3				 29
#define NVIC_TIM4				 30
#define NVIC_I2C1_EV			 31
#define NVIC_I2C1_ER			 32
#define NVIC_I2C2_EV			 33
#define NVIC_I2C2_ER			 34
#define NVIC_SPI1				 35
#define NVIC_SPI2				 36
#define NVIC_USART1				 37
#define NVIC_USART2				 38
#define NVIC_USART3				 39
#define NVIC_EXTI15_10			 40
#define NVIC_RTCALARM			 41
#define NVIC_USBWAKEUP			 42
#define NVIC_TIM8_BRK			 43
#define NVIC_TIM8_UP			 44
#define NVIC_TIM8_TRG_COM		 45
#define NVIC_TIM8_CC			 46
#define NVIC_ADC3				 47
#define NVIC_FSMC				 48
#define NVIC_SDIO				 49
#define NVIC_TIM5				 50
#define NVIC_SPI3				 51
#define NVIC_UART4				 52
#define NVIC_UART5				 53
#define NVIC_TIM6				 54
#define NVIC_TIM7				 55
#define NVIC_DMA2_CHANNEL1		 56
#define NVIC_DMA2_CHANNEL2		 57
#define NVIC_DMA2_CHANNEL3		 58
#define NVIC_DMA2_CHANNEL4_5	 59

#endif