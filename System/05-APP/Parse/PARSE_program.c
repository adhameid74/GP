/**
 * @file PARSE_program.c
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 0.1
 * @date 30-05-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "PARSE_interface.h"
#include "PARSE_private.h"
#include "PARSE_config.h"

void PARSE_voidFlashRecord(u8* Copy_au8Record)
{
    if( Copy_au8Record[RECORD_TYPE_INDEX] == UPPER_ADDRESS_RECORD )
    {

    }
}

static u8 AsciiToDecimal(u8 Copy_u8Asci)
{
    if ( (Copy_u8Asci >= 48) && (Copy_u8Asci <= 57) )
	{
		return (Copy_u8Asci - 48);
	}
    else if( (Copy_u8Asci >= 65) && (Copy_u8Asci <= 70) )
    {
        return (Copy_u8Asci - 55);
    }
    else
    {
        return ASCII_ERROR;
    }
}

static void SetUpperAddress(u8* Copy_au8Record)
{
    u8 Local_u8Digit0, Local_u8Digit1, Local_u8Digit2, Local_u8Digit3;
    Local_u8Digit0 = AsciiToDecimal(Copy_au8Record[9]);
    Local_u8Digit1 = AsciiToDecimal(Copy_au8Record[10]);
    Local_u8Digit2 = AsciiToDecimal(Copy_au8Record[11]);
    Local_u8Digit3 = AsciiToDecimal(Copy_au8Record[12]);
    Address &= (u32)0x0000FFFF;
    Address |= (u32)((u32)(Local_u8Digit0 << 28) | (u32)(Local_u8Digit1 << 24) | (u32)(Local_u8Digit2 << 20) | (u32)(Local_u8Digit3 << 16));
}

static void FlashData(u8* Copy_au8Record)
{
    u8 Local_u8CC, Local_u8Digit0, Local_u8Digit1, Local_u8Digit2, Local_u8Digit3;
	u8 Local_u8Counter = 0;

	Local_u8Digit0 = AsciiToDecimal (Copy_au8Record[1]);
	Local_u8Digit1 = AsciiToDecimal (Copy_au8Record[2]);
	Local_u8CC = (Local_u8Digit0<<4) | Local_u8Digit1;

	Local_u8Digit0 = AsciiToDecimal (Copy_au8Record[3]);
	Local_u8Digit1 = AsciiToDecimal (Copy_au8Record[4]);
	Local_u8Digit2 = AsciiToDecimal (Copy_au8Record[5]);
	Local_u8Digit3 = AsciiToDecimal (Copy_au8Record[6]);

	Address &= (u32)0xFFFF0000;
	Address |= (u32)((u32)Local_u8Digit3) | ((u32)Local_u8Digit2 << 4) | ((u32)Local_u8Digit1 << 8) | ((u32)Local_u8Digit0<<12);

    if( (Local_u8CC % 2) == 0 )
    {
        for (Local_u8Counter=0;Local_u8Counter<Local_u8CC/2;Local_u8Counter++)
        {
            Local_u8Digit0 = AsciiToDecimal (Copy_au8Record[4*Local_u8Counter+9]);
            Local_u8Digit1 = AsciiToDecimal (Copy_au8Record[4*Local_u8Counter+10]);
            Local_u8Digit2 = AsciiToDecimal (Copy_au8Record[4*Local_u8Counter+11]);
            Local_u8Digit3 = AsciiToDecimal (Copy_au8Record[4*Local_u8Counter+12]);

            Data[Local_u8Counter] = (u16)((u16)Local_u8Digit3 << 8) | ((u16)Local_u8Digit2 << 12) | ((u16)Local_u8Digit1) | ((u16)Local_u8Digit0<<4);
        }
    }
    else
    {
        for (Local_u8Counter=0;Local_u8Counter<Local_u8CC/2;Local_u8Counter++)
        {
            Local_u8Digit0 = AsciiToDecimal (Copy_au8Record[4*Local_u8Counter+9]);
            Local_u8Digit1 = AsciiToDecimal (Copy_au8Record[4*Local_u8Counter+10]);
            Local_u8Digit2 = AsciiToDecimal (Copy_au8Record[4*Local_u8Counter+11]);
            Local_u8Digit3 = AsciiToDecimal (Copy_au8Record[4*Local_u8Counter+12]);

            Data[Local_u8Counter] = (Local_u8Digit3 << 8) | (Local_u8Digit2 << 12) | (Local_u8Digit1) | (Local_u8Digit0<<4);
        }
        Local_u8Digit0 = AsciiToDecimal (Copy_au8Record[2*Local_u8CC+7]);
        Local_u8Digit1 = AsciiToDecimal (Copy_au8Record[2*Local_u8CC+8]);
        Local_u8Digit2 = 0xFF;
        Local_u8Digit3 = 0xFF;

        Data[Local_u8Counter] = (Local_u8Digit3 << 8) | (Local_u8Digit2 << 12) | (Local_u8Digit1) | (Local_u8Digit0<<4);
        Local_u8Counter++;
    }
    FPEC_voidWriteArea(Address, Data, Local_u8Counter);
}
