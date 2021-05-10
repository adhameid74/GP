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

#ifndef UDS_TESTERPRESENT_PRIVATE_H_
#define UDS_TESTERPRESENT_PRIVATE_H_

#define subFunctionNotSupported 					0x12
#define incorrectMessageLengthOrInvalidFormat		0x13

#define NRC_LENGTH									3
#define NRC_ID										0x7F
#define SID											0x3E
#define POS_RESPONSE_SID							0x7E
#define POS_RESPONSE_LENGTH							2

static void SendPosResponse();
static void SendNegResponse(u8 Copy_u8NRC);

#endif
