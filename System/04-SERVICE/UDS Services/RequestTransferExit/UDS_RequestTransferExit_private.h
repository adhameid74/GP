/**
 * @file UDS_RequestTransferExit_private.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 09-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef UDS_REQUESTTRANSFEREXIT_PRIVATE_H_
#define UDS_REQUESTTRANSFEREXIT_PRIVATE_H_

#define incorrectMessageLengthOrInvalidFormat		0x13
#define requestSequenceError						0x24

#define NRC_LENGTH									3
#define NRC_ID										0x7F
#define SID											0x37
#define POS_RESPONSE_SID							0x77
#define POS_RESPONSE_LENGTH							1

static void SendPosResponse();
static void SendNegResponse(u8 Copy_u8NRC);

#endif
