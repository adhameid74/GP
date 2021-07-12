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

#include "FPEC_interface.h"

#include "PARSE_interface.h"
#include "PARSE_private.h"
#include "PARSE_config.h"

void PARSE_voidFlashRecord(u8* Copy_au8Record)
{
    if( Copy_au8Record[RECORD_TYPE_INDEX] == UPPER_ADDRESS_RECORD )
    {
        SetUpperAddress(Copy_au8Record);
    }
    else if ( Copy_au8Record[RECORD_TYPE_INDEX] == DATA_RECORD )
    {
        FlashData(Copy_au8Record);
    }
}

/*
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
    else if( (Copy_u8Asci >= 97) && (Copy_u8Asci <= 102) )
    {
        return (Copy_u8Asci - 87);
    }
    else
    {
        return ASCII_ERROR;
    }
}
*/
static void SetUpperAddress(u8* Copy_au8Record)
{
    Address &= (u32)0x0000FFFF;
    Address |= (u32)((u32)(Copy_au8Record[4] << 24) | (u32)(Copy_au8Record[5] << 16));
}

static void FlashData(u8* Copy_au8Record)
{
	u8 Local_u8Counter = 0;

	Address &= (u32)0xFFFF0000;
    Address |= (u32)((u32)(Copy_au8Record[1] << 8) | (u32)(Copy_au8Record[2]));

    if( (Copy_au8Record[0] % 2) == 0 )
    {
        for (Local_u8Counter=0;Local_u8Counter<Copy_au8Record[0]/2;Local_u8Counter++)
        {
            Data[Local_u8Counter] = (u16)((u16)(Copy_au8Record[(Local_u8Counter*2)+5] << 8) | (u16)(Copy_au8Record[(Local_u8Counter*2)+4]));
        }
    }
    else
    {
        for (Local_u8Counter=0;Local_u8Counter<Copy_au8Record[0]/2;Local_u8Counter++)
        {
            Data[Local_u8Counter] = (u16)((u16)(Copy_au8Record[(Local_u8Counter*2)+5] << 8) | (u16)(Copy_au8Record[(Local_u8Counter*2)+4]));
        }
        Data[Local_u8Counter] = (u16)((u16)(Copy_au8Record[Copy_au8Record[0]+3]) | (u16)(0xFF00));
        Local_u8Counter++;
    }
    FPEC_voidWriteArea(Address, Data, Local_u8Counter);
}
