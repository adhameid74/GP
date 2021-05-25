/**
 * @file UDSHandler_interface.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 24-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef UDSHANDLER_INTERFACE_H_
#define UDSHANDLER_INTERFACE_H_

#define generalReject										0x10
#define subFunctionNotSupported								0x12
#define incorrectMessageLengthOrInvalidFormat				0x13
#define conditionsNotCorrect								0x22
#define requestOutOfRange									0x31
#define securityAccessDenied								0x33
#define invalidKey											0x35
#define exceedNumberOfAttempts								0x36
#define requiredTimeDelayNotExpired							0x37
#define uploadDownloadNotAccepted							0x70
#define transferDataSuspended								0x71
#define generalProgrammingFailure							0x72
#define wrongBlockSequenceCounter							0x73
#define requestCorrectlyReceived_ResponsePending			0x78
#define subFunctionNotSupportedInActiveSession				0x7E
#define serviceNotSupportedInActiveSession					0x7F

void UDSHandler_voidCallService(INDICATION_SDU ReceivedMessage);
void UDSHandler_voidSendNegResponse(u8 Copy_u8SID, u8 Copy_u8NRC);
void UDSHandler_voidSendPosResponse(u8* Copy_pu8Message, u8 Copy_u8Length);

#endif
