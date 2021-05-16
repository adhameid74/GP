/**
 * @file UDS_RequestDownload_private.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 04-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef UDS_REQUESTDOWNLOAD_PRIVATE_H_
#define UDS_REQUESTDOWNLOAD_PRIVATE_H_

#define incorrectMessageLengthOrInvalidFormat		0x13
#define conditionsNotCorrect						0x22
#define requestOutOfRange							0x31
#define securityAccessDenied						0x33
#define uploadDownloadNotAccepted					0x70

#define NRC_LENGTH									3
#define NRC_ID										0x7F
#define SID											0x34
#define POS_RESPONSE_SID							0x74
#define POS_RESPONSE_LENGTH							3
#define lengthFormatIdentifier						1
#define maxNumberOfBlockLength						1

static void SendPosResponse();
static void SendNegResponse(u8 Copy_u8NRC);

#endif
