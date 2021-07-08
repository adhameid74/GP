/**
 * @file BL_main.c
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 31-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO_interface.h"
#include "I2C_interface.h"
#include "FPEC_interface.h"
#include "EEPROM_interface.h"
#include "PARSE_interface.h"

#define APP_ADDRESS             0x08001004

void main()
{
    volatile u8 BL_au8Record[20];
    volatile u8 BL_ImageAddress = EEPROM_APP_START_ADDRESS;
    volatile u16 BL_ImageNumOfLines;
    u8 Local_u8HighNibble, Local_u8LowNibble;
    Function_t APP = *(Function_t*)(APP_ADDRESS);

    RCC_voidInitSystemClock();
    RCC_voidEnableClock(RCC_APB2, RCC_APB2_GPIOB);
    RCC_voidEnableClock(RCC_APB1, RCC_APB1_I2C1);
    RCC_voidEnableClock(RCC_AHB, RCC_AHB_FPEC);

    /* SCL Pin Configuration */
    Port_SetPinDirection(PB6, OUTPUT_S10MHZ);
    Port_SetPinMode(PB6, AF_OUTPUT_OPEN_DRAIN);
    /* SDA Pin Configuration */
    Port_SetPinDirection(PB7, OUTPUT_S10MHZ);
    Port_SetPinMode(PB7, AF_OUTPUT_OPEN_DRAIN);

    MI2C_voidInit();
    
    Local_u8HighNibble = HEEPROM_u8ReadByte(EEPROM_ADDRESS, EEPROM_NUM_OF_LINES_ADDRESS);
    Local_u8LowNibble = HEEPROM_u8ReadByte(EEPROM_ADDRESS, EEPROM_NUM_OF_LINES_ADDRESS-1);
    BL_ImageNumOfLines = (u16)(((u16)Local_u8HighNibble<<8) | (u16)Local_u8LowNibble);
    if ( BL_ImageNumOfLines == 0xFFFF )
    {
        APP();
    }

    FPEC_voidEraseAppArea();
    for(u8 Local_u8LinesCounter = 0; Local_u8LinesCounter < BL_ImageNumOfLines; Local_u8LinesCounter++)
    {
        BL_au8Record[0] = HEEPROM_u8ReadByte(EEPROM_ADDRESS, BL_ImageAddress++);
        for (u8 Local_u8Counter = 0; Local_u8Counter < (BL_au8Record[0]+3); Local_u8Counter++)
        {
            BL_au8Record[Local_u8Counter+1] = HEEPROM_u8ReadByte(EEPROM_ADDRESS, BL_ImageAddress++);
        }
        PARSE_voidFlashRecord(BL_au8Record);
    }
    HEEPROM_voidWriteByte(EEPROM_ADDRESS, EEPROM_NUM_OF_LINES_ADDRESS, 0xFF);
    HEEPROM_voidWriteByte(EEPROM_ADDRESS, EEPROM_NUM_OF_LINES_ADDRESS-1, 0xFF);
    APP();
}