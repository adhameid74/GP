/**
 * @file FPEC_program.c
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 0.1
 * @date 29-05-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "FPEC_interface.h"
#include "FPEC_private.h"
#include "FPEC_config.h"

void FPEC_voidErasePage(u8 Copy_u8PageNumber)
{
	while( GET_BIT(FPEC_SR, SR_BSY) == 1 );
	if( GET_BIT(FPEC_CR, CR_LOCK) == 1 )
	{
		FPEC_KEYR = KEY1;
		FPEC_KEYR = KEY2;
	}
	SET_BIT(FPEC_CR, CR_PER);
	FPEC_AR = (u32)(Copy_u8PageNumber * 1024) + 0x08000000;
	SET_BIT(FPEC_CR, CR_STRT);
	while( GET_BIT(FPEC_SR, SR_BSY) == 1 );
	SET_BIT(FPEC_SR, SR_EOP);
	CLR_BIT(FPEC_CR, CR_PER);
}

void FPEC_voidEraseAppArea()
{
	for (u8 Local_u8Counter = FPEC_APP_FIRST_PAGE; Local_u8Counter <= FPEC_APP_LAST_PAGE; Local_u8Counter++)
	{
		FPEC_voidErasePage(Local_u8Counter);
	}
}

void FPEC_voidMassErase()
{
	while( GET_BIT(FPEC_SR, SR_BSY) == 1 );
	if( GET_BIT(FPEC_CR, CR_LOCK) == 1 )
	{
		FPEC_KEYR = KEY1;
		FPEC_KEYR = KEY2;
	}
	SET_BIT(FPEC_CR, CR_MER);
	SET_BIT(FPEC_CR, CR_STRT);
	while( GET_BIT(FPEC_SR, SR_BSY) == 1 );
	SET_BIT(FPEC_SR, SR_EOP);
	CLR_BIT(FPEC_CR, CR_MER);
}

void FPEC_voidWriteArea(u32 Copy_u32Address, u16* Copy_u16Data, u8 Copy_u8Length)
{
	while( GET_BIT(FPEC_SR, SR_BSY) == 1 );
	if( GET_BIT(FPEC_CR, CR_LOCK) == 1 )
	{
		FPEC_KEYR = KEY1;
		FPEC_KEYR = KEY2;
	}
	for (u8 Local_u8Counter = 0; Local_u8Counter < Copy_u8Length; Local_u8Counter++)
	{
		SET_BIT(FPEC_CR, CR_PG);
		(*((volatile u16*)Copy_u32Address)) = Copy_u16Data[Local_u8Counter];
		Copy_u32Address+=2;
		while( GET_BIT(FPEC_SR, SR_BSY) == 1 );
		SET_BIT(FPEC_SR, SR_EOP);
		CLR_BIT(FPEC_CR, CR_PG);
	}
}
