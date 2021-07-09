/**
 * @file VSEN_program.c
 * @author Abdallah Hassan (abdallahhashem029@gmail.com)
 * @brief source file for voltage sensor
 * @version 0.1
 * @date 2020-12-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ADC_interface.h"
#include "VSEN_interface.h"
#include "VSEN_config.h"
#include "VSEN_private.h"



u16 VSEN_u8ReadVoltage()
{
	u16 Local_u16Value = 0;
	u16 Local_u16Vref = 0;
	#if VREF == VREF_3_3
		Local_u16Vref = 3300;
	#elif VREF == VREF_5
		Local_u16Vref = 5000;
	#endif
	Local_u16Value= ADC_u16ReadRegularSync();
	Local_u16Value = (u32)Local_u16Vref*(u32)Local_u16Value/ADC_RES;
	Local_u16Value = Local_u16Value*5;
	Local_u16Value = 0.6659*Local_u16Value + 86.18;

	return Local_u16Value;
}

