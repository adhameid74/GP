/**
 * @file ADC_program.c
 * @author Abdallah Hassan (Abdallahhashem029@gmail.com)
 * @brief ADC source file in Stm32f103xxx
 * @version 0.1
 * @date 2020-11-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include  "ADC_interface.h"
#include  "ADC_config.h"
#include  "ADC_private.h"

void (*ADC_ISR)(u16) = NULL;

void ADC_voidInit(void)
{
	MADC->CR1 = 0;
	MADC->CR2 = 0;
	MADC->SQR[0] = 0;
	MADC->JSQR = 0;

	/*Enable ADC*/
	SET_BIT(MADC->CR2,ADON);

	#if ADC_MODE == SINGLE_CHANNEL_SINGLE_CONVERSION_MODE
	#elif ADC_MODE == DISCONTINUOUS_MODE
		#if ADC_DISCONTINUOUS_REGULAR == ENABLE
			SET_BIT(MADC->CR1,DISCEN);
		#elif ADC_DISCONTINUOUS_INJECTED == ENABLE
			SET_BIT(MADC->CR1,JDISCEN);
		#else 
			/*error*/
		#endif
		MADC->CR1 |= ((ADC_DISCONTINUOUS_REGULAR_CHANNELS-1) << 13);
	#elif ADC_MODE == SINGLE_CHANNEL_CONTINUOUS_CONVERSION_MODE
			SET_BIT(MADC->CR2,CONT);
	#elif ADC_MODE == MULTI_CHANNEL_CONTINUOUS_CONVERSION_MODE
			SET_BIT(MADC->CR2,CONT);
			SET_BIT(MADC->CR1,SCAN);
	#elif ADC_MODE == MULTI_CHANNEL_SINGLE_CONVERSION_MODE
			SET_BIT(MADC->CR1,SCAN);
	#else 
			/*error*/
	#endif

	/*ENABLE EXTERNAL TRIGGER TO START THE CONVERSION FRO REGULAR CHANNELS*/
	#if ADC_EXTERNAL_REGULAR == ENABLE
		SET_BIT(MADC->CR2,EXTTRIG);
		MADC->CR2 |= ADC_EXTERNAL_REGULAR_SELECT << 17;
	#elif ADC_EXTERNAL_REGULAR == DISABLE
	#else 
		/*error*/
	#endif

	/*ENABLE EXTERNAL TRIGGER TO START THE CONVERSION FRO INJECTED CHANNELS*/
	#if ADC_EXTERNAL_INJECTED == ENABLE
		SET_BIT(MADC->CR2,JEXTTRIG);
		MADC->CR2 |= ADC_EXTERNAL_INJECTED_SELECT << 12;
	#elif ADC_EXTERNAL_INJECTED == DISABLE
	#else 
		/*error*/
	#endif	

	/*Choose Right alignment to read data*/
	#if ADC_DATA_ALIGN == RIGHT_ALIGNMENT
		CLR_BIT(MADC->CR2,ALIGN);
	#elif ADC_DATA_ALIGN == LEFT_ALIGNMENT
		SET_BIT(MADC->CR2,ALIGN);
	#else 
		/*error*/
	#endif

	#if ADC_EOC_REGULAR_INTERRUPT == ENABLE
		SET_BIT(MADC->CR1,EOCIE);
	#elif ADC_EOC_REGULAR_INTERRUPT	== DISABLE
	#else
		/*error*/
	#endif

	#if ADC_EOC_INJECTED_INTERRUPT == ENABLE
		SET_BIT(MADC->CR1,JEOCIE);
	#elif ADC_EOC_INJECTED_INTERRUPT == DISABLE
	#else
		/*error*/
	#endif
}

void ADC_voidAssignRegularSequence(u8 Copy_u8SeqLength, u8 Copy_u8SeqChannels[])
{
	MADC->SQR[0] |= (Copy_u8SeqLength-1) << 20;
	u8 Local_u8Index = 0;
	for(u8 Local_u8Counter = 1; Local_u8Counter <= Copy_u8SeqLength ; Local_u8Counter++)
	{
		if(Local_u8Counter <= 6)
		{
			MADC->SQR[2] |= (Copy_u8SeqChannels[Local_u8Counter-1]) << ((Local_u8Counter-1)*5);
		}
		else if(Local_u8Counter <=12)
		{
			Local_u8Index = Local_u8Counter-6;
			MADC->SQR[1] |= (Copy_u8SeqChannels[Local_u8Counter-1]) << ((Local_u8Index-1)*5);
		}
		else if(Local_u8Counter <=16)
		{
			Local_u8Index = Local_u8Counter-12;
			MADC->SQR[0] |= (Copy_u8SeqChannels[Local_u8Counter-1]) << ((Local_u8Index-1)*5);
		}
	}
}

void ADC_voidAssignInjectedSequence(u8 Copy_u8SeqLength, u8 Copy_u8SeqChannels[])
{
	MADC->JSQR |= (Copy_u8SeqLength-1) << 20;
	for(u8 Local_u8Counter = 1; Local_u8Counter <= Copy_u8SeqLength ; Local_u8Counter++)
	{
		MADC->JSQR |= (Copy_u8SeqChannels[Local_u8Counter-1]) << (17-((Local_u8Counter-1)*5));
	}
}

void ADC_voidSetCallBackRegular(void (*Copy_Notification)(u16))
{
	ADC_ISR = Copy_Notification;
}

u16 ADC_u16ReadRegularSync()
{
	u16 ADC_Reading, Local_u16Timer = 0;

	SET_BIT(MADC->CR2,SWSTART_BIT);
	while( (GET_BIT(MADC->SR,EOC) == 0) && ( Local_u16Timer < ADC_TIMEOUT ) )
	{
		Local_u16Timer++;
	}

	if ( Local_u16Timer == ADC_TIMEOUT )
	{
		return 0xFFFF;
	}
	
	ADC_Reading = 0xFFFF & MADC->DR;
	//CLR_BIT(MADC->SR,EOC);
	return ADC_Reading;
}

void ADC_voidStartRegularConversion()
{
	SET_BIT(MADC->CR2,SWSTART_BIT);
}

void ADC1_2_IRQHandler()
{
	ADC_ISR(MADC->DR);
}
