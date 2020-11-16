/**
 * @file ADC_private.h
 * @author Abdallah Hassan (Abdallahhashem029@gmail.com)
 * @brief ADC private file in Stm32f103xxx
 * @version 0.1
 * @date 2020-11-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

typedef struct
{
	volatile u32	SR;
	volatile u32	CR1;
	volatile u32	CR2;
	volatile u32	SMPR[2];
	volatile u32	JOFR[4];
	volatile u32	HTR;
	volatile u32	LTR;
	volatile u32	SQR[3];
	volatile u32	JSQR;
	volatile u32	JDR[4];
	volatile u32	DR;

}MADC_Type;

#define MADC	((MADC_Type*)0x40012400)

#define AWDEN			23
#define ADON			0
#define EXTTRIG 		20
#define JEXTTRIG		15
#define JSWSTART_BIT	21
#define ALIGN 			11
#define SWSTART_BIT		22
#define EOC 			1
#define EOCIE			5
#define JEOCIE			7
#define CONT 			1
#define SCAN 			8
#define DISCEN 			11
#define JDISCEN			12

#define DISCONTINUOUS_MODE									1
#define SINGLE_CHANNEL_CONTINUOUS_CONVERSION_MODE			2
#define SINGLE_CHANNEL_SINGLE_CONVERSION_MODE				3
#define MULTI_CHANNEL_CONTINUOUS_CONVERSION_MODE			4
#define MULTI_CHANNEL_SINGLE_CONVERSION_MODE				5

#define ENABLE												1
#define DISABLE												2

#define RIGHT_ALIGNMENT										1
#define LEFT_ALIGNMENT										2					

#define TIMER1_CC1											0
#define TIMER1_CC2											1
#define TIMER1_CC3											2
#define TIMER2_CC2											3
#define TIMER3_TRGO											4
#define TIMER4_CC4											5
#define EXTI_LINE_11										6
#define SWSTART												7

#define TIMER1_TRGO											0
#define TIMER1_CC4											1
#define TIMER2_TRGO											2
#define TIMER2_CC1											3
#define TIMER3_CC4											4
#define TIMER4_TRGO											5
#define EXTI_LINE_15										6
#define JSWSTART											7

#endif
