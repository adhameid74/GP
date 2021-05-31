/**
 * @file PARSE_private.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 0.1
 * @date 30-05-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef PARSE_PRIVATE_H_
#define PARSE_PRIVATE_H_

#define ASCII_ERROR                 255
#define RECORD_TYPE_INDEX           8
#define DATA_RECORD                 48
#define UPPER_ADDRESS_RECORD        52

static u32 Address;
static u16 Data[20];

static u8 AsciiToDecimal(u8 Copy_u8Asci);
static void SetUpperAddress(u8* Copy_au8Record);
static void FlashData(u8* Copy_au8Record);

#endif
