/**
 * @file UDS_TesterPresent_private.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 09-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef UDS_IOCONTROLBYID_PRIVATE_H_
#define UDS_IOCONTROLBYID_PRIVATE_H_


#define POS_RESPONSE_SID							0x6F

typedef struct
    {
       u8 subFunction;
       u8 DID;
       u16 ValueToUse;
    }ControlOptionRecord;

u16 ExecutecontrolOptionRecord(ControlOptionRecord ControlRecord)   // the return size to be confirmed
u8 IsNotID( u8 Copy_u8DataId );
u8 IsNotSubFunction (u8 Copy_u8SubFunction);

#endif