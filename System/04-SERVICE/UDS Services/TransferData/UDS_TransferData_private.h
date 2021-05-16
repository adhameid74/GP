/**
 * @file UDS_TransferData_private.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 12-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef UDS_TRANSFERDATA_PRIVATE_H_
#define UDS_TRANSFERDATA_PRIVATE_H_

#define incorrectMessageLengthOrInvalidFormat		0x13
#define requestSequenceError						0x24
#define requestOutOfRange							0x31
#define transferDataSuspended						0x71
#define generalProgrammingFailure					0x72
#define wrongBlockSequenceCounter					0x73
#define voltageTooHigh								0x92
#define voltageTooLow								0x93

#define NRC_LENGTH									3
#define NRC_ID										0x7F
#define SID											0x36
#define POS_RESPONSE_SID							0x76
#define POS_RESPONSE_LENGTH							2

static void SendPosResponse();
static void SendNegResponse(u8 Copy_u8NRC);

#endif
