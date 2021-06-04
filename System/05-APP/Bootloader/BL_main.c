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
#include "SYSTICK_interface.h"
#include "DIO_interface.h"
#include "I2C_interface.h"
#include "CAN_interface.h"
#include "FPEC_interface.h"
#include "EEPROM_interface.h"
#include "PARSE_interface.h"

#define APP_ADDRESS             0x08001004

typedef void (*Function_t)(void);
Function_t APP = 0;
APP = *(Function_t*)(APP_ADDRESS);
APP();

void CAN_ReceiveCallBack(CAN_msg_t ImageInfo);

volatile static u8 BL_au8Record[20];
volatile static u8 BL_ImageAddress = 0;
volatile static u8 BL_ImageSize = 0;
volatile static u16 BL_ImageNumOfLines = 0;

void main()
{
    CAN_msg_t BL_ImageInfoReqMsg = {CAN_ID_IMAGE_INFO, {0}, 0, CAN_REMOTE_FRAME};
    CAN_filter_t BL_ImageInfoFilter = {CAN_ID_IMAGE_INFO, CAN_DATA_FRAME, CAN_FIFO0};
//    u8 Local_u8CC;

    RCC_voidInitSystemClock();
    RCC_voidEnableClock(RCC_APB2, RCC_APB2_GPIOA);
    RCC_voidEnableClock(RCC_APB2, RCC_APB2_GPIOB);
    RCC_voidEnableClock(RCC_APB1, RCC_APB1_I2C1);
    RCC_voidEnableClock(RCC_APB1, RCC_APB1_CAN);
    RCC_voidEnableClock(RCC_AHB, RCC_AHB_FPEC);

    /* SCL Pin Configuration */
    Port_SetPinDirection(PB6, OUTPUT_S10MHZ);
    Port_SetPinMode(PB6, AF_OUTPUT_OPEN_DRAIN);
    /* SDA Pin Configuration */
    Port_SetPinDirection(PB7, OUTPUT_S10MHZ);
    Port_SetPinMode(PB7, AF_OUTPUT_OPEN_DRAIN);

    MI2C_voidInit();
    SYSTICK_voidInit();
    
    CAN_voidInit();
    CAN_voidStart();
    CAN_u8SetCallBack(CAN_ReceiveCallBack);
    CAN_u8WriteFilter(&BL_ImageInfoFilter);
    CAN_u8WriteMsg(&BL_ImageInfoReqMsg);

    SYSTICK_voidSetIntervalSingle(2000000, APP);
    while(BL_ImageSize = 0);
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

}

void CAN_ReceiveCallBack(CAN_msg_t ImageInfo)
{
    BL_ImageAddress = ImageInfo.DATA[0];
    BL_ImageSize = ImageInfo.DATA[1];
    BL_ImageNumOfLines = (u16)((u16)(ImageInfo.DATA[2]<<8) | (u16)(ImageInfo.DATA[3]));
}
